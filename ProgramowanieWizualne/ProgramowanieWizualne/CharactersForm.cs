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
    public partial class CharactersForm : Form
    {
        List<Character> CharactersList; // Lista przechowująca postacie
        List<Item> CharacterItemsList; // Lista potrzebna do przypisywania przedmiotów do aktualnie wybranej postaci
        List<Item> ItemsList; // Lista przechowująca przedmioty ze sklepu
        ToolTip Default; // Chmurka podpowiadająca
        BindingSource ComboBind; // Bind do ComboBox z postaciami

        public CharactersForm()
        {
            CharactersList = new List<Character>();
            CharacterItemsList = new List<Item>();
            ItemsList = new List<Item>();
            Default = new ToolTip();
            ComboBind = new BindingSource();
            ComboBind.DataSource = CharactersList;
            InitializeComponent();
        }

        public List<Item> SetCharacterItems // Właściwość wykorzystywana przez InventoryForm do ustawiania przedmiotów postaci
        {
            set { CharacterItemsList = value; }
        }

        public List<Item> SetItemsList // Właściwość wykorzystywana przez InventoryForm do ustawiania sklepu
        {
            set { ItemsList = value; }
        }

        private void AssignCharacterItems(List<Item> items) //Funkcja przypisująca przedmioty do odpowiedniej postaci
        {
            Character Selected = (Character)CharactersCombo.SelectedItem;
            Selected.CharacterItems = items;
        }

        private void CharactersForm_Load(object sender, EventArgs e)
        {
            ClassCombo.Items.Add("Warrior");
            ClassCombo.Items.Add("Mage");
            CharactersCombo.DataSource = ComboBind;
            CharactersCombo.DisplayMember = "Name";
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            string name = NameBox.Text;
            string description = DescriptionBox.Text;
            string profession;
            int lvl;
            int.TryParse(LevelBox.Text, out lvl);

            if (ClassCombo.SelectedItem == null)
                profession = "Warrior";
            else
                profession = ClassCombo.SelectedItem.ToString();

            Character New_Character = new Character(name, lvl, description, profession);
            CharactersList.Add(New_Character);
            ComboBind.ResetBindings(false);

            NameBox.Clear();
            LevelBox.Clear();
            DescriptionBox.Clear();
            ClassCombo.ResetText();
        }

        private void NameBox_MouseHover(object sender, EventArgs e)
        {
            Default.Show("Domyślnie: Gall", NameBox);
        }

        private void DescriptionBox_MouseHover(object sender, EventArgs e)
        {
            Default.Show("Domyślnie: Anonim", DescriptionBox);
        }

        private void CharactersCombo_SelectionChangeCommitted(object sender, EventArgs e)
        {
            Character Selected = (Character)CharactersCombo.SelectedItem;
            NameBox.Text = Selected.Name;
            LevelBox.Text = Selected.Level.ToString();
            DescriptionBox.Text = Selected.Description;
            ClassCombo.SelectedItem = Selected.Profession.Description;
        }

        private void LevelBox_MouseHover(object sender, EventArgs e)
        {
            Default.Show("Domyślnie lub przy błędzie: 1", LevelBox);
        }

        private void EditButton_Click(object sender, EventArgs e)
        {
            Character Edited = new Character(NameBox.Text, int.Parse(LevelBox.Text), DescriptionBox.Text, ClassCombo.SelectedItem.ToString());
            CharactersList[CharactersCombo.SelectedIndex] = Edited;
            ComboBind.ResetBindings(false);
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            CharactersList.RemoveAt(CharactersCombo.SelectedIndex);
            ComboBind.ResetBindings(false);

            NameBox.Clear();
            LevelBox.Clear();
            DescriptionBox.Clear();
            ClassCombo.ResetText();
        }

        private void CharacterWindowButton_Click(object sender, EventArgs e) // Otwieranie InventoryForm
        {
            Character Selected = (Character)CharactersCombo.SelectedItem;
            InventoryForm InventoryForm = new InventoryForm(this, Selected, ItemsList);
            InventoryForm.ShowDialog();
        }

        private void ClassCombo_MouseHover(object sender, EventArgs e)
        {
            Default.Show("Domyślnie: Warrior", ClassCombo);
        }

        private void CharactersForm_Activated(object sender, EventArgs e) // Funkcja aktualizująca przedmioty postaci po wyjściu z InventoryForm
        {
            AssignCharacterItems(CharacterItemsList);
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            Character character = (Character)CharactersCombo.SelectedItem;

            using (StreamWriter writer = new StreamWriter(saveFileDialog1.FileName + ".txt"))
            {
                writer.WriteLine(character.Character_ID.ToString());
                writer.WriteLine(character.Name);
                writer.WriteLine(character.Level);
                writer.WriteLine(character.Profession.Description);
                writer.WriteLine(character.Description);
                writer.WriteLine(character.Might.ToString());
                writer.WriteLine(character.Defence.ToString());
                writer.WriteLine(character.CurrentWeight.ToString());
                writer.WriteLine(character.CarryWeight.ToString());

                foreach (Item item in character.CharacterItems)
                {
                    writer.WriteLine("/*");

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

                    writer.WriteLine("*/");
                }
            }
        }

        private void LoadButton_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            int char_id, lvl, might, defence, current_weight, carry_weight;
            string char_name, char_description, profession;

            using (StreamReader reader = new StreamReader(openFileDialog1.FileName))
            {
                char_id = int.Parse(reader.ReadLine());
                char_name = reader.ReadLine();
                lvl = int.Parse(reader.ReadLine());
                profession = reader.ReadLine();
                char_description = reader.ReadLine();
                might = int.Parse(reader.ReadLine());
                defence = int.Parse(reader.ReadLine());
                current_weight = int.Parse(reader.ReadLine());
                carry_weight = int.Parse(reader.ReadLine());

                while (reader.Peek() > -1)
                {
                    if (reader.ReadLine() == "/*")
                    {
                        int item_id, item_weight;
                        string name, type, description;
                        string[] split;
                        List<string> requirements = new List<string>();
                        List<string> properties = new List<string>();
                        List<Tuple<string, int>> bonus = new List<Tuple<string, int>>();

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
                        CharacterItemsList.Add(new_item);
                        reader.ReadLine();
                    }
                }

                Character new_character = new Character(char_id, char_name, char_description, profession, lvl, might, defence, current_weight, carry_weight, CharacterItemsList);
                CharactersList.Add(new_character);
                ComboBind.DataSource = null;
                ComboBind.DataSource = CharactersList;
            }
        }
    }
}
