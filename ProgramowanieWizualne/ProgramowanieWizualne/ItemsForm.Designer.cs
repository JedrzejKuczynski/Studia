namespace ProgramowanieWizualne
{
    partial class ItemsForm
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
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.NameLabel = new System.Windows.Forms.Label();
            this.NameBox = new System.Windows.Forms.TextBox();
            this.TypeBox = new System.Windows.Forms.TextBox();
            this.TypeLabel = new System.Windows.Forms.Label();
            this.DescriptionBox = new System.Windows.Forms.TextBox();
            this.DescriptionLabel = new System.Windows.Forms.Label();
            this.RequirementsCheckedListBox = new System.Windows.Forms.CheckedListBox();
            this.RequirementsLabel = new System.Windows.Forms.Label();
            this.MightBox = new System.Windows.Forms.TextBox();
            this.MightLabel = new System.Windows.Forms.Label();
            this.DefenceBox = new System.Windows.Forms.TextBox();
            this.DefenceLabel = new System.Windows.Forms.Label();
            this.WeightBox = new System.Windows.Forms.TextBox();
            this.WeightLabel = new System.Windows.Forms.Label();
            this.ItemWeightBox = new System.Windows.Forms.TextBox();
            this.ItemWeightLabel = new System.Windows.Forms.Label();
            this.PropertiesBox = new System.Windows.Forms.RichTextBox();
            this.PropertiesLabel = new System.Windows.Forms.Label();
            this.AddButton = new System.Windows.Forms.Button();
            this.EditButton = new System.Windows.Forms.Button();
            this.ItemsListBox = new System.Windows.Forms.ListBox();
            this.ItemsLabel = new System.Windows.Forms.Label();
            this.SaveButton = new System.Windows.Forms.Button();
            this.LoadButton = new System.Windows.Forms.Button();
            this.DeleteButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Location = new System.Drawing.Point(57, 29);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(35, 13);
            this.NameLabel.TabIndex = 1;
            this.NameLabel.Text = "Name";
            // 
            // NameBox
            // 
            this.NameBox.Location = new System.Drawing.Point(98, 26);
            this.NameBox.Name = "NameBox";
            this.NameBox.Size = new System.Drawing.Size(100, 20);
            this.NameBox.TabIndex = 2;
            // 
            // TypeBox
            // 
            this.TypeBox.Location = new System.Drawing.Point(98, 52);
            this.TypeBox.Name = "TypeBox";
            this.TypeBox.Size = new System.Drawing.Size(100, 20);
            this.TypeBox.TabIndex = 3;
            // 
            // TypeLabel
            // 
            this.TypeLabel.AutoSize = true;
            this.TypeLabel.Location = new System.Drawing.Point(61, 55);
            this.TypeLabel.Name = "TypeLabel";
            this.TypeLabel.Size = new System.Drawing.Size(31, 13);
            this.TypeLabel.TabIndex = 4;
            this.TypeLabel.Text = "Type";
            // 
            // DescriptionBox
            // 
            this.DescriptionBox.Location = new System.Drawing.Point(98, 78);
            this.DescriptionBox.Name = "DescriptionBox";
            this.DescriptionBox.Size = new System.Drawing.Size(100, 20);
            this.DescriptionBox.TabIndex = 5;
            // 
            // DescriptionLabel
            // 
            this.DescriptionLabel.AutoSize = true;
            this.DescriptionLabel.Location = new System.Drawing.Point(32, 81);
            this.DescriptionLabel.Name = "DescriptionLabel";
            this.DescriptionLabel.Size = new System.Drawing.Size(60, 13);
            this.DescriptionLabel.TabIndex = 6;
            this.DescriptionLabel.Text = "Description";
            // 
            // RequirementsCheckedListBox
            // 
            this.RequirementsCheckedListBox.CheckOnClick = true;
            this.RequirementsCheckedListBox.FormattingEnabled = true;
            this.RequirementsCheckedListBox.Location = new System.Drawing.Point(16, 208);
            this.RequirementsCheckedListBox.Name = "RequirementsCheckedListBox";
            this.RequirementsCheckedListBox.Size = new System.Drawing.Size(100, 94);
            this.RequirementsCheckedListBox.TabIndex = 7;
            // 
            // RequirementsLabel
            // 
            this.RequirementsLabel.AutoSize = true;
            this.RequirementsLabel.Location = new System.Drawing.Point(28, 305);
            this.RequirementsLabel.Name = "RequirementsLabel";
            this.RequirementsLabel.Size = new System.Drawing.Size(72, 13);
            this.RequirementsLabel.TabIndex = 8;
            this.RequirementsLabel.Text = "Requirements";
            // 
            // MightBox
            // 
            this.MightBox.Location = new System.Drawing.Point(98, 104);
            this.MightBox.Name = "MightBox";
            this.MightBox.Size = new System.Drawing.Size(100, 20);
            this.MightBox.TabIndex = 9;
            // 
            // MightLabel
            // 
            this.MightLabel.AutoSize = true;
            this.MightLabel.Location = new System.Drawing.Point(28, 107);
            this.MightLabel.Name = "MightLabel";
            this.MightLabel.Size = new System.Drawing.Size(66, 13);
            this.MightLabel.TabIndex = 10;
            this.MightLabel.Text = "Bonus Might";
            // 
            // DefenceBox
            // 
            this.DefenceBox.Location = new System.Drawing.Point(98, 130);
            this.DefenceBox.Name = "DefenceBox";
            this.DefenceBox.Size = new System.Drawing.Size(100, 20);
            this.DefenceBox.TabIndex = 11;
            // 
            // DefenceLabel
            // 
            this.DefenceLabel.AutoSize = true;
            this.DefenceLabel.Location = new System.Drawing.Point(13, 133);
            this.DefenceLabel.Name = "DefenceLabel";
            this.DefenceLabel.Size = new System.Drawing.Size(81, 13);
            this.DefenceLabel.TabIndex = 12;
            this.DefenceLabel.Text = "Bonus Defence";
            // 
            // WeightBox
            // 
            this.WeightBox.Location = new System.Drawing.Point(98, 156);
            this.WeightBox.Name = "WeightBox";
            this.WeightBox.Size = new System.Drawing.Size(100, 20);
            this.WeightBox.TabIndex = 13;
            // 
            // WeightLabel
            // 
            this.WeightLabel.AutoSize = true;
            this.WeightLabel.Location = new System.Drawing.Point(18, 159);
            this.WeightLabel.Name = "WeightLabel";
            this.WeightLabel.Size = new System.Drawing.Size(74, 13);
            this.WeightLabel.TabIndex = 14;
            this.WeightLabel.Text = "Bonus Weight";
            // 
            // ItemWeightBox
            // 
            this.ItemWeightBox.Location = new System.Drawing.Point(98, 182);
            this.ItemWeightBox.Name = "ItemWeightBox";
            this.ItemWeightBox.Size = new System.Drawing.Size(100, 20);
            this.ItemWeightBox.TabIndex = 15;
            // 
            // ItemWeightLabel
            // 
            this.ItemWeightLabel.AutoSize = true;
            this.ItemWeightLabel.Location = new System.Drawing.Point(28, 185);
            this.ItemWeightLabel.Name = "ItemWeightLabel";
            this.ItemWeightLabel.Size = new System.Drawing.Size(64, 13);
            this.ItemWeightLabel.TabIndex = 16;
            this.ItemWeightLabel.Text = "Item Weight";
            // 
            // PropertiesBox
            // 
            this.PropertiesBox.Location = new System.Drawing.Point(122, 208);
            this.PropertiesBox.Name = "PropertiesBox";
            this.PropertiesBox.Size = new System.Drawing.Size(100, 96);
            this.PropertiesBox.TabIndex = 17;
            this.PropertiesBox.Text = "";
            // 
            // PropertiesLabel
            // 
            this.PropertiesLabel.AutoSize = true;
            this.PropertiesLabel.Location = new System.Drawing.Point(144, 305);
            this.PropertiesLabel.Name = "PropertiesLabel";
            this.PropertiesLabel.Size = new System.Drawing.Size(54, 13);
            this.PropertiesLabel.TabIndex = 18;
            this.PropertiesLabel.Text = "Properties";
            // 
            // AddButton
            // 
            this.AddButton.Location = new System.Drawing.Point(16, 323);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(100, 23);
            this.AddButton.TabIndex = 19;
            this.AddButton.Text = "Add";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // EditButton
            // 
            this.EditButton.Location = new System.Drawing.Point(123, 323);
            this.EditButton.Name = "EditButton";
            this.EditButton.Size = new System.Drawing.Size(99, 23);
            this.EditButton.TabIndex = 20;
            this.EditButton.Text = "Edit";
            this.EditButton.UseVisualStyleBackColor = true;
            this.EditButton.Click += new System.EventHandler(this.EditButton_Click);
            // 
            // ItemsListBox
            // 
            this.ItemsListBox.FormattingEnabled = true;
            this.ItemsListBox.Location = new System.Drawing.Point(359, 35);
            this.ItemsListBox.Name = "ItemsListBox";
            this.ItemsListBox.Size = new System.Drawing.Size(120, 251);
            this.ItemsListBox.TabIndex = 21;
            this.ItemsListBox.DoubleClick += new System.EventHandler(this.ItemsListBox_DoubleClick);
            // 
            // ItemsLabel
            // 
            this.ItemsLabel.Location = new System.Drawing.Point(359, 9);
            this.ItemsLabel.Name = "ItemsLabel";
            this.ItemsLabel.Size = new System.Drawing.Size(120, 23);
            this.ItemsLabel.TabIndex = 22;
            this.ItemsLabel.Text = "ITEMS";
            this.ItemsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(338, 292);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 23;
            this.SaveButton.Text = "Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // LoadButton
            // 
            this.LoadButton.Location = new System.Drawing.Point(419, 292);
            this.LoadButton.Name = "LoadButton";
            this.LoadButton.Size = new System.Drawing.Size(75, 23);
            this.LoadButton.TabIndex = 24;
            this.LoadButton.Text = "Load";
            this.LoadButton.UseVisualStyleBackColor = true;
            this.LoadButton.Click += new System.EventHandler(this.LoadButton_Click);
            // 
            // DeleteButton
            // 
            this.DeleteButton.Location = new System.Drawing.Point(338, 321);
            this.DeleteButton.Name = "DeleteButton";
            this.DeleteButton.Size = new System.Drawing.Size(156, 23);
            this.DeleteButton.TabIndex = 25;
            this.DeleteButton.Text = "Delete";
            this.DeleteButton.UseVisualStyleBackColor = true;
            this.DeleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
            // 
            // ItemsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(549, 358);
            this.Controls.Add(this.DeleteButton);
            this.Controls.Add(this.LoadButton);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.ItemsLabel);
            this.Controls.Add(this.ItemsListBox);
            this.Controls.Add(this.EditButton);
            this.Controls.Add(this.AddButton);
            this.Controls.Add(this.PropertiesLabel);
            this.Controls.Add(this.PropertiesBox);
            this.Controls.Add(this.ItemWeightLabel);
            this.Controls.Add(this.ItemWeightBox);
            this.Controls.Add(this.WeightLabel);
            this.Controls.Add(this.WeightBox);
            this.Controls.Add(this.DefenceLabel);
            this.Controls.Add(this.DefenceBox);
            this.Controls.Add(this.MightLabel);
            this.Controls.Add(this.MightBox);
            this.Controls.Add(this.RequirementsLabel);
            this.Controls.Add(this.RequirementsCheckedListBox);
            this.Controls.Add(this.DescriptionLabel);
            this.Controls.Add(this.DescriptionBox);
            this.Controls.Add(this.TypeLabel);
            this.Controls.Add(this.TypeBox);
            this.Controls.Add(this.NameBox);
            this.Controls.Add(this.NameLabel);
            this.Name = "ItemsForm";
            this.Text = "Items";
            this.Deactivate += new System.EventHandler(this.ItemsForm_Deactivate);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ItemsForm_FormClosing);
            this.Load += new System.EventHandler(this.ItemsForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.TextBox NameBox;
        private System.Windows.Forms.TextBox TypeBox;
        private System.Windows.Forms.Label TypeLabel;
        private System.Windows.Forms.TextBox DescriptionBox;
        private System.Windows.Forms.Label DescriptionLabel;
        private System.Windows.Forms.CheckedListBox RequirementsCheckedListBox;
        private System.Windows.Forms.Label RequirementsLabel;
        private System.Windows.Forms.TextBox MightBox;
        private System.Windows.Forms.Label MightLabel;
        private System.Windows.Forms.TextBox DefenceBox;
        private System.Windows.Forms.Label DefenceLabel;
        private System.Windows.Forms.TextBox WeightBox;
        private System.Windows.Forms.Label WeightLabel;
        private System.Windows.Forms.TextBox ItemWeightBox;
        private System.Windows.Forms.Label ItemWeightLabel;
        private System.Windows.Forms.RichTextBox PropertiesBox;
        private System.Windows.Forms.Label PropertiesLabel;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.Button EditButton;
        private System.Windows.Forms.ListBox ItemsListBox;
        private System.Windows.Forms.Label ItemsLabel;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.Button LoadButton;
        private System.Windows.Forms.Button DeleteButton;
    }
}