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

namespace SpriteMapGenerator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string filename = null;

        public MainWindow()
        {
            InitializeComponent();
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
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingOpen_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingSave_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = (filename != null && filename.Length > 0);
        }

        void CommandBindingSave_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingSaveAs_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingExport_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        /**
         * Edit Menu Event Handlers
         */

        void CommandBindingPlaceImage_Executed(object target, ExecutedRoutedEventArgs e)
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
                sheetCanvas.AddSprite(new Sprite(filename));
            }
        }

        void CommandBindingCut_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            //TODO
        }

        void CommandBindingCut_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingCopy_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            //TODO
        }

        void CommandBindingCopy_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
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
            //TODO
        }

        void CommandBindingDelete_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }

        void CommandBindingSelectAll_CanExecute(object target, CanExecuteRoutedEventArgs e)
        {
            //TODO
        }

        void CommandBindingSelectAll_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
        }
    }
}
