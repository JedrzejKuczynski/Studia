using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProgramowanieWizualne
{
    public class Profession
    {
        public int ID { get; set; }
        public string Description { get; set; }
        public int Might { get; set; }
        public int Defence { get; set; }
        public int CarryWeight { get; set; }

        public Profession(string profession, int level)
        {
            if (profession == "Warrior")
            {
                ID = 1;
                Description = "Warrior";
                Might = 30;
                Defence = 50;
                CarryWeight = 150;
                LevelUp(level, profession);
            }else if (profession == "Mage")
            {
                ID = 2;
                Description = "Mage";
                Might = 50;
                Defence = 30;
                CarryWeight = 100;
                LevelUp(level, profession);
            }
        }

        void LevelUp(int level, string profession)
        {
            if (profession == "Warrior")
            {
                for (int i = 0; i < level; i++)
                {
                    Might = (int)Math.Round(Might * 1.1);
                    Defence = (int)Math.Round(Defence * 1.2);
                    CarryWeight += 10;
                }
            } else if (profession == "Mage")
            {
                for (int i = 0; i < level; i++)
                {
                    Might = (int)Math.Round(Might * 1.2);
                    Defence = (int)Math.Round(Defence * 1.1);
                    CarryWeight += 5;
                }
            }
        }
    }
}
