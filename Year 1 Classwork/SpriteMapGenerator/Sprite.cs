/******************************************************************************
 * File:               Sprite.cs
 * Author:             Elizabeth Lowry
 * Date Created:       May 6, 2014
 * Description:        Class representing a single sprite.
 * Last Modified:      May 18, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SpriteMapGenerator
{
    // Manages a single sprite image on a sheet
    public class Sprite
    {

        // Name
        protected const string DEFAULT_NAME = "sprite";
        protected const string COPY_SUFFIX = " copy";
        protected static int autoNamedSprites = 0;
        protected string name;
        public string Name
        {
            get
            {
                if (null == name || 0 == name.Length)
                {
                    ++autoNamedSprites;
                    name = DEFAULT_NAME + " " + autoNamedSprites.ToString();
                }
                return name;
            }
            set
            {
                name = Regex.Replace(value, @"[\s-[ ]]", "").Trim();
            }
        }
        public static void ResetAutoNamedSpriteCount() { autoNamedSprites = 0; }

        // Image data source
        BitmapSource source;
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
        public int Width { get; protected set; }
        public int Height { get; protected set; }
        public Size Size
        {
            get { return new Size(Width, Height); }
            protected set
            {
                Width = (int)value.Width;
                Height = (int)value.Height;
            }
        }

        // Location
        public int X { get; set; }
        public int Y { get; set; }
        public Point Location
        {
            get { return new Point(X, Y); }
            set
            {
                X = (int)value.X;
                Y = (int)value.Y;
            }
        }
        public int Left { get { return X; } }
        public int Top { get { return Y; } }
        public int Right { get { return X + Width; } }
        public int Bottom { get { return Y + Height; } }

        // sprite boundary rectangle
        public Rect Boundary { get { return new Rect(Location, Size); } }

        // constructors
        public Sprite(int width = 0, int height = 0, string name = "")
        {
            Setup(name);
            Source = null;
            Size = new Size(width, height);
        }
        public Sprite(BitmapSource source, string name = "")
        {
            Setup(name);
            Source = source;
        }
        public Sprite(string filename, string name = "")
        {
            Setup(name.Length > 0 ? name : Path.GetFileNameWithoutExtension(filename));
            LoadFile(filename);
        }
        public Sprite(byte[] pngData, string name = "")
        {
            Setup(name);
            LoadPngData(pngData);
        }
        public Sprite(Stream pngStream, string name = "")
        {
            Setup(name);
            LoadPngStream(pngStream);
        }
        public Sprite(XmlNode node, string name = "")
        {
            Setup(name);
            LoadXml(node);
        }
        private void Setup(string name)
        {
            X = 0;
            Y = 0;
            Name = name;
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

            // load name
            if ((null == Name || Name.Length == 0) &&
                node.Attributes["name"] != null &&
                node.Attributes["name"].Value.Length > 0)
            {
                Name = node.Attributes["name"].Value;
            }

            // load image file or data
            if (node.Attributes["src"] != null &&
                node.Attributes["src"].Value.Length > 0)
            {
                LoadFile(node.Attributes["src"].Value);
                if (null == Name || Name.Length == 0)
                {
                    Name = node.Attributes["src"].Value;
                }
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

            // add name attributes
            XmlAttribute nameAttribute = document.CreateAttribute("name");
            nameAttribute.Value = Name;
            element.Attributes.Append(nameAttribute);

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

        // Add a suffix indicating that the sprite is a copy of another sprite
        // with the same name or add/increment a number to the end of the name.
        public void AdjustName()
        {
            if (Name == DEFAULT_NAME ||
                Name.Substring(Name.Length - COPY_SUFFIX.Length) == COPY_SUFFIX)
            {
                Name += " 2";
            }
            else if (Regex.IsMatch(Name, "^(" + DEFAULT_NAME + " |.*" + COPY_SUFFIX + " )[0-9]+$"))
            {
                string firstPart = Regex.Replace(Name, "[0-9]+$", "");
                int i;
                if (int.TryParse(Name.Substring(firstPart.Length), out i))
                {
                    Name = firstPart + (i + 1).ToString();
                }
            }
            else
            {
                Name += COPY_SUFFIX;
            }
        }

        // does the clipboard contain data that can be converted to a sprite?
        public static bool CanCreateFromClipboard()
        {
            if (Clipboard.ContainsText(TextDataFormat.Xaml) || Clipboard.ContainsText())
            {
                string xml = Clipboard.ContainsText(TextDataFormat.Xaml)
                             ? Clipboard.GetText(TextDataFormat.Xaml)
                             : Clipboard.GetText();
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(xml);
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
            // Try for XML first, since it'll have position data
            List<Sprite> sprites = new List<Sprite>();
            if (Clipboard.ContainsText(TextDataFormat.Xaml) || Clipboard.ContainsText())
            {
                string xml = Clipboard.ContainsText(TextDataFormat.Xaml)
                             ? Clipboard.GetText(TextDataFormat.Xaml)
                             : Clipboard.GetText();
                XmlDocument document = new XmlDocument();
                try
                {
                    document.LoadXml(xml);
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

            // If XML doesn't work, try PNG data (the default image format messes
            // with transparency)
            if (Clipboard.ContainsData("PNG"))
            {
                Object pngObject = Clipboard.GetData("PNG");
                if (pngObject is MemoryStream)
                {
                    PngBitmapDecoder decoder =
                        new PngBitmapDecoder(pngObject as MemoryStream,
                                             BitmapCreateOptions.None,
                                             BitmapCacheOption.Default);
                    foreach (BitmapFrame sprite in decoder.Frames)
                    {
                        if (null != sprite)
                        {
                            sprites.Add(new Sprite(sprite));
                        }
                    }
                    SpriteBin.Pack(sprites, SpriteBin.BinShape.Square);
                    return sprites.ToArray();
                }
            }

            // If there wasn't any PNG data, try regular image data
            if (Clipboard.ContainsImage())
            {
                return new Sprite[] { new Sprite(ClipboardDibDecoder.GetBitmapFrame()) };
            }

            // If nothing works, return an empty list.
            return new Sprite[0];
        }

        // Calculate a boundary that contains all the given sprites
        public static Rect UnionBoundary(ICollection<Sprite> members)
        {
            Rect boundary = new Rect();
            bool hasBoundary = false;
            foreach (Sprite sprite in members)
            {
                if (hasBoundary)
                {
                    boundary.Union(sprite.Boundary);
                }
                else
                {
                    boundary = sprite.Boundary;
                    hasBoundary = true;
                }
            }
            return boundary;
        }

    }
}
