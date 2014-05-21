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
        // default dwarf and troll piece drawings
        public static DrawingBrush DefaultDwarfFill;
        public static DrawingBrush DefaultTrollFill;
        public static DrawingBrush DefaultSelectedDwarfFill;
        public static DrawingBrush DefaultSelectedTrollFill;
        static ThudTile()
        {
            Geometry DwarfGeometry =
                new PathGeometry( new PathFigure[] {
                    new PathFigure(new Point(12, 0),
                        new PathSegment[] {
                            new LineSegment(new Point(24, 24), true),
                            new LineSegment(new Point(0, 24), true),
                            new LineSegment(new Point(12, 0), true)
                        }, true) });
            DefaultDwarfFill = new DrawingBrush(
                new GeometryDrawing(Brushes.Red, new Pen(Brushes.Magenta, 4),
                                    DwarfGeometry));
            DefaultDwarfFill.Stretch = Stretch.Uniform;
            DefaultDwarfFill.TileMode = TileMode.None;
            DefaultSelectedDwarfFill = new DrawingBrush(
                new GeometryDrawing(Brushes.Red, new Pen(Brushes.Yellow, 4),
                                    DwarfGeometry));
            DefaultSelectedDwarfFill.Stretch = Stretch.Uniform;
            DefaultSelectedDwarfFill.TileMode = TileMode.None;
            DefaultTrollFill = new DrawingBrush(
                new GeometryDrawing(Brushes.Blue, new Pen(Brushes.Aqua, 4),
                                    new RectangleGeometry(new Rect(0, 6, 24, 18))));
            DefaultTrollFill.Stretch = Stretch.Uniform;
            DefaultTrollFill.TileMode = TileMode.None;
            DefaultSelectedTrollFill = new DrawingBrush(
                new GeometryDrawing(Brushes.Blue, new Pen(Brushes.Lime, 4),
                                    new RectangleGeometry(new Rect(0, 6, 24, 18))));
            DefaultSelectedTrollFill.Stretch = Stretch.Uniform;
            DefaultSelectedTrollFill.TileMode = TileMode.None;
        }

        // For setting the size of Dwarf pieces
        public static readonly DependencyProperty DwarfRectProperty =
            DependencyProperty.RegisterAttached("DwarfRect", typeof(Rect), typeof(Panel),
                                                new FrameworkPropertyMetadata(
                                                    new Rect(0.125, 0.125, 0.875, 0.875),
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfRect(Panel panel, Rect rect)
        {
            panel.SetValue(DwarfRectProperty, rect);
        }
        public static Rect GetDwarfRect(Panel panel)
        {
            return (Rect)panel.GetValue(DwarfRectProperty);
        }
        public static readonly DependencyProperty DwarfRectIsAbsoluteProperty =
            DependencyProperty.RegisterAttached("DwarfRectIsAbsolute", typeof(bool), typeof(Panel),
                                                new FrameworkPropertyMetadata(false,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfRectIsAbsolute(Panel panel, bool absolute)
        {
            panel.SetValue(DwarfRectIsAbsoluteProperty, absolute);
        }
        public static bool GetDwarfRectIsAbsolute(Panel panel)
        {
            return (bool)panel.GetValue(DwarfRectIsAbsoluteProperty);
        }

        // For setting the graphics a board uses for Dwarf pieces
        public static readonly DependencyProperty DwarfStrokeProperty =
            DependencyProperty.RegisterAttached("DwarfStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(DwarfStrokeProperty, stroke);
        }
        public static Pen GetDwarfStroke(Panel panel)
        {
            return (Pen)panel.GetValue(DwarfStrokeProperty);
        }
        public static readonly DependencyProperty DwarfFillProperty =
            DependencyProperty.RegisterAttached("DwarfFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(DefaultDwarfFill,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfFill(Panel panel, Brush fill)
        {
            panel.SetValue(DwarfFillProperty, fill);
        }
        public static Brush GetDwarfFill(Panel panel)
        {
            return (Brush)panel.GetValue(DwarfFillProperty);
        }

        // For setting the graphics a board uses for selected Dwarf pieces
        public static readonly DependencyProperty SelectedDwarfStrokeProperty =
            DependencyProperty.RegisterAttached("SelectedDwarfStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetSelectedDwarfStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(SelectedDwarfStrokeProperty, stroke);
        }
        public static Pen GetSelectedDwarfStroke(Panel panel)
        {
            return (Pen)panel.GetValue(SelectedDwarfStrokeProperty);
        }
        public static readonly DependencyProperty SelectedDwarfFillProperty =
            DependencyProperty.RegisterAttached("SelectedDwarfFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(DefaultSelectedDwarfFill,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetSelectedDwarfFill(Panel panel, Brush fill)
        {
            panel.SetValue(SelectedDwarfFillProperty, fill);
        }
        public static Brush GetSelectedDwarfFill(Panel panel)
        {
            return (Brush)panel.GetValue(SelectedDwarfFillProperty);
        }

        // For setting the graphics a board overlays on tiles targeted by Dwarf pieces
        public static readonly DependencyProperty DwarfTargetStrokeProperty =
            DependencyProperty.RegisterAttached("DwarfTargetStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(new Pen(Brushes.Yellow, 3),
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfTargetStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(DwarfTargetStrokeProperty, stroke);
        }
        public static Pen GetDwarfTargetStroke(Panel panel)
        {
            return (Pen)panel.GetValue(DwarfTargetStrokeProperty);
        }
        public static readonly DependencyProperty DwarfTargetFillProperty =
            DependencyProperty.RegisterAttached("DwarfTargetFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetDwarfTargetFill(Panel panel, Brush fill)
        {
            panel.SetValue(DwarfTargetFillProperty, fill);
        }
        public static Brush GetDwarfTargetFill(Panel panel)
        {
            return (Brush)panel.GetValue(DwarfTargetFillProperty);
        }

        // For setting the size of Troll pieces
        public static readonly DependencyProperty TrollRectProperty =
            DependencyProperty.RegisterAttached("TrollRect", typeof(Rect), typeof(Panel),
                                                new FrameworkPropertyMetadata(
                                                    new Rect(0.125, 0.125, 0.875, 0.875),
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollRect(Panel panel, Rect rect)
        {
            panel.SetValue(TrollRectProperty, rect);
        }
        public static Rect GetTrollRect(Panel panel)
        {
            return (Rect)panel.GetValue(TrollRectProperty);
        }
        public static readonly DependencyProperty TrollRectIsAbsoluteProperty =
            DependencyProperty.RegisterAttached("TrollRectIsAbsolute", typeof(bool), typeof(Panel),
                                                new FrameworkPropertyMetadata(false,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollRectIsAbsolute(Panel panel, bool absolute)
        {
            panel.SetValue(TrollRectIsAbsoluteProperty, absolute);
        }
        public static bool GetTrollRectIsAbsolute(Panel panel)
        {
            return (bool)panel.GetValue(TrollRectIsAbsoluteProperty);
        }

        // For setting the graphics a board uses for Troll pieces
        public static readonly DependencyProperty TrollStrokeProperty =
            DependencyProperty.RegisterAttached("TrollStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(TrollStrokeProperty, stroke);
        }
        public static Pen GetTrollStroke(Panel panel)
        {
            return (Pen)panel.GetValue(TrollStrokeProperty);
        }
        public static readonly DependencyProperty TrollFillProperty =
            DependencyProperty.RegisterAttached("TrollFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(DefaultTrollFill,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollFill(Panel panel, Brush fill)
        {
            panel.SetValue(TrollFillProperty, fill);
        }
        public static Brush GetTrollFill(Panel panel)
        {
            return (Brush)panel.GetValue(TrollFillProperty);
        }

        // For setting the graphics a board uses for selected Troll pieces
        public static readonly DependencyProperty SelectedTrollStrokeProperty =
            DependencyProperty.RegisterAttached("SelectedTrollStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetSelectedTrollStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(SelectedTrollStrokeProperty, stroke);
        }
        public static Pen GetSelectedTrollStroke(Panel panel)
        {
            return (Pen)panel.GetValue(SelectedTrollStrokeProperty);
        }
        public static readonly DependencyProperty SelectedTrollFillProperty =
            DependencyProperty.RegisterAttached("SelectedTrollFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(DefaultSelectedTrollFill,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetSelectedTrollFill(Panel panel, Brush fill)
        {
            panel.SetValue(SelectedTrollFillProperty, fill);
        }
        public static Brush GetSelectedTrollFill(Panel panel)
        {
            return (Brush)panel.GetValue(SelectedTrollFillProperty);
        }

        // For setting the graphics a board overlays on tiles targeted by Troll pieces
        public static readonly DependencyProperty TrollTargetStrokeProperty =
            DependencyProperty.RegisterAttached("TrollTargetStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(new Pen(Brushes.Yellow, 3),
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollTargetStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(TrollTargetStrokeProperty, stroke);
        }
        public static Pen GetTrollTargetStroke(Panel panel)
        {
            return (Pen)panel.GetValue(TrollTargetStrokeProperty);
        }
        public static readonly DependencyProperty TrollTargetFillProperty =
            DependencyProperty.RegisterAttached("TrollTargetFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetTrollTargetFill(Panel panel, Brush fill)
        {
            panel.SetValue(TrollTargetFillProperty, fill);
        }
        public static Brush GetTrollTargetFill(Panel panel)
        {
            return (Brush)panel.GetValue(TrollTargetFillProperty);
        }

        // For setting the graphics a board uses for tiles where GridX + GridY is even
        public static readonly DependencyProperty EvenTileStrokeProperty =
            DependencyProperty.RegisterAttached("EvenTileStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetEvenTileStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(EvenTileStrokeProperty, stroke);
        }
        public static Pen GetEvenTileStroke(Panel panel)
        {
            return (Pen)panel.GetValue(EvenTileStrokeProperty);
        }
        public static readonly DependencyProperty EvenTileFillProperty =
            DependencyProperty.RegisterAttached("EvenTileFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(Brushes.White,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetEvenTileFill(Panel panel, Brush fill)
        {
            panel.SetValue(EvenTileFillProperty, fill);
        }
        public static Brush GetEvenTileFill(Panel panel)
        {
            return (Brush)panel.GetValue(EvenTileFillProperty);
        }

        // For setting the graphics a board uses for tiles where GridX + GridY is odd
        public static readonly DependencyProperty OddTileStrokeProperty =
            DependencyProperty.RegisterAttached("OddTileStroke", typeof(Pen), typeof(Panel),
                                                new FrameworkPropertyMetadata(null,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetOddTileStroke(Panel panel, Pen stroke)
        {
            panel.SetValue(OddTileStrokeProperty, stroke);
        }
        public static Pen GetOddTileStroke(Panel panel)
        {
            return (Pen)panel.GetValue(OddTileStrokeProperty);
        }
        public static readonly DependencyProperty OddTileFillProperty =
            DependencyProperty.RegisterAttached("OddTileFill", typeof(Brush), typeof(Panel),
                                                new FrameworkPropertyMetadata(Brushes.Black,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetOddTileFill(Panel panel, Brush fill)
        {
            panel.SetValue(OddTileFillProperty, fill);
        }
        public static Brush GetOddTileFill(Panel panel)
        {
            return (Brush)panel.GetValue(OddTileFillProperty);
        }

        // For setting a board's current player
        public static readonly DependencyProperty PlayerProperty =
            DependencyProperty.RegisterAttached("Player", typeof(GamePiece), typeof(Panel),
                                                new FrameworkPropertyMetadata(GamePiece.None,
                                                    FrameworkPropertyMetadataOptions.Inherits));
        public static void SetPlayer(Panel panel, GamePiece playerPiece)
        {
            panel.SetValue(PlayerProperty, playerPiece);
            panel.RaiseEvent(new RoutedEventArgs(PlayerChangedEvent));
        }
        public static GamePiece GetPlayer(Panel panel)
        {
            return (GamePiece)panel.GetValue(PlayerProperty);
        }
        public static readonly RoutedEvent PlayerChangedEvent =
            EventManager.RegisterRoutedEvent("PlayerChanged", RoutingStrategy.Bubble,
                                             typeof(RoutedEventHandler), typeof(Panel));
        public static void AddPlayerChangedHandler(DependencyObject d, RoutedEventHandler handler)
        {
            UIElement uie = d as UIElement;
            if (null != uie)
            {
                uie.AddHandler(ThudTile.PlayerChangedEvent, handler);
            }
        }
        public static void RemovePlayerChangedHandler(DependencyObject d, RoutedEventHandler handler)
        {
            UIElement uie = d as UIElement;
            if (null != uie)
            {
                uie.RemoveHandler(ThudTile.PlayerChangedEvent, handler);
            }
        }
    }
}