namespace ProgramowanieWizualne
{
    partial class CharactersForm
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
            this.NameBox = new System.Windows.Forms.TextBox();
            this.LevelBox = new System.Windows.Forms.TextBox();
            this.DescriptionBox = new System.Windows.Forms.TextBox();
            this.ClassCombo = new System.Windows.Forms.ComboBox();
            this.LabelName = new System.Windows.Forms.Label();
            this.LevelLabel = new System.Windows.Forms.Label();
            this.DescriptionLabel = new System.Windows.Forms.Label();
            this.ClassLabel = new System.Windows.Forms.Label();
            this.AddButton = new System.Windows.Forms.Button();
            this.CharactersCombo = new System.Windows.Forms.ComboBox();
            this.CharactersLabel = new System.Windows.Forms.Label();
            this.EditButton = new System.Windows.Forms.Button();
            this.LoadButton = new System.Windows.Forms.Button();
            this.DeleteButton = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.SaveButton = new System.Windows.Forms.Button();
            this.CharacterWindowButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // NameBox
            // 
            this.NameBox.Location = new System.Drawing.Point(78, 60);
            this.NameBox.Name = "NameBox";
            this.NameBox.Size = new System.Drawing.Size(129, 20);
            this.NameBox.TabIndex = 0;
            this.NameBox.MouseHover += new System.EventHandler(this.NameBox_MouseHover);
            // 
            // LevelBox
            // 
            this.LevelBox.Location = new System.Drawing.Point(78, 83);
            this.LevelBox.Name = "LevelBox";
            this.LevelBox.Size = new System.Drawing.Size(129, 20);
            this.LevelBox.TabIndex = 1;
            this.LevelBox.MouseHover += new System.EventHandler(this.LevelBox_MouseHover);
            // 
            // DescriptionBox
            // 
            this.DescriptionBox.Location = new System.Drawing.Point(78, 109);
            this.DescriptionBox.Name = "DescriptionBox";
            this.DescriptionBox.Size = new System.Drawing.Size(129, 20);
            this.DescriptionBox.TabIndex = 2;
            this.DescriptionBox.MouseHover += new System.EventHandler(this.DescriptionBox_MouseHover);
            // 
            // ClassCombo
            // 
            this.ClassCombo.FormattingEnabled = true;
            this.ClassCombo.Location = new System.Drawing.Point(78, 135);
            this.ClassCombo.Name = "ClassCombo";
            this.ClassCombo.Size = new System.Drawing.Size(129, 21);
            this.ClassCombo.TabIndex = 3;
            this.ClassCombo.MouseHover += new System.EventHandler(this.ClassCombo_MouseHover);
            // 
            // LabelName
            // 
            this.LabelName.AutoSize = true;
            this.LabelName.Location = new System.Drawing.Point(40, 63);
            this.LabelName.Name = "LabelName";
            this.LabelName.Size = new System.Drawing.Size(35, 13);
            this.LabelName.TabIndex = 4;
            this.LabelName.Text = "Name";
            // 
            // LevelLabel
            // 
            this.LevelLabel.AutoSize = true;
            this.LevelLabel.Location = new System.Drawing.Point(40, 86);
            this.LevelLabel.Name = "LevelLabel";
            this.LevelLabel.Size = new System.Drawing.Size(33, 13);
            this.LevelLabel.TabIndex = 5;
            this.LevelLabel.Text = "Level";
            // 
            // DescriptionLabel
            // 
            this.DescriptionLabel.AutoSize = true;
            this.DescriptionLabel.Location = new System.Drawing.Point(15, 112);
            this.DescriptionLabel.Name = "DescriptionLabel";
            this.DescriptionLabel.Size = new System.Drawing.Size(60, 13);
            this.DescriptionLabel.TabIndex = 6;
            this.DescriptionLabel.Text = "Description";
            // 
            // ClassLabel
            // 
            this.ClassLabel.AutoSize = true;
            this.ClassLabel.Location = new System.Drawing.Point(43, 138);
            this.ClassLabel.Name = "ClassLabel";
            this.ClassLabel.Size = new System.Drawing.Size(32, 13);
            this.ClassLabel.TabIndex = 7;
            this.ClassLabel.Text = "Class";
            // 
            // AddButton
            // 
            this.AddButton.Location = new System.Drawing.Point(66, 162);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(75, 23);
            this.AddButton.TabIndex = 8;
            this.AddButton.Text = "Add";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // CharactersCombo
            // 
            this.CharactersCombo.FormattingEnabled = true;
            this.CharactersCombo.Location = new System.Drawing.Point(364, 103);
            this.CharactersCombo.Name = "CharactersCombo";
            this.CharactersCombo.Size = new System.Drawing.Size(133, 21);
            this.CharactersCombo.TabIndex = 9;
            this.CharactersCombo.SelectionChangeCommitted += new System.EventHandler(this.CharactersCombo_SelectionChangeCommitted);
            // 
            // CharactersLabel
            // 
            this.CharactersLabel.AutoSize = true;
            this.CharactersLabel.Location = new System.Drawing.Point(300, 106);
            this.CharactersLabel.Name = "CharactersLabel";
            this.CharactersLabel.Size = new System.Drawing.Size(58, 13);
            this.CharactersLabel.TabIndex = 10;
            this.CharactersLabel.Text = "Characters";
            // 
            // EditButton
            // 
            this.EditButton.Location = new System.Drawing.Point(147, 162);
            this.EditButton.Name = "EditButton";
            this.EditButton.Size = new System.Drawing.Size(75, 23);
            this.EditButton.TabIndex = 11;
            this.EditButton.Text = "Edit";
            this.EditButton.UseVisualStyleBackColor = true;
            this.EditButton.Click += new System.EventHandler(this.EditButton_Click);
            // 
            // LoadButton
            // 
            this.LoadButton.Location = new System.Drawing.Point(350, 130);
            this.LoadButton.Name = "LoadButton";
            this.LoadButton.Size = new System.Drawing.Size(75, 23);
            this.LoadButton.TabIndex = 12;
            this.LoadButton.Text = "Load";
            this.LoadButton.UseVisualStyleBackColor = true;
            this.LoadButton.Click += new System.EventHandler(this.LoadButton_Click);
            // 
            // DeleteButton
            // 
            this.DeleteButton.Location = new System.Drawing.Point(431, 130);
            this.DeleteButton.Name = "DeleteButton";
            this.DeleteButton.Size = new System.Drawing.Size(75, 23);
            this.DeleteButton.TabIndex = 13;
            this.DeleteButton.Text = "Delete";
            this.DeleteButton.UseVisualStyleBackColor = true;
            this.DeleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
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
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(105, 191);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 14;
            this.SaveButton.Text = "Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // CharacterWindowButton
            // 
            this.CharacterWindowButton.Location = new System.Drawing.Point(147, 282);
            this.CharacterWindowButton.Name = "CharacterWindowButton";
            this.CharacterWindowButton.Size = new System.Drawing.Size(278, 34);
            this.CharacterWindowButton.TabIndex = 15;
            this.CharacterWindowButton.Text = "Show Character";
            this.CharacterWindowButton.UseVisualStyleBackColor = true;
            this.CharacterWindowButton.Click += new System.EventHandler(this.CharacterWindowButton_Click);
            // 
            // CharactersForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(549, 358);
            this.Controls.Add(this.CharacterWindowButton);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.DeleteButton);
            this.Controls.Add(this.LoadButton);
            this.Controls.Add(this.EditButton);
            this.Controls.Add(this.CharactersLabel);
            this.Controls.Add(this.CharactersCombo);
            this.Controls.Add(this.AddButton);
            this.Controls.Add(this.ClassLabel);
            this.Controls.Add(this.DescriptionLabel);
            this.Controls.Add(this.LevelLabel);
            this.Controls.Add(this.LabelName);
            this.Controls.Add(this.ClassCombo);
            this.Controls.Add(this.DescriptionBox);
            this.Controls.Add(this.LevelBox);
            this.Controls.Add(this.NameBox);
            this.Name = "CharactersForm";
            this.Text = "Form1";
            this.Activated += new System.EventHandler(this.CharactersForm_Activated);
            this.Load += new System.EventHandler(this.CharactersForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox NameBox;
        private System.Windows.Forms.TextBox LevelBox;
        private System.Windows.Forms.TextBox DescriptionBox;
        private System.Windows.Forms.ComboBox ClassCombo;
        private System.Windows.Forms.Label LabelName;
        private System.Windows.Forms.Label LevelLabel;
        private System.Windows.Forms.Label DescriptionLabel;
        private System.Windows.Forms.Label ClassLabel;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.ComboBox CharactersCombo;
        private System.Windows.Forms.Label CharactersLabel;
        private System.Windows.Forms.Button EditButton;
        private System.Windows.Forms.Button LoadButton;
        private System.Windows.Forms.Button DeleteButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.Button CharacterWindowButton;
    }
}

