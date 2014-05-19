/******************************************************************************
 * File:               MainWindow_FileMenu.cs
 * Author:             Elizabeth Lowry
 * Date Created:       May 19, 2014
 * Description:        Command bindings for File menu items.
 * Last Modified:      May 19, 2014
 * Last Modification:  Creation.
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
    public partial class MainWindow
    {
        // Current file, if any
        Uri fileUri = null;

        // Save to a file
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

    }
}