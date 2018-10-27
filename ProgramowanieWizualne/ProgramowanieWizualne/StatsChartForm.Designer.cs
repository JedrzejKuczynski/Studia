namespace ProgramowanieWizualne
{
    partial class StatsChartForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            this.StatsChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            ((System.ComponentModel.ISupportInitialize)(this.StatsChart)).BeginInit();
            this.SuspendLayout();
            // 
            // StatsChart
            // 
            chartArea1.AxisX.ScaleBreakStyle.Enabled = true;
            chartArea1.Name = "ChartArea1";
            this.StatsChart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.StatsChart.Legends.Add(legend1);
            this.StatsChart.Location = new System.Drawing.Point(12, 12);
            this.StatsChart.Name = "StatsChart";
            this.StatsChart.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StatsChart.Size = new System.Drawing.Size(474, 376);
            this.StatsChart.TabIndex = 0;
            this.StatsChart.Text = "Stats";
            // 
            // StatsChartForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(498, 400);
            this.Controls.Add(this.StatsChart);
            this.Name = "StatsChartForm";
            this.Text = "StatsChartForm";
            this.Load += new System.EventHandler(this.StatsChartForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.StatsChart)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart StatsChart;
    }
}