using System;
using System.Collections;
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
        // point values of each type of piece
        public const int DwarfPointValue = 1, TrollPointValue = 4;

        // default dwarf and troll piece drawings
        public static readonly Brush DefaultDwarfFill = MakeDefaultDwarfFill();
        public static readonly Brush DefaultTrollFill = MakeDefaultTrollFill();
        public static readonly Brush DefaultSelectedDwarfFill = MakeDefaultSelectedDwarfFill();
        public static readonly Brush DefaultSelectedTrollFill = MakeDefaultSelectedTrollFill();

        // initial layout of a thud board
        public static readonly GamePiece?[][] InitialLayout = MakeInitialLayout();

        // Make default dwarf brushes
        protected static Geometry MakeDefaultDwarfGeometry()
        {
            return new PathGeometry(new PathFigure[] {
                        new PathFigure(new Point(12, 0),
                            new PathSegment[] {
                                new LineSegment(new Point(24, 24), true),
                                new LineSegment(new Point(0, 24), true),
                                new LineSegment(new Point(12, 0), true)
                            }, true) });
        }
        protected static Brush MakeDefaultDwarfFill()
        {
            DrawingBrush fill = new DrawingBrush(
                new GeometryDrawing(Brushes.Red, new Pen(Brushes.Magenta, 4),
                                    MakeDefaultDwarfGeometry()));
            fill.Stretch = Stretch.Uniform;
            fill.TileMode = TileMode.None;
            return fill;
        }
        protected static Brush MakeDefaultSelectedDwarfFill()
        {
            DrawingBrush fill = new DrawingBrush(
                new GeometryDrawing(Brushes.Red, new Pen(Brushes.Yellow, 4),
                                    MakeDefaultDwarfGeometry()));
            fill.Stretch = Stretch.Uniform;
            fill.TileMode = TileMode.None;
            return fill;
        }

        // Make default troll brushes
        protected static Geometry MakeDefaultTrollGeometry()
        {
            return new RectangleGeometry(new Rect(3, 0, 18, 24));
        }
        protected static Brush MakeDefaultTrollFill()
        {
            DrawingBrush fill = new DrawingBrush(
                new GeometryDrawing(Brushes.Blue, new Pen(Brushes.Aqua, 4),
                                    MakeDefaultTrollGeometry()));
            fill.Stretch = Stretch.Uniform;
            fill.TileMode = TileMode.None;
            return fill;
        }
        protected static Brush MakeDefaultSelectedTrollFill()
        {
            DrawingBrush fill = new DrawingBrush(
                new GeometryDrawing(Brushes.Blue, new Pen(Brushes.Lime, 4),
                                    MakeDefaultTrollGeometry()));
            fill.Stretch = Stretch.Uniform;
            fill.TileMode = TileMode.None;
            return fill;
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

        // search for the tile child of the given panel with the given location,
        // if there is one
        public static ThudTile Get(DependencyObject parent, int X, int Y)
        {
            if (null == parent || !(parent is Panel))
            {
                return null;
            }
            return ((parent as Panel).Children).OfType<ThudTile>()
                    .FirstOrDefault(tile => (Grid.GetColumn(tile) == X &&
                                             Grid.GetRow(tile) == Y));
        }

        // get the number of pieces of a given type on the given panel
        public static int CountPieces(DependencyObject parent, GamePiece type)
        {
            if (null == parent || !(parent is Panel))
            {
                return 0;
            }
            return ((parent as Panel).Children as IEnumerable).OfType<ThudTile>()
                    .Count(tile => tile.Piece == type);
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
            foreach (ThudTile tile in ((parent as Panel).Children as IEnumerable)
                                        .OfType<ThudTile>()
                                        .Where(tile => (null != tile.TargetedBy)))
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
            ThudTile[] tiles = (board.Children as IEnumerable)
                                .OfType<ThudTile>().ToArray();
            foreach (ThudTile tile in tiles)
            {
                board.Children.Remove(tile);
            }

            // make new set of tiles
            for (int i = 0; i < InitialLayout.Length; ++i)
            {
                for (int j = 0; j < InitialLayout[0].Length; ++j)
                {
                    if (null != InitialLayout[i][j])
                    {
                        board.Children.Add(
                            new ThudTile(i, j, (GamePiece)InitialLayout[i][j]));
                    }
                }
            }
            board.InvalidateVisual();
        }
    }
}