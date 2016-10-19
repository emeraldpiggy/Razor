using System.Windows;

namespace RazorUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly RazorBridge.RazorBridgeWrapper _razorBridge;
        public MainWindow()
        {
            InitializeComponent();
            _razorBridge = new RazorBridge.RazorBridgeWrapper();

        }

        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            var scheme = GetScheme();

            Results.Text = !string.IsNullOrEmpty(scheme) ? scheme : "Wrong Uri";
        }

        public string GetScheme()
        {
            return _razorBridge.Parse(UriText.Text);
        }
    }
}
