using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;

namespace ThudPrototype
{
    public partial class ThudTile : Canvas
    {
        // stroke and fill
        protected Pen stroke;
        public Pen Stroke
        {
            get { return stroke; }
            set
            {
                if (value != stroke)
                {
                    stroke = value;
                    InvalidateVisual();
                }
            }
        }
        protected Brush fill;
        public Brush Fill
        {
            get { return fill; }
            set
            {
                if (value != fill)
                {
                    fill = value;
                    InvalidateVisual();
                }
            }
        }

        // game piece on this tile, if any
        public static const int DwarfPointValue = 1;
        public static const int TrollPointValue = 4;
        public enum GamePiece { None, Dwarf, Troll }
        protected GamePiece piece;
        public GamePiece Piece
        {
            get { return piece; }
            set
            {
                if (value != piece)
                {
                    piece = value;
                    InvalidateVisual();
                }
            }
        }

        // tile with a piece that can be moved to this tile
        protected ThudTile targetedBy;
        public ThudTile TargetedBy
        {
            get { return targetedBy; }
            set
            {
                if (value != targetedBy)
                {
                    targetedBy = value;
                    InvalidateVisual();
                }
            }
        }

        // location on grid
        public int Column
        {
            get { return Grid.GetColumn(this); }
            set
            {
                if (value != Grid.GetColumn(this))
                {
                    Grid.SetColumn(this, value);
                    InvalidateVisual();
                    if (null != Parent && Parent is UIElement)
                    {
                        (Parent as UIElement).InvalidateVisual();
                    }
                }
            }
        }
        public int Row
        {
            get { return Grid.GetRow(this); }
            set
            {
                if (value != Grid.GetRow(this))
                {
                    Grid.SetRow(this, value);
                    InvalidateVisual();
                    if (null != Parent && Parent is UIElement)
                    {
                        (Parent as UIElement).InvalidateVisual();
                    }
                }
            }
        }

        // neighboring tiles
        public ThudTile UpLeftTile { get { return Get(Parent, Column - 1, Row + 1); } }
        public ThudTile UpTile { get { return Get(Parent, Column, Row + 1); } }
        public ThudTile UpRightTile { get { return Get(Parent, Column + 1, Row + 1); } }
        public ThudTile RightTile { get { return Get(Parent, Column + 1, Row); } }
        public ThudTile DownRightTile { get { return Get(Parent, Column + 1, Row - 1); } }
        public ThudTile DownTile { get { return Get(Parent, Column, Row - 1); } }
        public ThudTile DownLeftTile { get { return Get(Parent, Column - 1, Row - 1); } }
        public ThudTile LeftTile { get { return Get(Parent, Column - 1, Row); } }

        // Constructor
        public ThudTile(int column, int row, GamePiece content = GamePiece.None)
        {
            Column = column;
            Row = row;
            Piece = content;
        }

        // Draw a tile
        protected override void OnRender(DrawingContext dc)
        {
            DrawTile(dc);
            DrawPiece(dc);
            DrawTargetingOverlay(dc);
        }

        // Draw the tile itself
        protected void DrawTile(DrawingContext dc)
        {
            // draw tile
            bool even = ((Row + Column) % 2 == 0);
            Pen pen = even ? GetEvenTileStroke(this)
                           : GetOddTileStroke(this);
            Brush brush = even ? GetEvenTileFill(this)
                               : GetOddTileFill(this);
            if (null == pen)
            {
                pen = even ? GetOddTileStroke(this)
                            : GetEvenTileStroke(this);
            }
            if (null == brush)
            {
                brush = even ? GetOddTileFill(this)
                                : GetEvenTileFill(this);
            }
            if (null == pen)
            {
                pen = Stroke;
            }
            if (null == brush)
            {
                brush = Fill;
            }
            dc.DrawRectangle(brush, pen, new Rect(0, 0, ActualWidth, ActualHeight));
        }

        // Draw the game piece on the tile, if any
        protected void DrawPiece(DrawingContext dc)
        {
            if (GamePiece.None == Piece)
            {
                return;
            }
            Panel board = Parent as Panel;
            bool troll = (GamePiece.Troll == Piece);
            bool selected = (this == TargetedBy);
            Rect rect = troll ? GetTrollRect(this) : GetDwarfRect(this);
            if (troll ? GetTrollRectIsAbsolute(this) : GetDwarfRectIsAbsolute(this))
            {
                rect.X *= ActualWidth;
                rect.Y *= ActualHeight;
                rect.Width *= ActualWidth;
                rect.Height *= ActualHeight;
            }
            Brush brush = troll ? (selected ? GetSelectedTrollFill(this) : GetTrollFill(this))
                                : (selected ? GetSelectedDwarfFill(this) : GetDwarfFill(this));
            Pen pen = troll ? (selected ? GetSelectedTrollStroke(this) : GetTrollStroke(this))
                            : (selected ? GetSelectedDwarfStroke(this) : GetDwarfStroke(this));
            dc.DrawRectangle(brush, pen, rect);
        }

        // If a piece on another tile targets this one, draw the overlay
        protected void DrawTargetingOverlay(DrawingContext dc)
        {
            if (CanBeCaptured())
            {
                bool troll = (GamePiece.Troll == TargetedBy.Piece);
                dc.DrawRectangle(troll ? GetTrollTargetFill(this) : GetDwarfTargetFill(this),
                                 troll ? GetTrollTargetStroke(this) : GetDwarfTargetStroke(this),
                                 new Rect(0, 0, ActualWidth, ActualHeight));
            }
        }

        // When this tile is clicked, play out
        protected override void OnMouseLeftButtonUp(System.Windows.Input.MouseButtonEventArgs e)
        {
            if (CanBeCaptured())
            {
                Capture();
            }
            else
            {
                Select();
            }
        }

        // Can this tile be captured by the piece targeting it, if there is one?
        protected bool CanBeCaptured()
        {
            return (null != TargetedBy && this != TargetedBy &&
                GamePiece.None != TargetedBy.Piece && Piece != TargetedBy.Piece);
        }

        // Make the piece targeting this tile, if any, capture this tile
        protected void Capture()
        {
            // move piece
            Piece = TargetedBy.Piece;
            TargetedBy.Piece = GamePiece.None;
            ClearTargeting(Parent);

            // Trolls smash adjacent dwarves
            if (GamePiece.Troll == Piece)
            {
                if (null != UpLeftTile && GamePiece.Dwarf == UpLeftTile.Piece)
                {
                    UpLeftTile.Piece = GamePiece.None;
                }
                if (null != UpTile && GamePiece.Dwarf == UpTile.Piece)
                {
                    UpTile.Piece = GamePiece.None;
                }
                if (null != UpRightTile && GamePiece.Dwarf == UpRightTile.Piece)
                {
                    UpRightTile.Piece = GamePiece.None;
                }
                if (null != RightTile && GamePiece.Dwarf == RightTile.Piece)
                {
                    RightTile.Piece = GamePiece.None;
                }
                if (null != DownRightTile && GamePiece.Dwarf == DownRightTile.Piece)
                {
                    DownRightTile.Piece = GamePiece.None;
                }
                if (null != DownTile && GamePiece.Dwarf == DownTile.Piece)
                {
                    DownTile.Piece = GamePiece.None;
                }
                if (null != DownLeftTile && GamePiece.Dwarf == DownLeftTile.Piece)
                {
                    DownLeftTile.Piece = GamePiece.None;
                }
                if (null != LeftTile && GamePiece.Dwarf == LeftTile.Piece)
                {
                    LeftTile.Piece = GamePiece.None;
                }
            }
            else if (GamePiece.Dwarf == Piece)
            {
                if ((null != UpLeftTile && GamePiece.Troll == UpLeftTile.Piece) ||
                    (null != UpTile && GamePiece.Troll == UpTile.Piece) ||
                    (null != UpRightTile && GamePiece.Troll == UpRightTile.Piece) ||
                    (null != RightTile && GamePiece.Troll == RightTile.Piece) ||
                    (null != DownRightTile && GamePiece.Troll == DownRightTile.Piece) ||
                    (null != DownTile && GamePiece.Troll == DownTile.Piece) ||
                    (null != DownLeftTile && GamePiece.Troll == DownLeftTile.Piece) ||
                    (null != LeftTile && GamePiece.Troll == LeftTile.Piece))
                {
                    Piece = GamePiece.None;
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
                                    ? GamePiece.Troll : GamePiece.Dwarf));
                }
            }
        }

        // Pick the next tile from the current one in a given direction
        protected static ThudTile GetNextInDirection(ThudTile tile, int xDir, int yDir)
        {
            if (null == tile)
            {
                return null;
            }
            if (yDir > 0)
            {
                if (xDir < 0)
                {
                    return tile.UpLeftTile;
                }
                if (xDir == 0)
                {
                    return tile.UpTile;
                }
                else if (xDir > 0)
                {
                    return tile.UpRightTile;
                }
            }
            if (yDir == 0)
            {
                if (xDir < 0)
                {
                    return tile.LeftTile;
                }
                if (xDir > 0)
                {
                    return tile.RightTile;
                }
            }
            if (yDir < 0)
            {
                if (xDir < 0)
                {
                    return tile.DownLeftTile;
                }
                if (xDir == 0)
                {
                    return tile.DownTile;
                }
                if (xDir > 0)
                {
                    return tile.DownRightTile;
                }
            }
            return null;
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
                    MarkLaunchTarget(i, j);

                    // Check regular movement (one space for trolls, any
                    // unobstructed distance for dwarves)
                    ThudTile tile = GetNextInDirection(this, i, j);
                    if (null != tile && GamePiece.None == tile.Piece)
                    {
                        do
                        {
                            tile.TargetedBy = this;
                            tile = GetNextInDirection(this, i, j);
                        } while (null != tile && GamePiece.None == tile.Piece &&
                                 GamePiece.Dwarf == Piece);
                    }
                }
            }
        }

        // If this piece can be launched to a tile in the given direction, target said tile
        protected void MarkLaunchTarget(int xDir, int yDir)
        {
            if (0 == xDir && 0 == yDir)
            {
                return;
            }

            // if there's a piece of the same type in front of this one in the
            // given direction, then it can't be launched.
            ThudTile inFront = GetNextInDirection(this, xDir, yDir);
            if (null != inFront && Piece == inFront.Piece)
            {
                return;
            }

            // set xDir and yDir to 1, 0, or -1 and save values as increment amounts
            xDir /= Math.Abs(xDir);
            int xInc = xDir;
            yDir /= Math.Abs(yDir);
            int yInc = yDir;

            // check to see how long a line of the same type of pieces 
            ThudTile pusher = GetNextInDirection(this, -xDir, -yDir);
            if (null == pusher || Piece != pusher.Piece)
            {
                return;
            }
            do
            {
                xDir += xInc;
                yDir += yInc;
                pusher = GetNextInDirection(this, -xDir, -yDir);
            } while (null != pusher && Piece == pusher.Piece);

            // if the target has no piece on it or, if this piece is a dwarf, has a troll
            // piece on it, then it's a valid launch target.
            ThudTile target = Get(Parent, Column + xDir, Row + yDir);
            if (CanCapture(target))
            {
                target.TargetedBy = this;
            }
        }

        // Can the piece on this tile, if any, capture the given tile?
        protected bool CanCapture(ThudTile tile)
        {
            return (null != tile &&
                    ((GamePiece.Dwarf == Piece && GamePiece.Dwarf != tile.Piece) ||
                     (GamePiece.Troll == Piece && GamePiece.None == tile.Piece)));
        }

        // search for the tile child of the given panel with the given location,
        // if there is one
        public static ThudTile Get(DependencyObject parent, int X, int Y)
        {
            if (null == parent || !(parent is Panel))
            {
                return null;
            }
            return ((parent as Panel).Children as IEnumerable<UIElement>)
                    .FirstOrDefault(element => (element is ThudTile &&
                                                Grid.GetColumn(element) == X &&
                                                Grid.GetRow(element) == Y)) as ThudTile;
        }

        // get the number of pieces of a given type on the given panel
        public static int CountPieces(DependencyObject parent, GamePiece type)
        {
            if (null == parent || !(parent is Panel))
            {
                return 0;
            }
            return ((parent as Panel).Children as IEnumerable<UIElement>)
                    .Count(element => (element is ThudTile &&
                                       (element as ThudTile).Piece == type));
        }
        public static int DwarfPoints(DependencyObject parent)
        {
            return DwarfPointValue * CountPieces(parent, GamePiece.Dwarf);
        }
        public static int TrollPoints(DependencyObject parent)
        {
            return TrollPointValue * CountPieces(parent, GamePiece.Troll);
        }

        // set all the tile children of the given panel to not be targeted
        public static void ClearTargeting(DependencyObject parent)
        {
            if (null == parent || !(parent is Panel))
            {
                return;
            }
            foreach (ThudTile tile in ((parent as Panel).Children as IEnumerable<UIElement>)
                                        .Where(element => (element is ThudTile &&
                                                           null != (element as ThudTile).TargetedBy))
                                        .Cast<ThudTile>())
            {
                tile.TargetedBy = null;
            }
        }

        // clear all tiles from the panel and set up a new set in the start layout
        public static void NewBoard(DependencyObject parent)
        {
            if (null == parent || !(parent is Panel))
            {
                return;
            }
            Panel board = parent as Panel;

            // clear the board
            ThudTile[] tiles = (board.Children as IEnumerable<UIElement>)
                                .Where(element => (element is ThudTile))
                                .Cast<ThudTile>().ToArray();
            foreach (ThudTile tile in tiles)
            {
                board.Children.Remove(tile);
            }

            // make new set of tiles
            for (int i = 0; i < initialLayout.Length; ++i)
            {
                for (int j = 0; j < initialLayout[0].Length; ++j)
                {
                    if (null != initialLayout[i][j])
                    {
                        board.Children.Add(
                            new ThudTile(i, j, (GamePiece)initialLayout[i][j]));
                    }
                }
            }
            board.InvalidateVisual();
        }
    }
}
