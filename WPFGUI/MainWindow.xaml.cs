using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public bool Started
        {
            get { return (bool)GetValue(StartedProperty); }
            set { SetValue(StartedProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Started.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty StartedProperty =
            DependencyProperty.Register("Started", typeof(bool), typeof(MainWindow), new PropertyMetadata(false));

        public MainWindow()
        {
            InitializeComponent();
            btnStartStop.DataContext = this;
        }

        private void btnStartStop_Click(object sender, RoutedEventArgs e)
        {
            Started = !Started;
        }
    }
}
