using System;
using System.Collections.Generic;
using System.IO;
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
//using System.Windows.Shapes;
using System.Xml;

namespace SpriteMapGenerator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Uri fileUri = null;

        public MainWindow()
        {
            InitializeComponent();
        }

        void CopySelected()
        {
            if (sheetCanvas.Selections > 0)
            {
                DataObject data = new DataObject();
                string xml = sheetCanvas.SelectedXmlText();
                data.SetText(xml, TextDataFormat.Xaml);
                data.SetText(xml, TextDataFormat.Text);
                data.SetData("PNG", sheetCanvas.SelectedPngData());
                data.SetImage(sheetCanvas.SelectedBmpImage());
                Clipboard.SetDataObject(data);
            }
        }

        void Save(Uri uri, bool includeImages = true)
        {
            if (uri != null && uri.IsFile)
            {
                XmlDocument document = new XmlDocument();
                document.AppendChild(sheetCanvas.ToXml(document, includeImages));
                document.Save(uri.LocalPath);
            }
        }

        void ShowNotImplementedMessage(ExecutedRoutedEventArgs e)
        {
            string command = ((RoutedUICommand)e.Command).Text;
            MessageBox.Show("The \"" + command + "\" command is not yet implemented!",
                            "Command not implemented", MessageBoxButton.OK, MessageBoxImage.Exclamation);
        }

        /**
         * File Menu Event Handlers
         */

        void CommandBindingNew_Executed(object target, ExecutedRoutedEventArgs e)
        {
            fileUri = null;
            sheetCanvas.ClearAll();
            this.Title = "new - Sprite Map Generator";
        }

        void CommandBindingOpen_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Title = "Open a sprite map file";
            dlg.Filter = "Sprite map|*.smap|All Files|*.*"; // Filter files by extension

            // Show open file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results 
            if (result == true)
            {
                // grab the file name of the sprite map
                string filename = dlg.FileName;

                // check validity
                Uri uri = new Uri(filename);
                if (uri.IsFile)
                {
                    // load document
                    XmlDocument file = new XmlDocument();
                    file.Load(filename);
                    XmlNode sheet = file.SelectSingleNode("/sheet");
                    if (null != sheet)
                    {
                        // load sprites
                        sheetCanvas.ClearAll();
                        sheetCanvas.LoadXml(sheet);

                        // update window title
                        this.Title = Path.GetFileName(uri.LocalPath) + " - Sprite Map Generator";
                        fileUri = uri;
                    }
                }
            }
        }

        void CommandBindingSave_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (fileUri != null && fileUri.IsFile);
        }

        void CommandBindingSave_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Save(fileUri);
        }

        void CommandBindingSaveAs_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.Title = "Save sprite map file";
            if (null == fileUri)
            {
                dlg.FileName = "new"; // Default file name 
                dlg.DefaultExt = ".smap"; // Default file extension 
            }
            else
            {
                dlg.FileName = Path.GetFileNameWithoutExtension(fileUri.LocalPath);
                dlg.DefaultExt = Path.GetExtension(fileUri.LocalPath);
            }
            dlg.Filter = "Sprite map|*.smap|All Files|*.*"; // Filter files by extension

            // Show save file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results 
            if (result == true)
            {
                Uri uri = new Uri(dlg.FileName);
                if (uri != null && uri.IsFile)
                {
                    Save(uri);
                    fileUri = uri;
                    this.Title = Path.GetFileName(uri.LocalPath) + " - Sprite Map Generator";
                }
            }
        }

        void CommandBindingExport_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.Title = "Export sprite map to another format";
            if (null == fileUri)
            {
                dlg.FileName = "new"; // Default file name 
                dlg.DefaultExt = ".xml"; // Default file extension 
            }
            else
            {
                dlg.FileName = Path.GetFileNameWithoutExtension(fileUri.LocalPath);
                dlg.DefaultExt = ".xml"; // Default file extension 
            }
            dlg.Filter = "Sprite map XML|*.xml|Portable Network Graphics|*.png"; // Filter files by extension

            // Show save file dialog box 
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results 
            if (result == true)
            {
                Uri uri = new Uri(dlg.FileName);
                if (uri != null && uri.IsFile)
                {
                    if (dlg.FilterIndex == 1)
                    {
                        Save(uri, false);
                    }
                    else
                    {
                        using (FileStream stream = new FileStream(uri.LocalPath, FileMode.Create))
                        {
                            PngBitmapEncoder encoder = new PngBitmapEncoder();
                            encoder.Frames.Add(sheetCanvas.ToBitmap());
                            encoder.Save(stream);
                        }
                    }
                }
            }
        }

        /**
         * Edit Menu Event Handlers
         */

        void CommandBindingPlaceImage_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Multiselect = true;
            dlg.Title = "Add images to sprite sheet";
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
                // grab the file name of each image and load as a sprite
                foreach (string filename in dlg.FileNames)
                {
                    sheetCanvas.AddSprite(new Sprite(filename));
                }
            }
        }

        void CommandBindingCut_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.Selections > 0);
        }

        void CommandBindingCut_Executed(object target, ExecutedRoutedEventArgs e)
        {
            CopySelected();
            sheetCanvas.ClearSelected();
        }

        void CommandBindingCopy_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.Selections > 0);
        }

        void CommandBindingCopy_Executed(object target, ExecutedRoutedEventArgs e)
        {
            CopySelected();
        }

        void CommandBindingPaste_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Sprite.CanCreateFromClipboard();
        }

        void CommandBindingPaste_Executed(object target, ExecutedRoutedEventArgs e)
        {
            Sprite[] sprites = Sprite.CreateFromClipboard();
            foreach (Sprite sprite in sprites)
            {
                if (null != sprite)
                {
                    sheetCanvas.AddSprite(sprite);
                }
            }
        }

        void CommandBindingDelete_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.Selections > 0);
        }

        void CommandBindingDelete_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.ClearSelected();
        }

        void CommandBindingSelectAll_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.Sprites > 0);
        }

        void CommandBindingSelectAll_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.SelectAll();
        }
    }
}
