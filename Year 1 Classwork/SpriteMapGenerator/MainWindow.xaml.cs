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
            //TODO
            ShowNotImplementedMessage(e);
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
            if (System.Windows.Clipboard.ContainsImage())
            {
                e.CanExecute = true;
            }
            else if (System.Windows.Clipboard.ContainsText(TextDataFormat.Xaml))
            {
                //string xaml = System.Windows.Clipboard.GetText(TextDataFormat.Xaml);
                e.CanExecute = false/*TODO check if xaml contains sprite data*/;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        void CommandBindingPaste_Executed(object target, ExecutedRoutedEventArgs e)
        {
            //TODO
            ShowNotImplementedMessage(e);
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
