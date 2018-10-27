using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProgramowanieWizualne
{
    public partial class ItemsForm : Form
    {
        InventoryForm InventoryForm = null;
        List<Item> ItemsList; // Lista przechowująca przedmioty ze sklepu
        BindingSource ListBind;
        ToolTip Tip;

        public ItemsForm()
        {
            InitializeComponent();
        }

        public ItemsForm(Form CallingForm, List<Item> shop)
        {
            Tip = new ToolTip();
            InventoryForm = CallingForm as InventoryForm;
            ItemsList = shop;
            ListBind = new BindingSource();
            ListBind.DataSource = ItemsList;
            InitializeComponent();
        }

        private void ItemsForm_Load(object sender, EventArgs e)
        {
            RequirementsCheckedListBox.Items.Add("Any");
            RequirementsCheckedListBox.Items.Add("Warrior");
            RequirementsCheckedListBox.Items.Add("Mage");
            ItemsListBox.DataSource = ListBind;
            ItemsListBox.DisplayMember = "Name";
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            string name, type, description;
            int weight, might, defence, carryweight;
            List<string> requirements = new List<string>();
            List<string> properties;
            List<Tuple<string, int>> bonus = new List<Tuple<string, int>>();

            if (NameBox.Text == "")
            {
                MessageBox.Show("Puste pole na imię!");
                return;
            }
            else
                name = NameBox.Text;

            if (TypeBox.Text == "")
            {
                MessageBox.Show("Puste pole określające typ przedmiotu!");
                return;
            }
            else
                type = TypeBox.Text;

            if (DescriptionBox.Text == "")
            {
                MessageBox.Show("Puste pole opisu!");
                return;
            }
            else
                description = DescriptionBox.Text;

            int.TryParse(ItemWeightBox.Text, out weight);
            if (weight == 0)
            {
                MessageBox.Show("Błąd w polu określającym wagę przedmiotu!");
                return;
            }

            bool might_result = int.TryParse(MightBox.Text, out might);
            bool defence_result = int.TryParse(DefenceBox.Text, out defence);
            bool carryweight_result = int.TryParse(WeightBox.Text, out carryweight);

            if (!might_result || !defence_result || !carryweight_result)
            {
                MessageBox.Show("Błąd w polach określających bonusy!");
                return;
            }
            else
            {
                Tuple<string, int> MightTuple = new Tuple<string, int>("Might", might);
                Tuple<string, int> DefenceTuple = new Tuple<string, int>("Defence", defence);
                Tuple<string, int> CarryWeightTuple = new Tuple<string, int>("CarryWeight", carryweight);
                bonus.Add(MightTuple);
                bonus.Add(DefenceTuple);
                bonus.Add(CarryWeightTuple);
            }

            if (RequirementsCheckedListBox.CheckedItems.Count == 0)
                requirements.Add("Any");
            else
            {
                foreach (object item in RequirementsCheckedListBox.CheckedItems)
                    requirements.Add(item.ToString());
            }

            properties = new List<string>(PropertiesBox.Lines);

            Item New_Item = new Item(name, type, description, requirements, bonus, properties, weight);
            ItemsList.Add(New_Item);
            ListBind.DataSource = null;
            ListBind.DataSource = ItemsList;

            NameBox.Clear();
            TypeBox.Clear();
            DescriptionBox.Clear();
            MightBox.Clear();
            DefenceBox.Clear();
            WeightBox.Clear();
            ItemWeightBox.Clear();
            PropertiesBox.Clear();

            foreach (int i in RequirementsCheckedListBox.CheckedIndices)
                RequirementsCheckedListBox.SetItemChecked(i, false);
        }

        private void EditButton_Click(object sender, EventArgs e)
        {
            string name, type, description;
            int weight, might, defence, carryweight;
            List<string> requirements = new List<string>();
            List<string> properties;
            List<Tuple<string, int>> bonus = new List<Tuple<string, int>>();

            if (NameBox.Text == "")
            {
                MessageBox.Show("Puste pole na imię!");
                return;
            }
            else
                name = NameBox.Text;

            if (TypeBox.Text == "")
            {
                MessageBox.Show("Puste pole określające typ przedmiotu!");
                return;
            }
            else
                type = TypeBox.Text;

            if (DescriptionBox.Text == "")
            {
                MessageBox.Show("Puste pole opisu!");
                return;
            }
            else
                description = DescriptionBox.Text;

            int.TryParse(ItemWeightBox.Text, out weight);
            if (weight == 0)
            {
                MessageBox.Show("Błąd w polu określającym wagę przedmiotu!");
                return;
            }

            bool might_result = int.TryParse(MightBox.Text, out might);
            bool defence_result = int.TryParse(DefenceBox.Text, out defence);
            bool carryweight_result = int.TryParse(WeightBox.Text, out carryweight);

            if (!might_result || !defence_result || !carryweight_result)
            {
                MessageBox.Show("Błąd w polach określających bonusy!");
                return;
            }
            else
            {
                Tuple<string, int> MightTuple = new Tuple<string, int>("Might", might);
                Tuple<string, int> DefenceTuple = new Tuple<string, int>("Defence", defence);
                Tuple<string, int> CarryWeightTuple = new Tuple<string, int>("CarryWeight", carryweight);
                bonus.Add(MightTuple);
                bonus.Add(DefenceTuple);
                bonus.Add(CarryWeightTuple);
            }

            if (RequirementsCheckedListBox.CheckedItems.Count == 0)
                requirements.Add("Any");
            else
            {
                foreach (object item in RequirementsCheckedListBox.CheckedItems)
                    requirements.Add(item.ToString());
            }

            properties = new List<string>(PropertiesBox.Lines);

            Item Edited = new Item(name, type, description, requirements, bonus, properties, weight);
            ItemsList[ItemsListBox.SelectedIndex] = Edited;
            ListBind.DataSource = null;
            ListBind.DataSource = ItemsList;
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            ItemsList.RemoveAt(ItemsListBox.SelectedIndex);
            ListBind.DataSource = null;
            ListBind.DataSource = ItemsList;

            NameBox.Clear();
            TypeBox.Clear();
            DescriptionBox.Clear();
            MightBox.Clear();
            DefenceBox.Clear();
            WeightBox.Clear();
            ItemWeightBox.Clear();
            PropertiesBox.Clear();

            foreach (int i in RequirementsCheckedListBox.CheckedIndices)
                RequirementsCheckedListBox.SetItemChecked(i, false);
        }

        private void ItemsListBox_DoubleClick(object sender, EventArgs e)
        {
            PropertiesBox.Clear();

            foreach (int i in RequirementsCheckedListBox.CheckedIndices)
                RequirementsCheckedListBox.SetItemChecked(i, false);

            Item Selected = (Item)ItemsListBox.SelectedItem;
            NameBox.Text = Selected.Name;
            TypeBox.Text = Selected.Type;
            DescriptionBox.Text = Selected.Description;
            MightBox.Text = Selected.Bonus.Find(t => t.Item1 == "Might").Item2.ToString();
            DefenceBox.Text = Selected.Bonus.Find(t => t.Item1 == "Defence").Item2.ToString();
            WeightBox.Text = Selected.Bonus.Find(t => t.Item1 == "CarryWeight").Item2.ToString();
            ItemWeightBox.Text = Selected.Weight.ToString();

            for (int i = 0; i < Selected.Requirements.Count; i++)
            {
                for (int j = 0; j < RequirementsCheckedListBox.Items.Count; j++)
                {
                    if (Selected.Requirements[i] == RequirementsCheckedListBox.Items[j].ToString())
                        RequirementsCheckedListBox.SetItemChecked(j, true);
                }
            }

            foreach (string property in Selected.Properties)
            {
                PropertiesBox.AppendText(property + "\n");
            }
        }

        private void ItemsForm_Deactivate(object sender, EventArgs e) // Aktualizacja list przedmiotów w InventoryForm
        {
            InventoryForm.SetItemShop = ItemsList;
            ItemsList = InventoryForm.FilterItems(ItemsList);
            InventoryForm.SetItemsList = ItemsList;
        }

        private void ItemsForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            Item item = (Item)ItemsListBox.SelectedItem;
            using (StreamWriter writer = new StreamWriter(saveFileDialog1.FileName + ".txt"))
            {

                writer.WriteLine(item.Item_ID.ToString());
                writer.WriteLine(item.Name);
                writer.WriteLine(item.Type);
                writer.WriteLine(item.Description);

                foreach (string req in item.Requirements)
                    writer.Write(req + ";");
                writer.WriteLine();

                foreach (Tuple<string, int> tuple in item.Bonus)
                    writer.Write(tuple.Item1 + " " + tuple.Item2.ToString() + ";");
                writer.WriteLine();

                foreach (string prop in item.Properties)
                    writer.Write(prop + ";");
                writer.WriteLine();

                writer.WriteLine(item.Weight.ToString());
            }
        }

        private void LoadButton_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            int item_id, item_weight;
            string name, type, description;
            string[] split;
            List<string> requirements = new List<string>();
            List<string> properties = new List<string>();
            List<Tuple<string, int>> bonus = new List<Tuple<string, int>>();


            using(StreamReader reader = new StreamReader(openFileDialog1.FileName))
            {
                item_id = int.Parse(reader.ReadLine());
                name = reader.ReadLine();
                type = reader.ReadLine();
                description = reader.ReadLine();


                split = reader.ReadLine().Split(';');
                foreach (string req in split)
                    if (req.Length > 0)
                        requirements.Add(req);

                split = reader.ReadLine().Split(';');
                foreach (string bon in split)
                {
                    if (bon.Length > 0)
                    {
                        string[] split_bonus = bon.Split(' ');
                        Tuple<string, int> new_tuple = new Tuple<string, int>(split_bonus[0], int.Parse(split_bonus[1]));
                        bonus.Add(new_tuple);
                    }
                }

                split = reader.ReadLine().Split(';');
                foreach (string prop in split)
                    if (prop.Length > 0)
                        properties.Add(prop);

                item_weight = int.Parse(reader.ReadLine());

                Item new_item = new Item(item_id, name, type, description, requirements, bonus, properties, item_weight);
                ItemsList.Add(new_item);
                ListBind.DataSource = null;
                ListBind.DataSource = ItemsList;
            }
        }
    }
}
