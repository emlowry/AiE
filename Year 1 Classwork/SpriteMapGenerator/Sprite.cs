using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SpriteMapGenerator
{
    public class Sprite : Canvas
    {
        BitmapSource source;
        //Rect sourceSlice = new Rect(0,0,0,0);

        // Accessors for sprite image data source
        public BitmapSource Source
        {
            get { return source; }
            set
            {
                if (value != source)
                {
                    /*if (value == null)
                    {
                        sourceSlice = new Rect(0, 0, 0, 0);
                    }
                    else if (sourceSlice.Right > value.PixelWidth ||
                             sourceSlice.Bottom > value.PixelHeight)
                    {
                        Point shift = new Point( sourceSlice.Right - value.PixelWidth,
                                                 sourceSlice.Bottom - value.PixelHeight );
                        sourceSlice = new Rect(Math.Max(sourceSlice.Left - shift.X, 0),
                                               Math.Max(sourceSlice.Top - shift.Y, 0),
                                               value.PixelWidth,
                                               value.PixelHeight);
                    }/**/
                    source = value;
                    Width = (null == source) ? 0 : source.PixelWidth;
                    Height = (null == source) ? 0 : source.PixelHeight;
                    InvalidateVisual();
                }
            }
        }

        /*// Accessors for source slice dimensions
        public Rect SourceSlice
        {
            get { return sourceSlice; }
            set
            {
                if (null == source)
                {
                    return;
                }
                Rect correctedValue = new Rect(Math.Max(Math.Round(value.Left), 0),
                                               Math.Max(Math.Round(value.Top), 0),
                                               Math.Min(Math.Round(value.Right), source.PixelWidth),
                                               Math.Min(Math.Round(value.Bottom), source.PixelHeight));
                if (correctedValue != sourceSlice)
                {
                    sourceSlice = correctedValue;
                    InvalidateVisual();
                }
            }
        }/**/

        // Location
        public double Left
        {
            get { return Canvas.GetLeft(this); }
            set
            {
                if (value != Canvas.GetLeft(this))
                {
                    Canvas.SetLeft(this, value);
                    InvalidateVisual();
                }
            }
        }
        public double Top
        {
            get { return Canvas.GetTop(this); }
            set
            {
                if (value != Canvas.GetTop(this))
                {
                    Canvas.SetTop(this, value);
                    InvalidateVisual();
                }
            }
        }
        public Rect Boundary
        {
            get { return new Rect(Left, Top, Left + Width, Top + Height); }
        }

        // constructors
        private void Setup()
        {
            Left = 0;
            Top = 0;
        }
        public Sprite()
        {
            Setup();
            Source = null;
        }
        public Sprite(BitmapSource source)
        {
            Setup();
            Source = source;
        }
        public Sprite(string filename)
        {
            Setup();
            LoadFile(filename);
        }
        public Sprite(byte[] pngData)
        {
            Setup();
            LoadPngData(pngData);
        }
        public Sprite(System.IO.Stream pngStream)
        {
            Setup();
            LoadPngStream(pngStream);
        }
        public Sprite(XmlNode node)
        {
            Setup();
            LoadXml(node);
        }

        // Does this sprite collide with another?
        public bool IntersectsWith(Sprite sprite)
        {
            return Boundary.IntersectsWith(sprite.Boundary);
        }

        // load image from file
        public void LoadFile(string filename)
        {
            Source = new BitmapImage(new Uri(filename));
        }

        // load image from a stream containing PNG data
        public void LoadPngStream(System.IO.Stream pngStream)
        {
            PngBitmapDecoder decoder =
                new PngBitmapDecoder(pngStream,
                                     BitmapCreateOptions.None,
                                     BitmapCacheOption.Default);
            if (decoder.Frames.Count > 0 && decoder.Frames[0] != null)
            {
                Source = decoder.Frames[0];
            }
        }

        // load image from raw PNG bytes
        public void LoadPngData(byte[] pngData)
        {
            if (null == pngData)
            {
                Source = null;
                return;
            }
            LoadPngStream(new System.IO.MemoryStream(pngData));
        }

        // load image and location from xml node
        public void LoadXml(XmlNode node)
        {
            // load image file or data
            if (node.Attributes["src"] != null &&
                node.Attributes["src"].Value.Length > 0)
            {
                LoadFile(node.Attributes["src"].Value);
            }
            else if (node.InnerText.Length > 0)
            {
                LoadPngData(Convert.FromBase64String(node.InnerText));
            }
            else
            {
                Source = null;
            }

            // update position
            double d;
            if (node.Attributes["x"] != null &&
                double.TryParse(node.Attributes["x"].Value, out d))
            {
                Left = d;
            }
            if (node.Attributes["y"] != null &&
                double.TryParse(node.Attributes["y"].Value, out d))
            {
                Top = d;
            }
        }

        // create a sprite xml node
        public XmlElement ToXml(XmlDocument document, bool includeImage = true)
        {
            // create the node
            if (null == document)
            {
                document = new XmlDocument();
            }
            XmlElement element = document.CreateElement("sprite");

            // add image data
            if (includeImage && source != null)
            {
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(source));
                System.IO.MemoryStream memory = new System.IO.MemoryStream();
                encoder.Save(memory);
                element.InnerText = Convert.ToBase64String(memory.ToArray());
            }

            // add size attributes
            XmlAttribute xAttribute = document.CreateAttribute("x");
            xAttribute.Value = Left.ToString();
            element.AppendChild(xAttribute);
            XmlAttribute yAttribute = document.CreateAttribute("y");
            yAttribute.Value = Top.ToString();
            element.AppendChild(yAttribute);
            XmlAttribute wAttribute = document.CreateAttribute("w");
            wAttribute.Value = Width.ToString();
            element.AppendChild(xAttribute);
            XmlAttribute hAttribute = document.CreateAttribute("h");
            hAttribute.Value = Height.ToString();
            element.AppendChild(hAttribute);

            // return
            return element;
        }

        // draw the sprite
        protected override void OnRender(DrawingContext dc)
        {
            if (source != null)
            {
                dc.DrawImage(this.Source, new Rect(0, 0, Width, Height));
            }
        }

        // does the clipboard contain data that can be converted to a sprite?
        public static bool CanCreateFromClipboard()
        {
            if (Clipboard.ContainsText(TextDataFormat.Xaml))
            {
                //TODO implement check for valid xml data
            }
            if (Clipboard.ContainsData("PNG") || Clipboard.ContainsImage())
            {
                return true;
            }
            return false;
        }

        // return a sprite created from data on the clipboad
        public static Sprite[] CreateFromClipboard()
        {
            if (Clipboard.ContainsText(TextDataFormat.Xaml))
            {
                //TODO read xml data from clipboard
            }
            if (Clipboard.ContainsData("PNG"))
            {
                Object pngObject = Clipboard.GetData("PNG");
                if (pngObject is System.IO.MemoryStream)
                {
                    List<Sprite> sprites = new List<Sprite>();
                    PngBitmapDecoder decoder =
                        new PngBitmapDecoder(pngObject as System.IO.MemoryStream,
                                             BitmapCreateOptions.None,
                                             BitmapCacheOption.Default);
                    foreach (BitmapFrame sprite in decoder.Frames)
                    {
                        if (null != sprite)
                        {
                            sprites.Add(new Sprite(sprite));
                        }
                    }
                    return sprites.ToArray();
                }
            }
            if (Clipboard.ContainsImage())
            {
                return new Sprite[]{new Sprite(ClipboardDibDecoder.GetBitmapFrame())};
            }
            return new Sprite[0];
        }
    }
}
