using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace ProgramowanieWizualne
{
    public partial class StatsChartForm : Form
    {
        List<string> SeriesList = new List<string>();
        List<int> PointsList = new List<int>();
        InventoryForm InventoryForm = null;

        public StatsChartForm()
        {
            InitializeComponent();
        }

        public StatsChartForm(Form CallingForm, List<string> series, List<int> points)
        {
            InventoryForm = CallingForm as InventoryForm;
            SeriesList = series;
            PointsList = points;
            InitializeComponent();
        }

        private void StatsChartForm_Load(object sender, EventArgs e)
        {
            StatsChart.Titles.Add("Stats");

            for (int i = 0; i < SeriesList.Count; i++)
            {
                Series series = StatsChart.Series.Add(SeriesList[i]);
                series.Points.Add(PointsList[i]);
            }

            StatsChart.Show();
        }
    }
}
