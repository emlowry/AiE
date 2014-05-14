using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SpriteMapGenerator
{
    class SheetCanvas : Canvas, INotifyPropertyChanged
    {
        static Pen normalOutline =
            new Pen(AnimatedPattern.Create(Colors.Lime, Colors.Yellow), 1);
        static Pen selectedOutline =
            new Pen(AnimatedPattern.Create(Colors.Blue, Colors.Aqua), 1);
        static Pen collidingOutline =
            new Pen(AnimatedPattern.Create(Colors.Red, Colors.Magenta), 1);

        HashSet<Sprite> selected = new HashSet<Sprite>();
        HashSet<Sprite> colliding = new HashSet<Sprite>();
        HashSet<Sprite> sprites = new HashSet<Sprite>();

        public int Collisions { get { return colliding.Count; } }
        public int Selections { get { return selected.Count; } }
        public int Sprites { get { return sprites.Count; } }
        public Size Size
        {
            get { return new Size(Width, Height); }
            set
            {
                Width = value.Width;
                Height = value.Height;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        protected SpriteBin.BinShape shape = SpriteBin.BinShape.Square;
        public SpriteBin.BinShape Shape
        {
            get { return shape; }
            set
            {
                if (value != shape)
                {
                    shape = value;
                    NotifyPropertyChanged("ArrangeSquare");
                    NotifyPropertyChanged("ArrangeTall");
                    NotifyPropertyChanged("ArrangeWide");
                }
            }
        }
        public bool ArrangeSquare
        {
            get { return (SpriteBin.BinShape.Square == Shape); }
            set { if (value) Shape = SpriteBin.BinShape.Square; }
        }
        public bool ArrangeTall
        {
            get { return (SpriteBin.BinShape.Tall == Shape); }
            set { if (value) Shape = SpriteBin.BinShape.Tall; }
        }
        public bool ArrangeWide
        {
            get { return (SpriteBin.BinShape.Wide == Shape); }
            set { if (value) Shape = SpriteBin.BinShape.Wide; }
        }

        protected SpriteBin spriteBin = null;
        protected bool autoArrange = false;
        public bool AutoArrange
        {
            get { return autoArrange; }
            set
            {
                if (value != autoArrange)
                {
                    autoArrange = value;
                    NotifyPropertyChanged("AutoArrange");
                    if (value)
                    {
                        Rearrange();
                    }
                    else
                    {
                        spriteBin = null;
                    }
                }
            }
        }

        protected override void OnRender(DrawingContext dc)
        {
            foreach (Sprite sprite in sprites)
            {
                dc.DrawImage(sprite.Source, sprite.Boundary);
            }
            foreach (Sprite sprite in sprites)
            {
                Rect border = sprite.Boundary;
                border.X += 0.5;
                border.Y += 0.5;
                border.Height -= 1;
                border.Width -= 1;
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

        public void AddSprite(Sprite sprite)
        {
            if (AutoArrange)
            {
                spriteBin = SpriteBin.Pack(spriteBin, sprite, Shape);
            }
            else
            {
                foreach (Sprite otherSprite in sprites)
                {
                    if (sprite.IntersectsWith(otherSprite))
                    {
                        colliding.Add(sprite);
                        colliding.Add(otherSprite);
                    }
                }
            }
            while (sprites.Count(otherSprite => (otherSprite.Name == sprite.Name)) > 0)
            {
                sprite.AdjustName();
            }
            sprites.Add(sprite);
            this.Width = (sprites.Count == 1) ? sprite.Right
                            : Math.Max(this.Width, sprite.Right);
            this.Height = (sprites.Count == 1) ? sprite.Bottom
                            : Math.Max(this.Height, sprite.Bottom);
            InvalidateVisual();
        }

        public void ClearAll()
        {
            sprites.Clear();
            selected.Clear();
            colliding.Clear();
            spriteBin = null;
            InvalidateVisual();
        }

        public void ClearSelected()
        {
            foreach (Sprite sprite in selected)
            {
                sprites.Remove(sprite);
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

        public void SelectAll()
        {
            selected.UnionWith(sprites);
            InvalidateVisual();
        }

        public void SelectNone()
        {
            selected.Clear();
            InvalidateVisual();
        }

        public void CheckCollisions()
        {
            colliding.Clear();
            if (sprites.Count > 1)
            {
                List<Sprite> toCheck = new List<Sprite>(sprites);
                for (int i = 0; i < toCheck.Count; ++i)
                {
                    for (int j = i + 1; j < toCheck.Count; ++j)
                    {
                        if (toCheck[i].IntersectsWith(toCheck[j]))
                        {
                            colliding.Add(toCheck[i]);
                            colliding.Add(toCheck[j]);
                        }
                    }
                }
            }
            InvalidateVisual();
        }

        public void FitToSprites()
        {
            if (sprites.Count == 0)
            {
                return;
            }
            Rect boundary = Sprite.UnionBoundary(sprites);
            foreach (Sprite sprite in sprites)
            {
                sprite.X -= (int)boundary.X;
                sprite.Y -= (int)boundary.Y;
            }
            this.Width = boundary.Width;
            this.Height = boundary.Height;
            InvalidateVisual();
        }

        public void Rearrange()
        {
            colliding.Clear();
            if (0 == Selections)
            {
                spriteBin = SpriteBin.Pack(sprites, Shape);
                if (null != spriteBin)
                {
                    this.Size = spriteBin.Size;
                }
            }
            else
            {
                if (AutoArrange)
                {
                    spriteBin = SpriteBin.Pack(SpriteBin.Pack(selected, Shape),
                                               sprites.Except(selected), Shape);
                    if (null != spriteBin)
                    {
                        this.Size = spriteBin.Size;
                    }
                }
                else
                {
                    Rect boundary = Sprite.UnionBoundary(selected);
                    SpriteBin.Pack(selected, boundary.Location, Shape);
                    CheckCollisions();
                    FitToSprites();
                }
            }
            InvalidateVisual();
        }

        public void LoadXml(XmlNode node)
        {
            foreach (XmlNode sprite in node.SelectNodes("./sprite"))
            {
                AddSprite(new Sprite(sprite));
            }
        }

        public XmlElement ToXml(XmlDocument document, bool includeImages = true)
        {
            XmlElement sheet = document.CreateElement("sheet");
            foreach (Sprite sprite in sprites)
            {
                sheet.AppendChild(sprite.ToXml(document, includeImages));
            }
            return sheet;
        }

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

        public string SelectedXmlText()
        {
            if (Selections == 0)
            {
                return "";
            }
            XmlDocument document = new XmlDocument();
            if (Selections == 1)
            {
                document.AppendChild(sprites.ElementAt(0).ToXml(document));
            }
            else
            {
                XmlElement sheet = document.CreateElement("sheet");
                foreach (Sprite sprite in selected)
                {
                    sheet.AppendChild(sprite.ToXml(document));
                }
                document.AppendChild(sheet);
            }
            return document.OuterXml;
        }

        public MemoryStream SelectedPngData(MemoryStream ms = null)
        {
            if (Selections == 0)
            {
                return ms;
            }
            if (null == ms)
            {
                ms = new MemoryStream();
            }

            // flatten selected sprites into bitmap image
            Rect boundary = Sprite.UnionBoundary(selected);
            DrawingVisual drawing = new DrawingVisual();
            DrawingContext dc = drawing.RenderOpen();
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

            // copy image to data object
            PngBitmapEncoder encoder = new PngBitmapEncoder();
            encoder.Frames.Add(frame);
            encoder.Save(ms);
            return ms;
        }

        public BitmapFrame SelectedBmpImage()
        {
            if (Selections == 0)
            {
                return null;
            }

            // flatten selected sprites into bitmap image
            Rect boundary = Sprite.UnionBoundary(selected);
            DrawingVisual drawing = new DrawingVisual();
            DrawingContext dc = drawing.RenderOpen();
            dc.DrawRectangle(Brushes.White, null,
                             new Rect(0, 0, boundary.Width, boundary.Height));
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
            return BitmapFrame.Create(bitmap);
        }
    }
}
