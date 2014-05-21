using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;

namespace ThudPrototype
{
    public partial class ThudTile
    {
        // When this tile is clicked, play out
        protected override void OnMouseLeftButtonUp(System.Windows.Input.MouseButtonEventArgs e)
        {
            if (CanBeCaptured())
            {
                Capture();
            }
            else if (null != Parent && Parent is Panel && GetPlayer(Parent as Panel) == Piece)
            {
                Select();
            }
        }

        // Can this tile be captured by the piece targeting it, if there is one?
        protected bool captureToEndTurn = false;
        protected bool CanBeCaptured()
        {
            return (captureToEndTurn ||
                    (null != TargetedBy && this != TargetedBy &&
                     Piece != TargetedBy.Piece &&
                     GamePiece.None != TargetedBy.Piece));
        }

        // Make the piece targeting this tile, if any, capture this tile
        protected void Capture()
        {
            // If capturing this piece ends the turn, do so
            if (captureToEndTurn)
            {
                // TODO
            }

            // if this tile isn't being targeted by anything, don't bother
            if (null == TargetedBy || GamePiece.None == TargetedBy.Piece)
            {
                return;
            }

            switch (Piece)
            {
                case GamePiece.Dwarf:
                    if (GamePiece.Troll == TargetedBy.Piece)
                    {
                        Piece = GamePiece.None;
                        TargetedBy = null;
                    }
                    break;
                case GamePiece.Troll:
                    if (GamePiece.Dwarf == TargetedBy.Piece)
                    {
                        Piece = GamePiece.Dwarf;
                        TargetedBy.Piece = GamePiece.None;
                        TargetedBy = null;
                    }
                    break;
                case GamePiece.None:
                    Piece = TargetedBy.Piece;
                    TargetedBy.Piece = GamePiece.None;
                    if (GamePiece.Troll == Piece)
                    {
                        foreach (ThudTile tile in Neighbors.Where(tile => GamePiece.Dwarf == tile.Piece))
                        {
                            tile.TargetedBy = this;
                        }
                        if (Neighbors.Contains(TargetedBy))
                        {
                            TargetedBy = this;
                            captureToEndTurn = true;
                        }
                    }
                    if (this != TargetedBy)
                    {
                        TargetedBy = null;
                    }
                    break;
            }

            // move piece
            Piece = TargetedBy.Piece;
            TargetedBy.Piece = GamePiece.None;
            ClearTargeting(Parent);

            // Trolls smash adjacent dwarves
            if (GamePiece.Troll == Piece)
            {
                foreach (ThudTile tile in Neighbors.Where(tile => GamePiece.Dwarf == tile.Piece))
                {
                    tile.Piece = GamePiece.None;
                }
            }

            // Update whose turn it is
            if (null != Parent && Parent is Panel)
            {
                if (CountPieces(Parent, GamePiece.Troll) == 0 ||
                    CountPieces(Parent, GamePiece.Dwarf) == 0)
                {
                    SetPlayer(Parent as Panel, GamePiece.None);
                }
                else if (GetPlayer(this) != GamePiece.None)
                {
                    SetPlayer(Parent as Panel,
                                   (GetPlayer(this) == GamePiece.Troll
                                    ? GamePiece.Dwarf : GamePiece.Troll));
                }
            }
        }

        protected void EndTurn()
        {
            captureToEndTurn = false;
            ClearTargeting(Parent);
        }

        // Select the piece on this tile, if any
        protected void Select()
        {
            ClearTargeting(Parent);
            if (GamePiece.None == Piece)
            {
                return;
            }
            TargetedBy = this;

            // In every direction,
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    // Check launchability
                    MarkTargets(i, j);
                }
            }
        }

        // Mark targets for movement of a game piece from this tile in the given direction
        protected void MarkTargets(int xDir, int yDir)
        {
            if ((0 == xDir && 0 == yDir) || GamePiece.None == Piece)
            {
                return;
            }

            // if there's another piece of the same type in front of this one in the
            // given direction, then it can't move in that direction.
            ThudTile inFront = GetNextInDirection(this, xDir, yDir);
            if (null != inFront && Piece == inFront.Piece)
            {
                return;
            }

            // set xDir and yDir to 1, 0, or -1 and save values as increment amounts
            xDir /= (0 == xDir ? 1 : Math.Abs(xDir));
            int xInc = xDir;
            yDir /= (0 == yDir ? 1 : Math.Abs(yDir));
            int yInc = yDir;

            // Calculate potential assisted move distance
            ThudTile assister = GetNextInDirection(this, -xDir, -yDir);
            int assistPlaces = 1;
            while (null != assister && GamePiece.Dwarf == assister.Piece)
            {
                ++assistPlaces;
                assister = GetNextInDirection(assister, -xDir, -yDir);
            }

            ThudTile target = GetNextInDirection(this, xDir, yDir);
            bool blocked = false;
            bool assistCanCapture = (GamePiece.Troll == Piece);
            do
            {
                // If the tile is empty and (if this piece is a troll) has adjacent
                // dwarves, or (if this piece is a dwarf) contains a troll, target it.
                if (null != target && Piece != target.Piece &&
                    GamePiece.Dwarf != target.Piece &&
                    (GamePiece.Dwarf == Piece ||
                     target.Neighbors.Count(tile => GamePiece.Dwarf == tile.Piece) > 0))
                {
                    target.TargetedBy = this;
                }

                // If the tile doesn't exist or contains an obstacle, or if this
                // piece is a troll, further movement is impossible without assist.
                if (!blocked &&
                    (GamePiece.Troll == Piece || null == target ||
                     GamePiece.None != target.Piece))
                {
                    blocked = true;
                }

                // If this piece is a dwarf and the tile contains a troll and is
                // within hurling distance, then hurling is allowed.
                if (!assistCanCapture && GamePiece.Dwarf == Piece && null != target &&
                    GamePiece.Troll == target.Piece && assistPlaces > 0)
                {
                    assistCanCapture = true;
                }

                // get ready to check the next tile
                --assistPlaces;
                target = GetNextInDirection(target, xDir, yDir);
            } while (!blocked || (assistCanCapture && assistPlaces > 0));
        }
    }
}