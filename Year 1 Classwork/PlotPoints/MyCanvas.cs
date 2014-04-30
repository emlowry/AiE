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
        BitmapImage background = null;
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
            if (source == null || source.SelectSingleNode("/canvas") == null)
            {
                return;
            }
            ClearCircles();
            ClearImage();
            XmlNode canvas = source.SelectSingleNode("/canvas");
            if (canvas.Attributes["background"] != null)
            {
                LoadImage(canvas.Attributes["background"].Value);
            }
            foreach (XmlNode circleNode in canvas.SelectNodes("./circle"))
            {
                EllipseGeometry circle = new EllipseGeometry();
                Point center = circle.Center;
                double d;
                if (circleNode.Attributes["x"] != null &&
                    double.TryParse(circleNode.Attributes["x"].ToString(), out d))
                {
                    center.X = d;
                }
                if (circleNode.Attributes["y"] != null &&
                    double.TryParse(circleNode.Attributes["y"].ToString(), out d))
                {
                    center.Y = d;
                }
                circle.Center = center;
                if (circleNode.Attributes["r"] != null &&
                    double.TryParse(circleNode.Attributes["r"].ToString(), out d))
                {
                    circle.RadiusX = d;
                    circle.RadiusY = d;
                }
                circles.Add(circle);
            }
            this.InvalidateVisual();
        }

        public XmlDocument WriteXml(XmlDocument destination = null)
        {
            if (destination == null)
            {
                destination = new XmlDocument();
            }
            XmlNode canvas = destination.CreateElement("canvas");
            if (background != null)
            {
                XmlAttribute backgroundAttribute = destination.CreateAttribute("background");
                backgroundAttribute.Value = background.UriSource.ToString();
                canvas.Attributes.Append(backgroundAttribute);
            }
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
            destination.AppendChild(canvas);
            return destination;
        }
    }
}
