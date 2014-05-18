/******************************************************************************
 * File:               MainWindow.xaml.cs
 * Author:             Elizabeth Lowry
 * Date Created:       May 5, 2014
 * Description:        C# backend for the main window of the WPF App.
 * Last Modified:      May 17, 2014
 * Last Modification:  Minor tweaks.
 ******************************************************************************/

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
using System.Xml;

namespace SpriteMapGenerator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Current file, if any
        Uri fileUri = null;

        public MainWindow()
        {
            InitializeComponent();
        }

        void CopySelected()
        {
            if (sheetCanvas.SelectionCount > 0)
            {
                // Save text, both regular and xaml
                DataObject data = new DataObject();
                XmlDocument document = sheetCanvas.SelectedXml();
                StringWriter writer = new StringWriter();
                document.Save(writer);
                string xml = writer.ToString();
                data.SetText(xml, TextDataFormat.Xaml);
                data.SetText(xml, TextDataFormat.Text);

                // Save image with transparency
                MemoryStream ms = new MemoryStream();
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(sheetCanvas.SelectedBitmap());
                encoder.Save(ms);
                data.SetData("PNG", ms);

                // Save image without transparency
                ms = new MemoryStream();
                data.SetImage(sheetCanvas.SelectedBitmap(Brushes.White));
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

        /**
         * Mouse Event Handlers
         */

        void CanvasMoveHandler(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                sheetCanvas.Drag(e.GetPosition(sheetCanvas));
            }
        }

        void CanvasLeftButtonUpHandler(object sender, MouseButtonEventArgs e)
        {
            sheetCanvas.EndDrag(e.GetPosition(sheetCanvas));
        }

        /**
         * File Menu Event Handlers
         */

        void CommandBindingNew_Executed(object target, ExecutedRoutedEventArgs e)
        {
            fileUri = null;
            sheetCanvas.ClearAll();
            Sprite.ResetAutoNamedSpriteCount();
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
                        Sprite.ResetAutoNamedSpriteCount();
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

        // Export the sprite sheet as either a PNG image or as XML without
        // embedded base64 PNG image data
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
                    // Export to image-free xml
                    if (dlg.FilterIndex == 1)
                    {
                        Save(uri, false);
                    }
                    // Export to PNG
                    else
                    {
                        FileStream stream = new FileStream(uri.LocalPath, FileMode.Create);
                        PngBitmapEncoder encoder = new PngBitmapEncoder();
                        encoder.Frames.Add(sheetCanvas.ToBitmap());
                        encoder.Save(stream);
                    }
                }
            }
        }

        // Add images as new sprites
        void CommandBindingImport_Executed(object target, ExecutedRoutedEventArgs e)
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
                List<Sprite> sprites = new List<Sprite>();
                foreach (string filename in dlg.FileNames)
                {
                    sprites.Add(new Sprite(filename));
                }

                // If the canvas isn't in autoarrange mode, spread out the new sprites now
                if (!sheetCanvas.AutoArrange)
                {
                    SpriteBin.Pack(sprites, sheetCanvas.SpriteLayout);
                }

                // Add sprites to sheet
                sheetCanvas.AddSprites(sprites, true);
            }
        }

        /**
         * Edit Menu Event Handlers
         */

        void CommandBindingCut_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SelectionCount > 0);
        }

        void CommandBindingCut_Executed(object target, ExecutedRoutedEventArgs e)
        {
            CopySelected();
            sheetCanvas.ClearSelected();
        }

        void CommandBindingCopy_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SelectionCount > 0);
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
            sheetCanvas.AddSprites(sprites, true, Keyboard.Modifiers & ~ModifierKeys.Control);
        }

        void CommandBindingDelete_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SelectionCount > 0);
        }

        void CommandBindingDelete_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.ClearSelected();
        }

        void CommandBindingSelectAll_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SpriteCount > 0);
        }

        void CommandBindingSelectAll_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.SelectAll();
        }

        void CommandBindingSelectNone_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SelectionCount > 0);
        }

        void CommandBindingSelectNone_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.SelectNone();
        }

        void CommandBindingSelectInverse_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SpriteCount > 0);
        }

        void CommandBindingSelectInverse_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.SelectInverse();
        }

        /**
         * Arrange Menu Event Handlers
         */

        void CommandBindingRearrange_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (sheetCanvas.SpriteCount > 0);
        }

        void CommandBindingRearrange_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.Rearrange();
        }

        void CommandBindingAutoArrange_Executed(object target, ExecutedRoutedEventArgs e)
        {
            sheetCanvas.AutoArrange = !sheetCanvas.AutoArrange;
            //autoArrangeMenuItem.IsChecked = sheetCanvas.AutoArrange;
        }

        // Scroll up or down through sprite layout options
        void CommandBindingArrangeShapeDown_Executed(object target, ExecutedRoutedEventArgs e)
        {
            switch (sheetCanvas.SpriteLayout)
            {
                case SpriteBin.BinShape.Square: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Tall; break;
                case SpriteBin.BinShape.Tall: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Wide; break;
                default: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Square; break;
            }
        }
        void CommandBindingArrangeShapeUp_Executed(object target, ExecutedRoutedEventArgs e)
        {
            switch (sheetCanvas.SpriteLayout)
            {
                case SpriteBin.BinShape.Square: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Wide; break;
                case SpriteBin.BinShape.Wide: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Tall; break;
                default: sheetCanvas.SpriteLayout = SpriteBin.BinShape.Square; break;
            }
        }
    }
}
