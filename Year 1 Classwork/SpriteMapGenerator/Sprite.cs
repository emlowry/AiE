using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SpriteMapGenerator
{
    public class Sprite
    {
        BitmapSource source;

        // Accessors for sprite image data source
        public BitmapSource Source
        {
            get { return source; }
            set
            {
                if (value != source)
                {
                    source = value;
                    Size = (null == source) ? new Size(0,0)
                        : new Size(source.PixelWidth, source.PixelHeight);
                }
            }
        }

        // Size
        public Size Size { get; protected set; }
        public int Width { get { return (int)Size.Width; } }
        public int Height { get { return (int)Size.Height; } }

        // Location
        Point location;
        public Point Location
        {
            get { return location; }
            set { location = new Point((int)value.X, (int)value.Y); }
        }
        public int X
        {
            get { return (int)location.X; }
            set { location.X = value; }
        }
        public int Y
        {
            get { return (int)location.X; }
            set { location.X = value; }
        }
        public int Left { get { return X; } }
        public int Top { get { return Y; } }
        public int Right { get { return X + Width; } }
        public int Bottom { get { return Y + Height; } }

        // sprite boundary rectangle
        public Rect Boundary { get { return new Rect(Location, Size); } }

        // constructors
        private void Setup()
        {
            X = 0;
            Y = 0;
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
        public Sprite(Stream pngStream)
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
        public void LoadPngStream(Stream pngStream)
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
            LoadPngStream(new MemoryStream(pngData));
        }

        // load image and location from xml node
        public void LoadXml(XmlNode node)
        {
            int i;

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

            // load image dimensions, if no data is available
            else
            {
                Source = null;
                Size size = new Size(0,0);
                if (node.Attributes["w"] != null &&
                    int.TryParse(node.Attributes["w"].Value, out i))
                {
                    size.Width = i;
                }
                if (node.Attributes["h"] != null &&
                    int.TryParse(node.Attributes["h"].Value, out i))
                {
                    size.Height = i;
                }
                this.Size = size;
            }

            // update position
            if (node.Attributes["x"] != null &&
                int.TryParse(node.Attributes["x"].Value, out i))
            {
                X = i;
            }
            if (node.Attributes["y"] != null &&
                int.TryParse(node.Attributes["y"].Value, out i))
            {
                Y = i;
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
                MemoryStream memory = new MemoryStream();
                encoder.Save(memory);
                element.InnerText = Convert.ToBase64String(memory.ToArray());
            }

            // add size attributes
            XmlAttribute xAttribute = document.CreateAttribute("x");
            xAttribute.Value = X.ToString();
            element.Attributes.Append(xAttribute);
            XmlAttribute yAttribute = document.CreateAttribute("y");
            yAttribute.Value = Y.ToString();
            element.Attributes.Append(yAttribute);
            XmlAttribute wAttribute = document.CreateAttribute("w");
            wAttribute.Value = Width.ToString();
            element.Attributes.Append(wAttribute);
            XmlAttribute hAttribute = document.CreateAttribute("h");
            hAttribute.Value = Height.ToString();
            element.Attributes.Append(hAttribute);

            // return
            return element;
        }

        // does the clipboard contain data that can be converted to a sprite?
        public static bool CanCreateFromClipboard()
        {
            if (Clipboard.ContainsText(TextDataFormat.Xaml))
            {
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(Clipboard.GetText(TextDataFormat.Xaml));
                    if (document.SelectNodes("//sprite").Count > 0)
                    {
                        return true;
                    }
                }
                catch { }
            }
            if (Clipboard.ContainsText())
            {
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(Clipboard.GetText());
                    if (document.SelectNodes("//sprite").Count > 0)
                    {
                        return true;
                    }
                }
                catch { }
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
            List<Sprite> sprites = new List<Sprite>();
            if (Clipboard.ContainsText(TextDataFormat.Xaml))
            {
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(Clipboard.GetText(TextDataFormat.Xaml));
                    XmlNodeList nodes = document.SelectNodes("//sprite");
                    if (nodes.Count > 0)
                    {
                        foreach (XmlNode sprite in nodes)
                        {
                            sprites.Add(new Sprite(sprite));
                        }
                        return sprites.ToArray();
                    }
                }
                catch { }
            }
            if (Clipboard.ContainsText())
            {
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(Clipboard.GetText());
                    XmlNodeList nodes = document.SelectNodes("//sprite");
                    if (nodes.Count > 0)
                    {
                        foreach (XmlNode sprite in nodes)
                        {
                            sprites.Add(new Sprite(sprite));
                        }
                        return sprites.ToArray();
                    }
                }
                catch { }
            }
            if (Clipboard.ContainsData("PNG"))
            {
                Object pngObject = Clipboard.GetData("PNG");
                if (pngObject is System.IO.MemoryStream)
                {
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
                return new Sprite[] { new Sprite(ClipboardDibDecoder.GetBitmapFrame()) };
            }
            return new Sprite[0];
        }
    }
}
