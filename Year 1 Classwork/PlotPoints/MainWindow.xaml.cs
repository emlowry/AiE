using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;

namespace PlotPoints
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool loadedFile = false;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MenuItemNew_Click(object sender, RoutedEventArgs e)
        {
            canvas1.ClearCircles();
            canvas1.ClearImage();
            this.Title = "New File";
            loadedFile = false;
        }

        private void MenuItemOpen_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Title = "Load canvas contents from xml";
            dlg.Filter = "Canvas XML|*.xml|All Files|*.*"; // Filter files by extension

            // Show open file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results 
            if (result == true)
            {
                // grab the file name of the image 
                string filename = dlg.FileName;

                // check validity
                Uri uri = new Uri(filename);
                if (uri.IsFile)
                {
                    // load background and circles from canvas
                    XmlDocument file = new XmlDocument();
                    file.Load(filename);
                    canvas1.ReadXml(file);

                    // update window title
                    this.Title = System.IO.Path.GetFileName(uri.LocalPath);
                    loadedFile = true;
                }
            }
        }

        private void MenuItemSave_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.Title = "Save canvas contents to xml";
            if (loadedFile)
            {
                dlg.FileName = this.Title;
            }
            else
            {
                dlg.FileName = "canvas"; // Default file name 
                dlg.DefaultExt = ".xml"; // Default file extension 
            }
            dlg.Filter = "Canvas XML|*.xml|All Files|*.*"; // Filter files by extension

            // Show open file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results 
            if (result == true)
            {
                // grab the file name of the image 
                string filename = dlg.FileName;

                // write canvas information to file
                XmlDocument document = canvas1.WriteXml();
                document.Save(filename);

                // update window title
                this.Title = filename;
                loadedFile = true;
            }
        }

        private void MenuItemAddBackground_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Title = "Load a background image";
            dlg.Filter = "All Images|*.bmp;*.gif;*.jpeg;*.jpg;*.png;*.tiff;*.tif|" +
                         "All Files|*.*|" +
                         "Windows Bitmap|*.bmp|" +
                         "Graphics Interchange Format|*.gif|" +
                         "Joint Photographics Experts Group|*.jpeg;*.jpg|" +
                         "Portable Network Graphics|*.png|" +
                         "Tagged Image File Format|*.tiff;*.tif"; // Filter files by extension 

            // Show open file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results 
            if (result == true)
            {
                // grab the file name of the image 
                string filename = dlg.FileName;

                // and load the image 
                canvas1.LoadImage(filename);
            }
        }

        private void MenuItemClearBackground_Click(object sender, RoutedEventArgs e)
        {
            canvas1.ClearImage();
        }

        private void MenuItemEraseCircles_Click(object sender, RoutedEventArgs e)
        {
            canvas1.ClearCircles();
        }

    }
}
