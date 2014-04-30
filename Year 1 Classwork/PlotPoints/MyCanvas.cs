using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;

namespace PlotPoints
{
    class MyCanvas : Canvas
    {
        BitmapSource background = null;
        List<EllipseGeometry> circles = new List<EllipseGeometry>();
        EllipseGeometry inProgress = null;
        Pen pen = new Pen(Brushes.Transparent,0);

        public void ClearCircles()
        {
            circles.Clear();
            inProgress = null;
            this.InvalidateVisual();
        }

        public void ClearImage()
        {
            background = null;
            this.InvalidateVisual();
        }

        public void LoadImage(string filename)
        {
            background = new BitmapImage(new Uri(filename));
            this.InvalidateVisual();
        }

        protected override void OnRender(DrawingContext dc)
        {
            dc.DrawRectangle(this.Background, pen, new Rect(0, 0, this.ActualWidth, this.ActualHeight));
            if (background != null)
            {
                dc.DrawImage(background, new Rect(0, 0, background.PixelWidth,
                                                  background.PixelHeight));
            }
            foreach (EllipseGeometry circle in circles)
            {
                dc.DrawEllipse(Brushes.Black, pen, circle.Center, circle.RadiusX, circle.RadiusY);
            }
            if (inProgress != null)
            {
                dc.DrawEllipse(Brushes.Black, pen, inProgress.Center, inProgress.RadiusX, inProgress.RadiusY);
            }
        }

        protected override void OnMouseLeftButtonDown(System.Windows.Input.MouseButtonEventArgs e)
        {
            if (inProgress != null)
            {
                OnMouseLeftButtonUp(e);
            }
            else
            {
                inProgress = new EllipseGeometry(e.GetPosition(this), 0, 0);
                this.InvalidateVisual();
            }
        }
        protected override void OnMouseMove(System.Windows.Input.MouseEventArgs e)
        {
            if (inProgress != null)
            {
                Vector displacement = e.GetPosition(this) - inProgress.Center;
                inProgress.RadiusX = displacement.Length;
                inProgress.RadiusY = displacement.Length;
                this.InvalidateVisual();
            }
        }
        protected override void OnMouseLeftButtonUp(System.Windows.Input.MouseButtonEventArgs e)
        {
            if (inProgress != null)
            {
                circles.Add(inProgress);
                inProgress = null;
            }
        }

        public void ReadXml(XmlDocument source)
        {
            // If there's no canvas data to read, don't bother
            if (source == null || source.SelectSingleNode("/canvas") == null)
            {
                return;
            }
            XmlNode canvas = source.SelectSingleNode("/canvas");

            // Erase the current canvas contents
            ClearCircles();
            ClearImage();

            // Read all the circle data
            foreach (XmlNode circleNode in canvas.SelectNodes("./circle"))
            {
                EllipseGeometry circle = new EllipseGeometry();
                Point center = circle.Center;
                double d;
                if (circleNode.Attributes["x"] != null &&
                    double.TryParse(circleNode.Attributes["x"].Value, out d))
                {
                    center.X = d;
                }
                if (circleNode.Attributes["y"] != null &&
                    double.TryParse(circleNode.Attributes["y"].Value, out d))
                {
                    center.Y = d;
                }
                circle.Center = center;
                if (circleNode.Attributes["r"] != null &&
                    double.TryParse(circleNode.Attributes["r"].Value, out d))
                {
                    circle.RadiusX = d;
                    circle.RadiusY = d;
                }
                circles.Add(circle);
            }

            // Read the background image data
            XmlNode backgroundNode = canvas.SelectSingleNode("./background");
            if (backgroundNode != null)
            {
                System.IO.MemoryStream memory = new System.IO.MemoryStream(Convert.FromBase64String(backgroundNode.InnerText));
                PngBitmapDecoder decoder = new PngBitmapDecoder(memory,BitmapCreateOptions.None,BitmapCacheOption.Default);
                if (decoder.Frames.Count > 0 && decoder.Frames[0] != null)
                {
                    background = decoder.Frames[0];
                }
            }

            // make sure canvas updates
            this.InvalidateVisual();
        }

        public XmlDocument WriteXml(XmlDocument destination = null)
        {
            // If no document is passed in, create one
            if (destination == null)
            {
                destination = new XmlDocument();
            }

            // create root node
            XmlNode canvas = destination.CreateElement("canvas");

            // create circle nodes
            foreach (EllipseGeometry circle in circles)
            {
                XmlElement circleElement = destination.CreateElement("circle");
                XmlAttribute xAttribute = destination.CreateAttribute("x");
                xAttribute.Value = circle.Center.X.ToString();
                circleElement.Attributes.Append(xAttribute);
                XmlAttribute yAttribute = destination.CreateAttribute("y");
                yAttribute.Value = circle.Center.Y.ToString();
                circleElement.Attributes.Append(yAttribute);
                XmlAttribute rAttribute = destination.CreateAttribute("r");
                rAttribute.Value = circle.RadiusX.ToString();
                circleElement.Attributes.Append(rAttribute);
                canvas.AppendChild(circleElement);
            }

            // create background image node
            if (background != null)
            {
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(background));
                System.IO.MemoryStream memory = new System.IO.MemoryStream();
                encoder.Save(memory);
                XmlElement backgroundElement = destination.CreateElement("background");
                backgroundElement.InnerText = Convert.ToBase64String(memory.ToArray());
                canvas.AppendChild(backgroundElement);
            }

            // add root node to document and return
            destination.AppendChild(canvas);
            return destination;
        }
    }
}
