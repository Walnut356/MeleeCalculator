#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Character_Data.h"




double getInput()
{
    double damage;
    cin >> damage;
    return damage;
}

bool getBool()
{
    char yon;
    cin >> yon;
    if (yon == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print(const string& input)
{
    cout << input;
    return;
}

void pause()
{
    std::cin.ignore();
    cin.get();
}

int main()
{
    cout << "Fallspeed or Shieldstun/Hitlag (f/s): ";

    char startInput;
    cin >> startInput;

    if (startInput == 's')
    {
        bool cont = false;
        do
        {
            print("How much damage does the move do? - ");

            double damage = getInput();

            print("Is the move electric? (y/n) - ");

            bool elec = getBool();

            double sStun = shieldStun(damage);
            double hLag = hitLag(damage, elec);

            cout << "Damage entered: " << damage << '%' << '\n';
            cout << "Shieldstun: " << sStun << " frames" << '\n';
            cout << "Hitlag: " << hLag << " frames" << '\n' << '\n';
            print("Would you like to continue? (y/n) - ");
            cont = getBool();
        } while (cont == true);

        cout << "Press enter to exit...";
        pause();

    }
    else
    {
        jHeightMain();
    }
    system("Pause");
    return 0;
}

/*
void stale()
{
    vector<double> staleQueue = { .09, .08, .07, 06, .05, .04, .03, .02, .01 };
     Where does the move appear in the stale move queue?
    pointer interation extract number, add all numbers together, modify damage by resultant double staleMultipl += [pointer math]

    or use binary representation for vector input, and use pointers to vector values to multiply by stale move queue values, then add values together for staleMultiplier

    int stale = 0;
    while (stale >= 0;)
    {
        int fDamage;
        int queue = (stale / 100);
        fDamage *= queue;
        --stale;
        queue -= .01;
    }
}
*/




