using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ProgramowanieWizualne
{
    public partial class InventoryForm : Form
    {

        CharactersForm CharactersForm = null;
        Character CurrentCharacter; // Zmienna przechowująca aktualną postać
        ItemsForm ItemsManagerForm = null;
        List<Item> ItemsList, ItemShopList; // Lista przedmiotów dostępnych dla postaci ze sklepu oraz sklep
        List<Item> CharacterItemsList; // Lista przedmiotów postaci
        BindingSource CharacterItemsBind, ItemsBind;

        public InventoryForm()
        {
            InitializeComponent();
        }

        public InventoryForm(Form CallingForm, Character character, List<Item> shop)
        {
            CharactersForm = CallingForm as CharactersForm;
            CurrentCharacter = character;
            ItemShopList = shop;
            if (CurrentCharacter != null)
            {
                CharacterItemsBind = new BindingSource();
                CharacterItemsList = CurrentCharacter.CharacterItems;
                CharacterItemsBind.DataSource = CharacterItemsList;
            }
            InitializeComponent();
        }

        private void InventoryForm_Load(object sender, EventArgs e)
        {
            if (CurrentCharacter != null)
            {
                int bonus_might = 0;
                int bonus_defence = 0;
                int bonus_carry = 0;

                NameBox.Text = CurrentCharacter.Name;
                LevelBox.Text = CurrentCharacter.Level.ToString();
                ClassBox.Text = CurrentCharacter.Profession.Description;
                DescriptionBox.Text = CurrentCharacter.Description;
                MightBox.Text = CurrentCharacter.Might.ToString();
                DefenceBox.Text = CurrentCharacter.Defence.ToString();
                CurrentCarryBox.Text = CurrentCharacter.CurrentWeight.ToString();
                CarryWeightBox.Text = CurrentCharacter.CarryWeight.ToString();
                CharacterItemsListBox.DataSource = CharacterItemsBind;
                CharacterItemsListBox.DisplayMember = "Name";

                foreach (Item item in CurrentCharacter.CharacterItems)
                {
                    bonus_might += item.Bonus.Find(t => t.Item1 == "Might").Item2;
                    bonus_defence += item.Bonus.Find(t => t.Item1 == "Defence").Item2;
                    bonus_carry += item.Bonus.Find(t => t.Item1 == "CarryWeight").Item2;
                }

                BonusMightBox.Text = bonus_might.ToString();
                BonusDefenceBox.Text = bonus_defence.ToString();
                BonusCarryBox.Text = bonus_carry.ToString();
            }

            ItemsList = FilterItems(ItemShopList);

            foreach (Item item in ItemsList)
            {
                if (CharacterItemsList.Contains(item))
                    ItemsList.Remove(item);
            }

            ItemsBind = new BindingSource();
            ItemsBind.DataSource = ItemsList;
            ItemsListBox.DataSource = ItemsBind;
            ItemsListBox.DisplayMember = "Name";
        }

        public List<Item> SetItemsList // Właściwość wykorzystywana przez ItemsForm do ustawiania listy przedmiotów dostępnej dla postaci
        {
            set
            {
                ItemsList = value;
            }
        }

        public List<Item> SetItemShop // Właściwość wykorzystywana przez ItemsForm do ustawiania sklepu
        {
            set
            {
                ItemShopList = value;
            }
        }

        public List<Item> FilterItems(List<Item> items) // Funkcja filtrująca przedmioty ze sklepu (zwraca listę przedmiotów dostępnych dla aktualnie wybranej postaci)
        {
            List<Item> FilteredItems = new List<Item>();

            foreach (Item item in items)
            {
                if (item.Requirements.Contains("Any") || item.Requirements.Contains(CurrentCharacter.Profession.Description))
                    FilteredItems.Add(item);
            }

            return FilteredItems;
        }

        private void InventoryForm_Activated(object sender, EventArgs e)
        {
            ItemsBind = new BindingSource();

            foreach (Item item in ItemsList)
            {
                if (CharacterItemsList.Contains(item))
                    ItemsList.Remove(item);
            }

            ItemsBind.DataSource = ItemsList;
            ItemsListBox.DataSource = ItemsBind;
            ItemsListBox.DisplayMember = "Name";
        }

        private void ItemDetailsButton_Click(object sender, EventArgs e)
        {
            ItemDetailsForm ItemDetails = new ItemDetailsForm(this, (Item)ItemsListBox.SelectedItem);
            ItemDetails.ShowDialog();
        }

        private void ItemsListBox_DoubleClick(object sender, EventArgs e)
        {
            Item Selected = (Item)ItemsListBox.SelectedItem;
            if (CurrentCharacter != null)
            {
                int carry = CurrentCharacter.CurrentWeight + Selected.Weight;
                if (carry <= CurrentCharacter.CarryWeight)
                {
                    int bonus_might, bonus_defence, bonus_carry;

                    int.TryParse(BonusMightBox.Text, out bonus_might);
                    int.TryParse(BonusDefenceBox.Text, out bonus_defence);
                    int.TryParse(BonusCarryBox.Text, out bonus_carry);

                    CurrentCharacter.CurrentWeight += Selected.Weight;

                    bonus_might += Selected.Bonus.Find(t => t.Item1 == "Might").Item2;
                    bonus_defence += Selected.Bonus.Find(t => t.Item1 == "Defence").Item2;
                    bonus_carry += Selected.Bonus.Find(t => t.Item1 == "CarryWeight").Item2;

                    BonusMightBox.Text = bonus_might.ToString();
                    BonusDefenceBox.Text = bonus_defence.ToString();
                    BonusCarryBox.Text = bonus_carry.ToString();
                    CurrentCarryBox.Text = CurrentCharacter.CurrentWeight.ToString();

                    CharacterItemsList.Add(Selected);
                    ItemsList.RemoveAt(ItemsListBox.SelectedIndex);
                    ItemsBind.DataSource = null;
                    ItemsBind.DataSource = ItemsList;
                    CharacterItemsBind.DataSource = null;
                    CharacterItemsBind.DataSource = CharacterItemsList;
                }
                else
                {
                    MessageBox.Show("Przedmiot jest za ciężki!!!");
                    return;
                }
            }
        }

        private void ChartButton_Click(object sender, EventArgs e)
        {
            Item Selected = (Item)ItemsListBox.SelectedItem;
            int bonus_might = CurrentCharacter.Might + Selected.Bonus.Find(t => t.Item1 == "Might").Item2;
            int bonus_defence = CurrentCharacter.Defence + Selected.Bonus.Find(t => t.Item1 == "Defence").Item2;
            int bonus_carry = CurrentCharacter.CarryWeight + Selected.Bonus.Find(t => t.Item1 == "CarryWeight").Item2;
            int carry_weight = CurrentCharacter.CurrentWeight + Selected.Weight;

            string[] names = { "Base_Might", "Bonus_Might", "Base_Defence", "Bonus_Defence", "CarryWeight", "WithItem_CarryWeight", "Current_Weight", "WithItem_Weight" };
            List<string> SeriesList = new List<string>(names);

            int[] stats = { CurrentCharacter.Might, bonus_might, CurrentCharacter.Defence, bonus_defence, CurrentCharacter.CarryWeight, bonus_carry, CurrentCharacter.CurrentWeight, carry_weight };
            List<int> PointsList = new List<int>(stats);

            StatsChartForm StatsForm = new StatsChartForm(this, SeriesList, PointsList);
            StatsForm.ShowDialog();
        }

        private void CharacterItemsListBox_DoubleClick(object sender, EventArgs e)
        {
            ItemDetailsForm ItemDetails = new ItemDetailsForm(this, (Item)CharacterItemsListBox.SelectedItem);
            ItemDetails.ShowDialog();
        }

        private void InventoryForm_FormClosing(object sender, FormClosingEventArgs e) // Aktualizacja list przedmiotów w CharactersForm
        {
            CharactersForm.SetItemsList = ItemShopList;
            CharactersForm.SetCharacterItems = CharacterItemsList;
        }

        private void ItemsButton_Click(object sender, EventArgs e)
        {
            if (ItemsManagerForm == null)
                ItemsManagerForm = new ItemsForm(this, ItemShopList);
            ItemsManagerForm.Show();
        }
    }
}
