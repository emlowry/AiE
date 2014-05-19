/******************************************************************************
 * File:               SheetCanvas.cs
 * Author:             Elizabeth Lowry
 * Date Created:       May 6, 2014
 * Description:        Canvas representing the sprite sheet as a whole.
 * Last Modified:      May 18, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SpriteMapGenerator
{
    class SheetCanvas : Canvas, INotifyPropertyChanged
    {
        // Pens used for outlining normal, selected, and colliding sprites,
        // respectively.
        protected static Pen normalOutline =
            new Pen(AnimatedPattern.Create(Colors.Lime, Colors.Yellow), 1);
        protected static Pen selectedOutline =
            new Pen(AnimatedPattern.Create(Colors.Blue, Colors.Aqua), 1);
        protected static Pen collidingOutline =
            new Pen(AnimatedPattern.Create(Colors.Red, Colors.Magenta), 1);

        // Variables for keeping track of click/drag events
        protected Point mouseStartPosition, mouseEndPosition;
        protected bool movingSelected = false;
        protected bool mouseDown = false;
        protected bool mouseStartedOnSelection = false;
        protected Sprite mouseStartedOn = null;

        // Track all the sprites and which ones are selected and which ones are
        // colliding.
        protected HashSet<Sprite> sprites = new HashSet<Sprite>();
        protected HashSet<Sprite> selected = new HashSet<Sprite>();
        protected HashSet<Sprite> colliding = new HashSet<Sprite>();
        public int SpriteCount { get { return sprites.Count; } }
        public int SelectionCount { get { return selected.Count; } }
        public int CollisionCount { get { return colliding.Count; } }

        // The size of the canvas can be retrieved by anyone but can only be set
        // within the class itself, when sprite layout changes.
        public Size Size
        {
            get { return new Size(Width, Height); }
            protected set
            {
                Width = (int)value.Width;
                Height = (int)value.Height;
            }
        }
        new public int Width
        {
            get { return (int)base.Width; }
            protected set
            {
                if (value != (int)base.Width)
                {
                    base.Width = value;
                    NotifyPropertyChanged("Size");
                    NotifyPropertyChanged("Width");
                    InvalidateVisual();
                }
            }
        }
        new public int Height
        {
            get { return (int)base.Height; }
            protected set
            {
                if (value != (int)base.Height)
                {
                    base.Height = value;
                    NotifyPropertyChanged("Size");
                    NotifyPropertyChanged("Height");
                    InvalidateVisual();
                }
            }
        }

        // Initial size, unlike regular size, can be set by others, but doing so
        // will only change the actual size of there's nothing currently on the
        // canvas
        int initialWidth, initialHeight;
        public int InitialWidth
        {
            get { return initialWidth; }
            set
            {
                if (value != initialWidth)
                {
                    initialWidth = value;
                    NotifyPropertyChanged("InitialSize");
                    NotifyPropertyChanged("InitialWidth");
                }
                if (0 == SpriteCount)
                {
                    Width = value;
                }
            }
        }
        public int InitialHeight
        {
            get { return initialHeight; }
            set
            {
                if (value != Height)
                {
                    initialHeight = value;
                    NotifyPropertyChanged("InitialSize");
                    NotifyPropertyChanged("InitialHeight");
                }
                if (0 == SpriteCount)
                {
                    Height = value;
                }
            }
        }
        public Size InitialSize
        {
            get { return new Size(InitialWidth, InitialHeight); }
            set
            {
                InitialWidth = (int)value.Width;
                InitialHeight = (int)value.Height;
            }
        }

        // The general shape to aim for when packing sprites into a compact sheet
        protected SpriteBin.BinShape layout = SpriteBin.BinShape.Square;
        public SpriteBin.BinShape SpriteLayout
        {
            get { return layout; }
            set
            {
                if (value != layout)
                {
                    layout = value;
                    NotifyPropertyChanged("SpriteLayout");
                    NotifyPropertyChanged("SquareLayout");
                    NotifyPropertyChanged("TallLayout");
                    NotifyPropertyChanged("WideLayout");
                }
            }
        }

        // These boolean properties can't be set to false directly - they only
        // change if one of the others is set to true.
        public bool SquareLayout
        {
            get { return (SpriteBin.BinShape.Square == SpriteLayout); }
            set { if (value) SpriteLayout = SpriteBin.BinShape.Square; }
        }
        public bool TallLayout
        {
            get { return (SpriteBin.BinShape.Tall == SpriteLayout); }
            set { if (value) SpriteLayout = SpriteBin.BinShape.Tall; }
        }
        public bool WideLayout
        {
            get { return (SpriteBin.BinShape.Wide == SpriteLayout); }
            set { if (value) SpriteLayout = SpriteBin.BinShape.Wide; }
        }

        // Should sprites added to the canvas be automatically arranged in a
        // collision-free and relatively compact layout when added?
        protected bool autoArrange = false;
        protected SpriteBin spriteBin = null;   // Tracks available free space
        public bool AutoArrange
        {
            get { return autoArrange; }
            set
            {
                if (value != autoArrange)
                {
                    autoArrange = value;
                    NotifyPropertyChanged("AutoArrange");

                    // If the canvas wasn't in auto-arrange mode before but is
                    // now, rearrange into an automatic layout.
                    if (value)
                    {
                        Rearrange();
                    }
                    // If the canvas *was* in auto-arrange mode before but
                    // *isn't* now, get rid of the structure tracking available
                    // freespace.
                    else
                    {
                        spriteBin = null;
                    }
                }
            }
        }

        // Make sure that custom properties that other things might listen to
        // send signals to their listeners when they change.
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        // Call this when a click/drag starts and while it continues.
        public void Drag(Point position)
        {
            // If the click/drag is just starting,
            if (!mouseDown)
            {
                // record that it started and where,
                mouseDown = true;
                mouseStartPosition = position;
                mouseStartedOn = At(mouseStartPosition);

                // and if starting on a sprite that isn't selected, try selecting it.
                if (null != mouseStartedOn && !selected.Contains(mouseStartedOn))
                {
                    Select(mouseStartedOn);
                }

                // After that check, is the sprite you started on selected?
                // If so, any movement will change this from a click to a drag.
                mouseStartedOnSelection = selected.Contains(mouseStartedOn);
            }

            // Use the current position as the end position.
            mouseEndPosition = position;

            // If this is still a click instead of a drag, but the click started
            // on a sprite that is now selected and the mouse has moved from its
            // start position, turn this into a drag.
            if (!movingSelected && mouseStartedOnSelection &&
                mouseStartPosition != mouseEndPosition)
            {
                movingSelected = true;

                // If in auto-arrange mode, update layout.
                if (AutoArrange)
                {
                    Rearrange();
                }
            }

            // If a drag is in process, update collision list.
            if (movingSelected)
            {
                CheckCollisions();
                InvalidateVisual();
            }
        }

        // Call this when a click or drag finishes.
        public void EndDrag(Point position)
        {
            // Note that the click has ended and where.
            mouseDown = false;
            mouseEndPosition = position;
            Sprite endedOn = At(mouseEndPosition);

            // If this was a drag and not just a click,
            if (movingSelected)
            {
                // note that the drag has ended.
                movingSelected = false;

                // If in auto-arrange mode, rearrange sprites if you've moved
                // the sprite you clicked on to start the drag enough that it no
                // longer overlaps with its previous position.
                if (AutoArrange)
                {
                    if (mouseStartedOn.Width < Math.Abs(mouseEndPosition.X - mouseStartPosition.X) ||
                        mouseStartedOn.Height < Math.Abs(mouseEndPosition.Y - mouseStartPosition.Y))
                    {
                        HashSet<Sprite> temp = new HashSet<Sprite>(selected);
                        selected.Clear();
                        Rearrange();
                        selected.UnionWith(temp);
                    }
                }
                // If not in auto-arrange mode, add displacement to the positions
                // of all selected sprites.
                else
                {
                    foreach (Sprite sprite in selected)
                    {
                        sprite.X += (int)(mouseEndPosition.X - mouseStartPosition.X);
                        sprite.Y += (int)(mouseEndPosition.Y - mouseStartPosition.Y);
                    }
                    CheckCollisions();
                }
                InvalidateVisual();
            }

            // If this was merely a click, and it didn't start on a sprite, try
            // to select whatever the click ended on.
            else if (null == mouseStartedOn)
            {
                Select(At(mouseEndPosition));
            }

            // Clean up remaining variables.
            mouseStartedOn = null;
            mouseStartedOnSelection = false;
        }

        protected override void OnRender(DrawingContext dc)
        {
            // Draw the sprite images first.  If a drag is in progress, draw them
            // at a displacement from their actual positions.
            foreach (Sprite sprite in sprites)
            {
                Rect boundary = sprite.Boundary;
                if (mouseDown && selected.Contains(sprite))
                {
                    boundary.X += (int)(mouseEndPosition.X - mouseStartPosition.X);
                    boundary.Y += (int)(mouseEndPosition.Y - mouseStartPosition.Y);
                }
                dc.DrawImage(sprite.Source, boundary);
            }

            // Draw the outlines next, so that even sprites covered up by others
            // will be indicated.
            foreach (Sprite sprite in sprites)
            {
                Rect border = sprite.Boundary;

                // Shrink the border to align with pixel centers.  Otherwise, it
                // will appear blurry.
                border.X += 0.5;
                border.Y += 0.5;
                border.Height -= 1;
                border.Width -= 1;

                // If a drag is in progress, draw the outline at a displacement
                // from the sprite's actual position.
                if (mouseDown && selected.Contains(sprite))
                {
                    border.X += (int)(mouseEndPosition.X - mouseStartPosition.X);
                    border.Y += (int)(mouseEndPosition.Y - mouseStartPosition.Y);
                }

                // Use the outline color to indicate if the sprite is currently
                // selected or colliding with other sprites.
                if (selected.Contains(sprite))
                {
                    dc.DrawRectangle(null, selectedOutline, border);
                }
                else if (colliding.Contains(sprite))
                {
                    dc.DrawRectangle(null, collidingOutline, border);
                }
                else
                {
                    dc.DrawRectangle(null, normalOutline, border);
                }
            }
        }

        // Add a new sprite to the sheet, selecting it if indicated.
        public void AddSprite(Sprite sprite, bool select = false,
                              ModifierKeys? modifiers = null)
        {
            // If the sprite should be selected,
            if (select)
            {
                // look up modifier keys if not already provided,
                if (null == modifiers)
                {
                    modifiers = Keyboard.Modifiers;
                }

                // and add to selection list.
                Select(sprite, (ModifierKeys)modifiers);
            }

            // If not actually selecting a sprite, there's no need to do
            // anything more.
            if (null == sprite)
            {
                return;
            }

            // If there's a sprite in the sheet with the same name as this one,
            // adjust the name until it is unique.
            while (sprites.Count(otherSprite => (otherSprite.Name == sprite.Name)) > 0)
            {
                sprite.AdjustName();
            }

            // Add the sprite to the sprite list.
            sprites.Add(sprite);
            NotifyPropertyChanged("SpriteCount");

            // If the canvas is in auto-arrange mode, change its position to
            // fit into a new or existing block of free space.
            if (AutoArrange)
            {
                spriteBin = SpriteBin.Pack(spriteBin, sprite, SpriteLayout);
            }
            else
            {
                // Otherwise, check all the other sprites to see if they collide
                // with this one.
                foreach (Sprite otherSprite in sprites)
                {
                    if (sprite != otherSprite &&
                        BoundariesCollide(sprite.Boundary, otherSprite.Boundary))
                    {
                        colliding.Add(sprite);
                        colliding.Add(otherSprite);
                    }
                }

                // If so, notify listeners of the change in the number of
                // collisions.
                if (colliding.Contains(sprite))
                {
                    NotifyPropertyChanged("CollisionCount");
                }
            }

            // Adjust canvas size to contain the new sprite, if neccessary.
            this.Width = (sprites.Count == 1) ? sprite.Right
                            : Math.Max(this.Width, sprite.Right);
            this.Height = (sprites.Count == 1) ? sprite.Bottom
                            : Math.Max(this.Height, sprite.Bottom);
            InvalidateVisual();
        }

        // Add multiple new sprites to the sheet, selecting them if indicated.
        public void AddSprites(IEnumerable<Sprite> spritesToAdd,
                               bool select = false,
                               ModifierKeys? modifiers = null)
        {
            // If selecting, look up modifier keys if not already provided
            if (select && null == modifiers)
            {
                modifiers = Keyboard.Modifiers;
            }
            if (null == spritesToAdd || 0 == spritesToAdd.Count())
            {
                Select(null, modifiers);
                return;
            }

            // Add each sprite.
            foreach (Sprite sprite in spritesToAdd)
            {
                if (null != sprite)
                {
                    sprites.Add(sprite);
                }

                // If selecting, add a shift to the modifiers so that all of the
                // added sprites will be selected.
                if (select)
                {
                    Select(sprite, modifiers);
                    modifiers = (ModifierKeys)modifiers | ModifierKeys.Shift;
                }
            }
            NotifyPropertyChanged("SpriteCount");

            // Adjust canvas dimensions
            if (AutoArrange)
            {
                spriteBin = SpriteBin.Pack(spriteBin, spritesToAdd, SpriteLayout);
                this.Size = spriteBin.Size;
            }
            else
            {
                CheckCollisions();
                this.Width = Math.Max(
                    (SpriteCount > spritesToAdd.Count() ? this.Width : 0),
                    spritesToAdd.Max(sprite => (null == sprite ? 0 : sprite.Right)));
                this.Height = Math.Max(
                    (SpriteCount > spritesToAdd.Count() ? this.Height : 0),
                    spritesToAdd.Max(sprite => (null == sprite ? 0 : sprite.Bottom)));
            }
            InvalidateVisual();
        }

        // Select the given sprite
        public void Select(Sprite sprite, ModifierKeys? modifiers = null)
        {
            // If the modifier keys weren't given, look them up.
            if (null == modifiers)
            {
                modifiers = Keyboard.Modifiers;
            }

            // If the Alt key is pressed, remove the given sprite from the
            // selection list if present.
            if ((modifiers & ModifierKeys.Alt) == ModifierKeys.Alt)
            {
                if (null != sprite)
                {
                    selected.Remove(sprite);
                    NotifyPropertyChanged("SelectionCount");
                }
            }
            // Otherwise,
            else
            {
                // if neither the shift nor the control key is pressed, empty the
                // selection list,
                if ((modifiers & ModifierKeys.Shift) != ModifierKeys.Shift &&
                    (modifiers & ModifierKeys.Control) != ModifierKeys.Control)
                {
                    selected.Clear();
                    NotifyPropertyChanged("SelectionCount");
                }
                // and if the sprite actually exists,
                if (null != sprite)
                {
                    // remove if already selected and the Shift key isn't pressed
                    if (selected.Contains(sprite) &&
                        (modifiers & ModifierKeys.Shift) != ModifierKeys.Shift)
                    {
                        selected.Remove(sprite);
                    }
                    // and just add it otherwise.
                    else
                    {
                        selected.Add(sprite);
                    }
                    NotifyPropertyChanged("SelectionCount");
                }
            }
            InvalidateVisual();
        }

        // Return the topmost sprite, if any, at the given location.
        public Sprite At(int x, int y) { return At(new Point(x, y)); }
        public Sprite At(Point location)
        {
            foreach (Sprite sprite in sprites.Reverse())
            {
                if (sprite.Boundary.Contains(location))
                {
                    return sprite;
                }
            }
            return null;
        }

        // Remove all sprites.
        public void ClearAll()
        {
            sprites.Clear();
            selected.Clear();
            colliding.Clear();
            NotifyPropertyChanged("SpriteCount");
            NotifyPropertyChanged("SelectionCount");
            NotifyPropertyChanged("CollisionCount");
            spriteBin = null;
            InvalidateVisual();
        }

        // Remove selected sprites.
        public void ClearSelected()
        {
            foreach (Sprite sprite in selected)
            {
                sprites.Remove(sprite);
            }
            if (selected.Count > 0)
            {
                NotifyPropertyChanged("SpriteCount");
                NotifyPropertyChanged("SelectedCount");
            }
            selected.Clear();
            if (AutoArrange)
            {
                Rearrange();
            }
            else
            {
                CheckCollisions();
            }
        }

        // Select all sprites.
        public void SelectAll()
        {
            if (selected.Count != sprites.Count)
            {
                NotifyPropertyChanged("SelectedCount");
            }
            selected.UnionWith(sprites);
            InvalidateVisual();
        }

        // Select no sprites
        public void SelectNone()
        {
            if (selected.Count > 0)
            {
                NotifyPropertyChanged("SelectedCount");
            }
            selected.Clear();
            InvalidateVisual();
        }

        // Select unselected sprites
        public void SelectInverse()
        {
            if (selected.Count != sprites.Count - selected.Count)
            {
                NotifyPropertyChanged("SelectedCount");
            }
            selected = new HashSet<Sprite>(sprites.Except(selected));
            InvalidateVisual();
        }

        // Check all sprites for collisions with each other
        public void CheckCollisions()
        {
            // If in auto-arrange mode, this will not be neccessary.
            if (AutoArrange)
            {
                return;
            }

            // Empty the current collision list.
            int oldCount = colliding.Count;
            colliding.Clear();

            // If there is more than one sprite in the sheet, check them all.
            if (sprites.Count > 1)
            {
                // Make a list of sprites not yet checked for collisions and
                // loop through it.
                List<Sprite> toCheck = new List<Sprite>(sprites);
                for (int i = 0; i < toCheck.Count; ++i)
                {
                    for (int j = i + 1; j < toCheck.Count; ++j)
                    {
                        // Adjust collision boundaries if a drag is in progress
                        Rect boundary1 = toCheck[i].Boundary;
                        if (mouseDown && selected.Contains(toCheck[i]))
                        {
                            boundary1.X += (int)(mouseEndPosition.X - mouseStartPosition.X);
                            boundary1.Y += (int)(mouseEndPosition.Y - mouseStartPosition.Y);
                        }
                        Rect boundary2 = toCheck[j].Boundary;
                        if (mouseDown && selected.Contains(toCheck[j]))
                        {
                            boundary2.X += (int)(mouseEndPosition.X - mouseStartPosition.X);
                            boundary2.Y += (int)(mouseEndPosition.Y - mouseStartPosition.Y);
                        }

                        // Test
                        if (BoundariesCollide(boundary1, boundary2))
                        {
                            colliding.Add(toCheck[i]);
                            colliding.Add(toCheck[j]);
                        }
                    }
                }
            }

            // Notify if count has changed
            if (oldCount != colliding.Count)
            {
                NotifyPropertyChanged("CollisionCount");
            }
            InvalidateVisual();
        }

        protected static bool BoundariesCollide(Rect boundary1, Rect boundary2)
        {
            Rect intersection = Rect.Intersect(boundary1, boundary2);
            return (null != intersection && !intersection.IsEmpty &&
                    intersection.Width * intersection.Height > 0);
        }

        // Adjust canvas size to fit all sprites
        public void FitToSprites()
        {
            // Don't bother if there are no sprites.
            if (sprites.Count == 0)
            {
                return;
            }

            // Calculate a boundary containing all sprites.
            Rect boundary = Sprite.UnionBoundary(sprites);

            // Adjust sprite positions so that there is at least one sprite
            // touching each edge of the canvas.
            foreach (Sprite sprite in sprites)
            {
                sprite.X -= (int)boundary.X;
                sprite.Y -= (int)boundary.Y;
            }

            // Adjust canvas dimensions
            this.Size = boundary.Size;
            InvalidateVisual();
        }

        // Arrange sprites into a collision-free, relatively compact layout
        public void Rearrange()
        {
            // Clear current collision list
            if (CollisionCount > 0)
            {
                NotifyPropertyChanged("CollisionCount");
            }
            colliding.Clear();

            if (0 == SelectionCount)
            {
                // If there are no sprites selected, arrange all of them at once.
                spriteBin = SpriteBin.Pack(sprites, SpriteLayout);
                if (null != spriteBin)
                {
                    this.Size = spriteBin.Size;
                }

                // Don't keep the map of free space while not in auto-arrange
                // mode, since it'll soon become obsolete.
                if (!AutoArrange)
                {
                    spriteBin = null;
                }
            }
            else
            {
                // If in auto-arrange mode, arrange the selected sprites into
                // a compact layout, then arrange the rest of the sprites around
                // that layout.  This can be useful when the automatic layout
                // algorithm doesn't provide the best results for sorting all
                // the sprites in one go.
                if (AutoArrange)
                {
                    spriteBin = SpriteBin.Pack(SpriteBin.Pack(selected, SpriteLayout),
                                               sprites.Except(selected), SpriteLayout);
                    if (null != spriteBin)
                    {
                        this.Size = spriteBin.Size;
                    }
                }
                // If not in auto-arrange mode, just arrange the selected sprites
                else
                {
                    Rect boundary = Sprite.UnionBoundary(selected);
                    SpriteBin.Pack(selected, boundary.Location, SpriteLayout);
                    CheckCollisions();
                    FitToSprites();
                }
            }
            InvalidateVisual();
        }

        // Load sprites from the descendents of the given XML node.
        public void LoadXml(XmlNode node)
        {
            List<Sprite> spritesToAdd = new List<Sprite>();
            foreach (XmlNode sprite in node.SelectNodes(".//sprite"))
            {
                spritesToAdd.Add(new Sprite(sprite));
            }
            AddSprites(spritesToAdd);
        }

        // Generate an XML element containing all the sprites.
        public XmlElement ToXml(XmlDocument document, bool includeImages = true)
        {
            XmlElement sheet = document.CreateElement("sheet");
            foreach (Sprite sprite in sprites)
            {
                sheet.AppendChild(sprite.ToXml(document, includeImages));
            }
            return sheet;
        }

        // Generate a bitmap of the entire sprite sheet
        public BitmapFrame ToBitmap()
        {
            DrawingVisual drawing = new DrawingVisual();
            DrawingContext dc = drawing.RenderOpen();
            foreach (Sprite sprite in sprites)
            {
                dc.DrawImage(sprite.Source, sprite.Boundary);
            }
            dc.Close();
            RenderTargetBitmap bitmap =
                new RenderTargetBitmap((int)this.Width, (int)this.Height,
                                       96, 96, PixelFormats.Pbgra32);
            bitmap.Render(drawing);
            return BitmapFrame.Create(bitmap);
        }

        // Generate XML for only the selected sprites.
        public XmlDocument SelectedXml()
        {
            // If no sprites are selected, return null.
            if (SelectionCount == 0)
            {
                return null;
            }
            XmlDocument document = new XmlDocument();

            // If only one sprite is selected, return a document containing only
            // a sprite element
            if (SelectionCount == 1)
            {
                document.AppendChild(selected.ElementAt(0).ToXml(document));
            }

            // If multiple sprites are selected, return a partial sprite sheet.
            else
            {
                XmlElement sheet = document.CreateElement("sheet");
                foreach (Sprite sprite in selected)
                {
                    sheet.AppendChild(sprite.ToXml(document));
                }
                document.AppendChild(sheet);
            }
            return document;
        }

        // Generate a bitmap of only the selected sprites
        public BitmapFrame SelectedBitmap(Brush background = null)
        {
            if (SelectionCount == 0)
            {
                return null;
            }

            // flatten selected sprites into bitmap image
            Rect boundary = Sprite.UnionBoundary(selected);
            DrawingVisual drawing = new DrawingVisual();
            DrawingContext dc = drawing.RenderOpen();
            if (null != background)
            {
                dc.DrawRectangle(background, null,
                                 new Rect(0, 0, boundary.Width, boundary.Height));
            }
            foreach (Sprite sprite in selected)
            {
                dc.DrawImage(sprite.Source,
                             new Rect(sprite.X - boundary.X,
                                      sprite.Y - boundary.Y,
                                      sprite.Width, sprite.Height));
            }
            dc.Close();
            RenderTargetBitmap bitmap =
                new RenderTargetBitmap((int)boundary.Width, (int)boundary.Height,
                                       96, 96, PixelFormats.Pbgra32);
            bitmap.Render(drawing);
            BitmapFrame frame = BitmapFrame.Create(bitmap);
            return frame;
        }
    }
}
