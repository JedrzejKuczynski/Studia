namespace ProgramowanieWizualne
{
    partial class InventoryForm
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
            this.ItemsListBox = new System.Windows.Forms.ListBox();
            this.ItemsLabel = new System.Windows.Forms.Label();
            this.ItemsButton = new System.Windows.Forms.Button();
            this.NameBox = new System.Windows.Forms.TextBox();
            this.NameLabel = new System.Windows.Forms.Label();
            this.LevelBox = new System.Windows.Forms.TextBox();
            this.ClassBox = new System.Windows.Forms.TextBox();
            this.DescriptionBox = new System.Windows.Forms.TextBox();
            this.LevelLabel = new System.Windows.Forms.Label();
            this.ClassLabel = new System.Windows.Forms.Label();
            this.DescriptionLabel = new System.Windows.Forms.Label();
            this.MightBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.DefenceBox = new System.Windows.Forms.TextBox();
            this.DefenceLabel = new System.Windows.Forms.Label();
            this.CurrentCarryBox = new System.Windows.Forms.TextBox();
            this.CurrentCarryLabel = new System.Windows.Forms.Label();
            this.CarryWeightBox = new System.Windows.Forms.TextBox();
            this.CarryWeightLabel = new System.Windows.Forms.Label();
            this.CharacterItemsListBox = new System.Windows.Forms.ListBox();
            this.CharacterItemsLabel = new System.Windows.Forms.Label();
            this.ItemDetailsButton = new System.Windows.Forms.Button();
            this.BonusMightBox = new System.Windows.Forms.TextBox();
            this.BonusDefenceBox = new System.Windows.Forms.TextBox();
            this.BonusCarryBox = new System.Windows.Forms.TextBox();
            this.ChartButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ItemsListBox
            // 
            this.ItemsListBox.FormattingEnabled = true;
            this.ItemsListBox.Location = new System.Drawing.Point(573, 32);
            this.ItemsListBox.Name = "ItemsListBox";
            this.ItemsListBox.Size = new System.Drawing.Size(167, 329);
            this.ItemsListBox.TabIndex = 0;
            this.ItemsListBox.DoubleClick += new System.EventHandler(this.ItemsListBox_DoubleClick);
            // 
            // ItemsLabel
            // 
            this.ItemsLabel.Location = new System.Drawing.Point(570, 14);
            this.ItemsLabel.Name = "ItemsLabel";
            this.ItemsLabel.Size = new System.Drawing.Size(167, 15);
            this.ItemsLabel.TabIndex = 1;
            this.ItemsLabel.Text = "ITEMS";
            this.ItemsLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // ItemsButton
            // 
            this.ItemsButton.Location = new System.Drawing.Point(573, 367);
            this.ItemsButton.Name = "ItemsButton";
            this.ItemsButton.Size = new System.Drawing.Size(167, 44);
            this.ItemsButton.TabIndex = 2;
            this.ItemsButton.Text = "Manage Items";
            this.ItemsButton.UseVisualStyleBackColor = true;
            this.ItemsButton.Click += new System.EventHandler(this.ItemsButton_Click);
            // 
            // NameBox
            // 
            this.NameBox.Location = new System.Drawing.Point(85, 38);
            this.NameBox.Name = "NameBox";
            this.NameBox.Size = new System.Drawing.Size(100, 20);
            this.NameBox.TabIndex = 3;
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Location = new System.Drawing.Point(44, 41);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(35, 13);
            this.NameLabel.TabIndex = 4;
            this.NameLabel.Text = "Name";
            // 
            // LevelBox
            // 
            this.LevelBox.Location = new System.Drawing.Point(85, 64);
            this.LevelBox.Name = "LevelBox";
            this.LevelBox.Size = new System.Drawing.Size(100, 20);
            this.LevelBox.TabIndex = 5;
            // 
            // ClassBox
            // 
            this.ClassBox.Location = new System.Drawing.Point(85, 90);
            this.ClassBox.Name = "ClassBox";
            this.ClassBox.Size = new System.Drawing.Size(100, 20);
            this.ClassBox.TabIndex = 6;
            // 
            // DescriptionBox
            // 
            this.DescriptionBox.Location = new System.Drawing.Point(85, 116);
            this.DescriptionBox.Name = "DescriptionBox";
            this.DescriptionBox.Size = new System.Drawing.Size(100, 20);
            this.DescriptionBox.TabIndex = 7;
            // 
            // LevelLabel
            // 
            this.LevelLabel.AutoSize = true;
            this.LevelLabel.Location = new System.Drawing.Point(46, 67);
            this.LevelLabel.Name = "LevelLabel";
            this.LevelLabel.Size = new System.Drawing.Size(33, 13);
            this.LevelLabel.TabIndex = 8;
            this.LevelLabel.Text = "Level";
            // 
            // ClassLabel
            // 
            this.ClassLabel.AutoSize = true;
            this.ClassLabel.Location = new System.Drawing.Point(47, 93);
            this.ClassLabel.Name = "ClassLabel";
            this.ClassLabel.Size = new System.Drawing.Size(32, 13);
            this.ClassLabel.TabIndex = 9;
            this.ClassLabel.Text = "Class";
            // 
            // DescriptionLabel
            // 
            this.DescriptionLabel.AutoSize = true;
            this.DescriptionLabel.Location = new System.Drawing.Point(19, 119);
            this.DescriptionLabel.Name = "DescriptionLabel";
            this.DescriptionLabel.Size = new System.Drawing.Size(60, 13);
            this.DescriptionLabel.TabIndex = 10;
            this.DescriptionLabel.Text = "Description";
            // 
            // MightBox
            // 
            this.MightBox.Location = new System.Drawing.Point(85, 142);
            this.MightBox.Name = "MightBox";
            this.MightBox.Size = new System.Drawing.Size(100, 20);
            this.MightBox.TabIndex = 11;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(47, 145);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Might";
            // 
            // DefenceBox
            // 
            this.DefenceBox.Location = new System.Drawing.Point(85, 165);
            this.DefenceBox.Name = "DefenceBox";
            this.DefenceBox.Size = new System.Drawing.Size(100, 20);
            this.DefenceBox.TabIndex = 13;
            // 
            // DefenceLabel
            // 
            this.DefenceLabel.AutoSize = true;
            this.DefenceLabel.Location = new System.Drawing.Point(31, 168);
            this.DefenceLabel.Name = "DefenceLabel";
            this.DefenceLabel.Size = new System.Drawing.Size(48, 13);
            this.DefenceLabel.TabIndex = 14;
            this.DefenceLabel.Text = "Defence";
            // 
            // CurrentCarryBox
            // 
            this.CurrentCarryBox.Location = new System.Drawing.Point(85, 191);
            this.CurrentCarryBox.Name = "CurrentCarryBox";
            this.CurrentCarryBox.Size = new System.Drawing.Size(100, 20);
            this.CurrentCarryBox.TabIndex = 15;
            // 
            // CurrentCarryLabel
            // 
            this.CurrentCarryLabel.AutoSize = true;
            this.CurrentCarryLabel.Location = new System.Drawing.Point(2, 194);
            this.CurrentCarryLabel.Name = "CurrentCarryLabel";
            this.CurrentCarryLabel.Size = new System.Drawing.Size(78, 13);
            this.CurrentCarryLabel.TabIndex = 16;
            this.CurrentCarryLabel.Text = "Current Weight";
            // 
            // CarryWeightBox
            // 
            this.CarryWeightBox.Location = new System.Drawing.Point(85, 217);
            this.CarryWeightBox.Name = "CarryWeightBox";
            this.CarryWeightBox.Size = new System.Drawing.Size(100, 20);
            this.CarryWeightBox.TabIndex = 17;
            // 
            // CarryWeightLabel
            // 
            this.CarryWeightLabel.AutoSize = true;
            this.CarryWeightLabel.Location = new System.Drawing.Point(11, 220);
            this.CarryWeightLabel.Name = "CarryWeightLabel";
            this.CarryWeightLabel.Size = new System.Drawing.Size(68, 13);
            this.CarryWeightLabel.TabIndex = 18;
            this.CarryWeightLabel.Text = "Carry Weight";
            // 
            // CharacterItemsListBox
            // 
            this.CharacterItemsListBox.FormattingEnabled = true;
            this.CharacterItemsListBox.Location = new System.Drawing.Point(12, 243);
            this.CharacterItemsListBox.Name = "CharacterItemsListBox";
            this.CharacterItemsListBox.Size = new System.Drawing.Size(173, 147);
            this.CharacterItemsListBox.TabIndex = 19;
            this.CharacterItemsListBox.DoubleClick += new System.EventHandler(this.CharacterItemsListBox_DoubleClick);
            // 
            // CharacterItemsLabel
            // 
            this.CharacterItemsLabel.AutoSize = true;
            this.CharacterItemsLabel.Location = new System.Drawing.Point(44, 393);
            this.CharacterItemsLabel.Name = "CharacterItemsLabel";
            this.CharacterItemsLabel.Size = new System.Drawing.Size(109, 13);
            this.CharacterItemsLabel.TabIndex = 20;
            this.CharacterItemsLabel.Text = "CHARACTER ITEMS";
            this.CharacterItemsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ItemDetailsButton
            // 
            this.ItemDetailsButton.Location = new System.Drawing.Point(452, 367);
            this.ItemDetailsButton.Name = "ItemDetailsButton";
            this.ItemDetailsButton.Size = new System.Drawing.Size(115, 44);
            this.ItemDetailsButton.TabIndex = 21;
            this.ItemDetailsButton.Text = "Show Item Details";
            this.ItemDetailsButton.UseVisualStyleBackColor = true;
            this.ItemDetailsButton.Click += new System.EventHandler(this.ItemDetailsButton_Click);
            // 
            // BonusMightBox
            // 
            this.BonusMightBox.Location = new System.Drawing.Point(191, 142);
            this.BonusMightBox.Name = "BonusMightBox";
            this.BonusMightBox.Size = new System.Drawing.Size(100, 20);
            this.BonusMightBox.TabIndex = 22;
            // 
            // BonusDefenceBox
            // 
            this.BonusDefenceBox.Location = new System.Drawing.Point(191, 165);
            this.BonusDefenceBox.Name = "BonusDefenceBox";
            this.BonusDefenceBox.Size = new System.Drawing.Size(100, 20);
            this.BonusDefenceBox.TabIndex = 23;
            // 
            // BonusCarryBox
            // 
            this.BonusCarryBox.Location = new System.Drawing.Point(191, 217);
            this.BonusCarryBox.Name = "BonusCarryBox";
            this.BonusCarryBox.Size = new System.Drawing.Size(100, 20);
            this.BonusCarryBox.TabIndex = 24;
            // 
            // ChartButton
            // 
            this.ChartButton.Location = new System.Drawing.Point(297, 367);
            this.ChartButton.Name = "ChartButton";
            this.ChartButton.Size = new System.Drawing.Size(149, 44);
            this.ChartButton.TabIndex = 26;
            this.ChartButton.Text = "Show Chart";
            this.ChartButton.UseVisualStyleBackColor = true;
            this.ChartButton.Click += new System.EventHandler(this.ChartButton_Click);
            // 
            // InventoryForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 423);
            this.Controls.Add(this.ChartButton);
            this.Controls.Add(this.BonusCarryBox);
            this.Controls.Add(this.BonusDefenceBox);
            this.Controls.Add(this.BonusMightBox);
            this.Controls.Add(this.ItemDetailsButton);
            this.Controls.Add(this.CharacterItemsLabel);
            this.Controls.Add(this.CharacterItemsListBox);
            this.Controls.Add(this.CarryWeightLabel);
            this.Controls.Add(this.CarryWeightBox);
            this.Controls.Add(this.CurrentCarryLabel);
            this.Controls.Add(this.CurrentCarryBox);
            this.Controls.Add(this.DefenceLabel);
            this.Controls.Add(this.DefenceBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MightBox);
            this.Controls.Add(this.DescriptionLabel);
            this.Controls.Add(this.ClassLabel);
            this.Controls.Add(this.LevelLabel);
            this.Controls.Add(this.DescriptionBox);
            this.Controls.Add(this.ClassBox);
            this.Controls.Add(this.LevelBox);
            this.Controls.Add(this.NameLabel);
            this.Controls.Add(this.NameBox);
            this.Controls.Add(this.ItemsButton);
            this.Controls.Add(this.ItemsLabel);
            this.Controls.Add(this.ItemsListBox);
            this.Name = "InventoryForm";
            this.Text = "Inventory";
            this.Activated += new System.EventHandler(this.InventoryForm_Activated);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.InventoryForm_FormClosing);
            this.Load += new System.EventHandler(this.InventoryForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox ItemsListBox;
        private System.Windows.Forms.Label ItemsLabel;
        private System.Windows.Forms.Button ItemsButton;
        private System.Windows.Forms.TextBox NameBox;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.TextBox LevelBox;
        private System.Windows.Forms.TextBox ClassBox;
        private System.Windows.Forms.TextBox DescriptionBox;
        private System.Windows.Forms.Label LevelLabel;
        private System.Windows.Forms.Label ClassLabel;
        private System.Windows.Forms.Label DescriptionLabel;
        private System.Windows.Forms.TextBox MightBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox DefenceBox;
        private System.Windows.Forms.Label DefenceLabel;
        private System.Windows.Forms.TextBox CurrentCarryBox;
        private System.Windows.Forms.Label CurrentCarryLabel;
        private System.Windows.Forms.TextBox CarryWeightBox;
        private System.Windows.Forms.Label CarryWeightLabel;
        private System.Windows.Forms.ListBox CharacterItemsListBox;
        private System.Windows.Forms.Label CharacterItemsLabel;
        private System.Windows.Forms.Button ItemDetailsButton;
        private System.Windows.Forms.TextBox BonusMightBox;
        private System.Windows.Forms.TextBox BonusDefenceBox;
        private System.Windows.Forms.TextBox BonusCarryBox;
        private System.Windows.Forms.Button ChartButton;
    }
}