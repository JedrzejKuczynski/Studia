using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProgramowanieWizualne
{
    public partial class ItemDetailsForm : Form
    {
        InventoryForm InventoryForm = null;
        Item CurrentItem;
        ToolTip Tip = new ToolTip();

        public ItemDetailsForm()
        {
            InitializeComponent();
        }

        public ItemDetailsForm(Form CallingForm, Item item)
        {
            InventoryForm = CallingForm as InventoryForm;
            CurrentItem = item;
            InitializeComponent();
        }

        private void ItemDetailsForm_Load(object sender, EventArgs e)
        {
            NameBox.Text = CurrentItem.Name;
            TypeBox.Text = CurrentItem.Type;
            DescriptionBox.Text = CurrentItem.Description;
            MightBox.Text = CurrentItem.Bonus.Find(t => t.Item1 == "Might").Item2.ToString();
            DefenceBox.Text = CurrentItem.Bonus.Find(t => t.Item1 == "Defence").Item2.ToString();
            WeightBox.Text = CurrentItem.Bonus.Find(t => t.Item1 == "CarryWeight").Item2.ToString();
            ItemWeightBox.Text = CurrentItem.Weight.ToString();

            foreach (string req in CurrentItem.Requirements)
                RequirementsBox.AppendText(req + Environment.NewLine);
            foreach (string prop in CurrentItem.Properties)
                PropertiesBox.AppendText(prop + Environment.NewLine);

        }
    }
}
