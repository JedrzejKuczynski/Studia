using System;
using System.Collections.Generic;

namespace ProgramowanieWizualne
{
    public class Item
    {
        public static int ID = 0;
        public int Item_ID { get; set; }
        public string Name { get; set; }
        public string Type { get; set; }
        public string Description { get; set; }
        public List<string> Requirements { get; set; }
        public List<Tuple<string, int>> Bonus { get; set; }
        public List<string> Properties { get; set; }
        public int Weight { get; set; }

        // Konstruktor odpowiedzialny za dodawanie przedmiotów
        public Item(string name, string type, string description, List<string> requirements, List<Tuple<string, int>> bonus, List<string> properties, int weight)
        {
            Item_ID = ID;
            Name = name;
            Type = type;
            Description = description;
            Requirements = requirements;
            Bonus = bonus;
            Properties = properties;
            Weight = weight;
            ID++;
        }

        // Konstruktor odpowiedzialny za wczytywanie przedmiotów z pliku
        public Item(int item_id, string name, string type, string description, List<string> requirements, List<Tuple<string, int>> bonus, List<string> properties, int weight)
        {
            Item_ID = item_id;
            Name = name;
            Type = type;
            Description = description;
            Requirements = requirements;
            Bonus = bonus;
            Properties = properties;
            Weight = weight;
            ID++;
        }
    }
}
