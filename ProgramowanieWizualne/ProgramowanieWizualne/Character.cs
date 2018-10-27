using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProgramowanieWizualne
{
    public class Character
    {
        public static int ID = 0;
        public int Character_ID { get; set; }
        public string Name { get; set; }
        public int Level { get; set; }
        public int Might { get; set; }
        public int Defence { get; set; }
        public string Description { get; set; }
        public int CarryWeight { get; set; }
        public int CurrentWeight { get; set; }
        public List<Item> CharacterItems { get; set; }
        public Profession Profession;

        // Konstruktor odpowiedzialny za dodawanie postaci
        public Character(string name, int lvl, string description, string profession)
        {

            // Zabezpieczenia w postaci wartości domyślnych
            if (name.Length > 0)
                Name = name;
            else
                Name = "Gall";

            if (lvl <= 0)
                lvl = 1;

            if (description.Length > 0)
                Description = description;
            else
                Description = "Anonim";

            Profession = new Profession(profession, lvl);
            Character_ID = ID;
            Level = lvl;
            Might = Profession.Might;
            Defence = Profession.Defence;
            CarryWeight = Profession.CarryWeight;
            CurrentWeight = 0;
            CharacterItems = new List<Item>();
            ID++;
        }

        // Konstruktor odpowiedzialny za wczytywanie postaci z pliku
        public Character(int char_id, string name, string description, string profession, int lvl, int might, int defence, int current_carry, int carry_weight, List<Item> items)
        {
            Profession = new Profession(profession, lvl);
            Character_ID = char_id;
            Name = name;
            Description = description;
            Level = lvl;
            Might = might;
            Defence = defence;
            CarryWeight = carry_weight;
            CurrentWeight = current_carry;
            CharacterItems = items;
            ID++;
        }
    }
}
