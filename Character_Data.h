#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <iostream>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;

//https://docs.google.com/spreadsheets/d/1JX2w-r2fuvWuNgGb6D3Cs4wHQKLFegZe2jhbBuIhCG8/edit#gid=21


//Global Variables:
const int maxKB = 2500;
const double elecMulti = 1.5;
const double ccMulti = (2 / 3);
const int tumbleThresh = 80;
const double vcancelMulti = .95;
const int maxHitlag = 20;
const double hitstunMulti = .4;
const int maxShieldHP = 60;
const double shieldDamageMulti = .7;
const double kbDecay = .051;

//look into airdodge units of movement. Airdodge velocity value? Is friction decremented by airdodge momentum multiplier (.9)?
// or decremented by traction? Probably both


//Character Attribute Maps
//keyed to strings of the character's name



const map<string, int> chrWeight = { {"bowser", 117},{"falcon", 104},{"dk", 114},{"doc", 100},{"falco", 80},{"fox", 75},{"gnw", 60},{"ganon", 109},{"ics", 88},
                                     {"jiggs", 60},{"kirby", 70},{"link", 104},{"luigi", 100},{"mario", 100},{"marth", 87},{"mewtwo", 85},{"ness", 94},{"peach", 90},
                                     {"pichu", 55},{"pika", 80},{"roy", 85},{"samus", 110},{"sheik", 90},{"yoshi", 108},{"ylink", 85},{"zelda", 90} };

const map<string, double> chrGravity = { {"bowser", .13},{"falcon", .13},{"dk", .1},{"doc", .095},{"falco", .17},{"fox", .23},{"gnw", .095},{"ganon", .13},{"ics", .1},
                                         {"jiggs", .064},{"kirby", .08},{"link", .11},{"luigi", .069},{"mario", .095},{"marth", .095},{"mewtwo", .082},{"ness", .09},{"peach", .08},
                                         {"pichu", .11},{"pika", .11},{"roy", .114},{"samus", .066},{"sheik", .12},{"yoshi", .093},{"ylink", .11},{"zelda", .073} };

const map<string, double> chrJumpForceF = { {"bowser", 2.8},{"falcon", 3.1},{"dk", 2.7},{"doc", 2.3},{"falco", 4.1},{"fox", 3.68},{"gnw", 2.3},{"ganon", 2.6},{"ics", 2.6},
                                         {"jiggs", 1.6},{"kirby", 2},{"link", 2.5},{"luigi", 2.4},{"mario", 2.3},{"marth", 2.4},{"mewtwo", 2.3},{"ness", 2.5},{"peach", 2.2},
                                         {"pichu", 2.6},{"pika", 2.6},{"roy", 2.6},{"samus", 2.1},{"sheik", 2.8},{"yoshi", 2.5},{"ylink", 2.62},{"zelda", 2.1} };

const map<string, double> chrJumpForceS = { {"bowser", 1.6},{"falcon", 1.9},{"dk", 1.6},{"doc", 1.4},{"falco", 1.9},{"fox", 2.1},{"gnw", 1.4},{"ganon", 2},{"ics", 1.4},
                                         {"jiggs", 1.05},{"kirby", 1.5},{"link", 1.5},{"luigi", 1.4},{"mario", 1.4},{"marth", 1.5},{"mewtwo", 1.4},{"ness", 1.5},{"peach", 1.6},
                                         {"pichu", 1.7},{"pika", 1.7},{"roy", 1.5},{"samus", 1.7},{"sheik", 2.14},{"yoshi", 1.8},{"ylink", 1.5},{"zelda", 1.6} };

const map<string, double> chrJumpForceDJ = { {"bowser", 2.8},{"falcon", 2.79},{"dk", 2.457},{"doc", 2.3},{"falco", 4.018},{"fox", 4.416},{"gnw", 2.3},{"ganon", 2.47},{"ics", 2.6},
                                          {"jiggs", 0.0},{"kirby", 0.0},{"link", 2.2},{"luigi", 2.16},{"mario", 2.3},{"marth", 2.112},{"mewtwo", 10.0},{"ness", 10.0},{"peach", 10.0},
                                          {"pichu", 2.6},{"pika", 2.6},{"roy", 2.288},{"samus", 1.89},{"sheik", 3.08},{"yoshi", 10},{"ylink", 2.3056},{"zelda", 1.806} };
//jiigs and kirby have multiple DJs and multiple DJ forces. Using 0.0 is a garbage workaround to let me if/else check them
//ditto for the DJC characters (Peach, yoshi, ness, m2), except with a value of 10 since theirs are mapped to their animation. 
//I will include a flat vector with the vertical velocity on each frame once I get around to it


const map<string, double> chrMaxFall = { {"bowser", 1.9},{"falcon", 2.9},{"dk", 2.4},{"doc", 1.7},{"falco", 3.1},{"fox", 2.8},{"gnw", 1.7},{"ganon", 2},{"ics", 1.6},
                                          {"jiggs", 1.3},{"kirby", 1.6},{"link", 2.13},{"luigi", 1.6},{"mario", 1.7},{"marth", 2.2},{"mewtwo", 1.5},{"ness", 1.83},{"peach", 1.5},
                                          {"pichu", 1.9},{"pika", 1.9},{"roy", 2.4},{"samus", 1.4},{"sheik", 2.13},{"yoshi", 1.93},{"ylink", 2.13},{"zelda", 1.4} };

const map<string, double> chrFastFall = { {"bowser", 117},{"falcon", 104},{"dk", 114},{"doc", 100},{"falco", 80},{"fox", 75},{"gnw", 60},{"ganon", 109},{"ics", 88},
                                          {"jiggs", 60},{"kirby", 70},{"link", 104},{"luigi", 100},{"mario", 100},{"marth", 87},{"mewtwo", 85},{"ness", 94},{"peach", 90},
                                          {"pichu", 55},{"pika", 80},{"roy", 85},{"samus", 110},{"sheik", 90},{"yoshi", 108},{"ylink", 85},{"zelda", 90} };


//Hitlag Calculator
int hitLag(double damage, bool elec)
{
    double elecConst = 1;
    double* ecRef = &elecConst;
    if (elec == true)
    {
        *ecRef = elecMulti;
    }
    int hLag = floor(floor((damage * 0.3333334 + 3)) * elecConst);
    return hLag;
}

//Shieldstun Calculator
double shieldStun(double damage)
{
    double stun = floor(((4.45 + damage) / 2.235));

    return stun;
}


//Jump Height Calculator
void calcHeight(double velocity, double gravity, double fallMax)
{
    double vel{ velocity };
    double grav{ gravity };
    double height{ vel };

    std::cout << "Frame: 1" << '\t' << "Velocity: " << vel << "\t \t" << "Height: " << height << '\n';

    for (int i = 2; height >= 0; ++i)
    {
        vel -= (grav);
        if (vel < -fallMax)
            vel = -fallMax;
        height += (vel);

        std::cout << "Frame: " << i << '\t';
        std::cout << "Velocity: " << vel << "\t \t \t";

        if (vel > 0)
            std::cout << "Height(^): " << height << '\n';
        else if (vel == 0)
            std::cout << "Height(-): " << height << '\n';
        else if (vel == -fallMax)
            std::cout << "Height(Y): " << height << '\n';
        else if (vel < 0)
            std::cout << "Height(V): " << height << '\n';

    }
    std::cout << '\n' << "=================================================" << '\n';
}

void jHeightMain()
{
    //double aJumpX{ 0 }; temporarily using flat value
    double gravity{ 0 };
    double fallMax{ 0 };
    double fhVelocity{ 0 };
    double shVelocity{ 0 };
    double djVelocity{ 0 };
    std::string chrName;

    std::cout << "Character: ";
    std::cin >> chrName;
    gravity = chrGravity.at(chrName);
    fallMax = chrMaxFall.at(chrName);
    fhVelocity = chrJumpForceF.at(chrName);
    shVelocity = chrJumpForceS.at(chrName);
    djVelocity = chrJumpForceDJ.at(chrName);


    std::cout << '\n' << '\n' << chrName << '\n' << "==========" << '\n';

    std::cout << "Fullhop:" << '\n';
    calcHeight(fhVelocity, gravity, fallMax);
    std::cout << "Shorthop:" << '\n';
    calcHeight(shVelocity, gravity, fallMax);
    
    if (djVelocity != 0.0 && djVelocity != 10.0)
    {
        std::cout << "Doublejump:" << '\n';
        calcHeight((djVelocity - gravity), gravity, fallMax);
    }
    else
        std::cout << "Weird doublejumps, working on calculating in the future =(";
    system("Pause");
    return;
}














/*
class Char_Data
{
public:
    //print details of character
    //compare 2 characters/attributes
    //





    std::string name = " ";
    //stun/lag calcs
    int weight;
    //grounded movement
    double walkInitial{};
    double walkAccel{}; //max walk acceleration (i.e. minimum accel + max stick held accel)
    double walkMax{}; //max walk speed
    double traction{}; //when above a max speed on the ground	the traction value will decrement the speed value.
    double dashInitial{}; //initial dash speed	CAN exceed dash/run MAX speed (see falco)
    double dashRunAccel{}; //Same as walkaccel but for dash and run
    double dashRunMax{};  //if max is below initial	traction is used
    int dashFrames{}; //total frames of dash before entering run
    //jump & air stats
    double jumpSquat{}; // airborne 1 frame after this value
    double g2aHInitial{}; // modifies initial air horizontal velocity if control stick his held left or right during jumpsquat
    double fhJumpForce{}; // the initial speed at which a character rises when fullhoping	modified over time by gravity
    double shJumpForce{}; // see above, but for shorthop
    double g2aMomentum{}; //ground to air momentum multiplier
    double g2aMaxH{}; //custom "ceiling" value for jumping H velocity (i.e. g2aHInitial + (grounded movespeed * g2aMomentum), with a max of this value)
    double maxAirSpeed{}; //max air speed when already in the air. When not in hitstun and above this value, your speed will be reduced by the Air Fricion value each frame
    double airJumpMultiplier{}; //modifies fhJumpForce to determine DJ jump force
    int jumpCount{};
    double gravity{};
    double maxFallSpeed{}; //gravity will decrement vertical velocity until this value is reached
    double fastFallSpeed{}; //press down when falling to instantly replace current vertical velocity with FF's value. Many animations can "reset" fastfall back to regular fall, such as doublejump's FallAerial
    double airAccel{};
    double airFriction{};
    //misc
    double shieldSize{};
    double ledgeJumpVelocity{}; //vertical "jump force" for ledge jump
    int defaultLandLag{}; //turns out this isn't just "4". Bowser, DK, and ganon have unique values
    double walljumpHVel{}; //pretty universally 1.3, but falcon's is different
    double walljumpVVel{}; //i think these values are used for walljump techs too?
    bool walljump{};
    //add roll/spotdodge/airdodge frames
};


Char_Data Bowser{"Bowser", 117, .03, .05, .65, .06, 1, .06, 1.5, 8, 1, 2.8, 1.6, .9, 1, .8, 1, 2, .13, 1.9, 2.4, .5, .01, 31.25, 2.2, 6, 1.3, 2.8, false };

Char_Data Falcon{ "Falcon", 104, 0.15, 0.1, 0.85, 0.08, 2, 1.51, 2.3, 4, 0.95, 3.1, 1.9, 0.75, 2.1, 1.12, 0.9, 2, 0.13, 2.9, 3.5, 0.06, 0.01, 15, 3.29, 4, 0.4, 3.1, true};

Char_Data DK{ "DK", 114, 0.1, 0.1, 1.2, 0.08, 1.6, 0.07, 1.6, 5, 1, 2.7, 1.6, 0.8, 1.6, 1, 0.91, 2, 0.1, 2.4, 2.96, 0.04, 0.02, 17.5, 2.7, 5, 1.3, 2.7, false };

Char_Data Doc{"Doc", 100, 0.1, 0.1, 1.1, 0.06, 1.5, 0.08, 1.5, 4, 1, 2.3, 1.4, 0.8, 1.5, 0.9, 1, 2, 0.095, 1.7, 2.3, 0.044, 0.016, 10.75, 2.3, 4, 1.3, 2.3, true };

Char_Data Falco{"Falco", 80, .2, .1, 1.4, .08, 1.9, .12, 1.5, 11, 5, .7, 4.1, 1.9, 1, 1.7, .83, .94, 2, .13, 3.1, 3.5, 12.5, 3.9, 4, 1.3, 3.6, true};

Char_Data Fox{"Fox", 75, 0.2, 0.1, 1.6, 0.08, 1.9, 0.12, 2.2, 3, 0.72, 3.68, 2.1, 0.83, 1.7, 0.83, 1.2, 2, 0.23, 2.8, 3.4, 0.08, 0.02, 14.375, 4, 4, 1.3, 3.3, true};

Char_Data GnW{"GnW", 60, 0.1, 0.1, 1.1, 0.06, 1.5, 0.08, 1.5, 4, 1, 2.3, 1.4, 0.8, 1.5, 1, 1, 2, 0.095, 1.7, 2.3, 0.05, 0.016, 10.75, 2.8, 4, 1.3, 2.3, false};

Char_Data Ganon{"Ganon", 109, 0.08, 0, 0.73, 0.07, 1.3, 0.09, 1.35, 6, 0.9, 2.6, 2, 0.75, 1.8, 0.78, 0.95, 2, 0.13, 2, 2.6, 0.06, 0.02, 15, 3.5, 5, 1.3, 2.6, true};

Char_Data ICs{"ICs", 88, 0.085, 0.1, 0.95, 0.035, 1.4, 0.07, 1.4, 3, 0.6, 2.6, 1.4, 0.8, 1.4, 0.7, 1, 2, 0.1, 1.6, 2, 0.047, 0.02, 10.75, 2.6, 4, 1.3, 2.6, false};

Char_Data Jiggs{"Jiggs", 60, 0.16, 0.1, 0.7, 0.09, 1.4, 0.085, 1.1, 5, 0.7, 1.6, 1.05, 1, 1.35, 1.35, 0, 6, 0.064, 1.3, 1.6, 0.28, 0.05, 13.125, 1.8, 4, 1.3, 1.6, false};

Char_Data Kirby{"Kirby", 70, 0.16, 0.1, 0.85, 0.08, 1.4, 0.1, 1.4, 3, 0.9, 2, 1.5, 0.8, 1.4, 0.78, 0, 6, 0.08, 1.6, 2, 0.06, 0.02, 14.7, 2, 4, 1.3, 2, false};

Char_Data Link{"Link", 104, 0.2, 0.1, 1.2, 0.1, 1.3, 0.12, 1.3, 6, 1, 2.5, 1.5, 0.8, 1.2, 1, 0.88, 2, 0.11, 2.13, 3, 0.06, 0.005, 11.625, 2.6, 4, 1.3, 2.6, true};

Char_Data Luigi{"Luigi", 100, 0.1, 0.1, 1.1, 0.025, 1.3, 0.08, 1.34, 4, 0.8, 2.5, 1.4, 0.8, 0.75, 0.68, 0.9, 2, 0.069, 1.6, 2, 0.015, 0.01, 10.75, 2.1, 4, 1.3, 2.1, false};

Char_Data Mario{"Mario", 100, 0.1, 0.1, 1.1, 0.06, 1.5, 0.08, 1.5, 4, 1, 2.3, 1.4, 0.8, 1.5, 0.86, 1, 2, 0.095, 1.7, 2.3, 0.045, 0.016, 10.75, 2.3, 4, 1.3, 2.3, true};

Char_Data Marth{"Marth", 87, 0.15, 0, 1.6, 0.06, 1.5, 0.06, 1.8, 4, 1, 2.4, 1.5, 0.8, 1.2, 0.9, 0.88, 2, 0.085, 2.2, 2.5, 0.05, 0.005, 11.75, 2.4, 4, 1.3, 2.4, false};

Char_Data Mewtwo{"Mewtwo", 85, 0.3, 0.1, 1, 0.04, 1.4, 0.1, 1.4, 5, 0.9, 2.3, 1.4, 0.7, 1.4, 1.2, 1, 2, 0.082, 1.5, 2.3, 0.05, 0.016, 16.25, 2.3, 4, 1.3, 2.3, false};

Char_Data Ness{"Ness", 94, 0.08, 0.1, 0.84, 0.06, 1.3, 0.06, 1.4, 4, 1, 2.5, 1.5, 0.8, 1.3, 0.93, 0.85, 2, 0.09, 1.83, 2.2, 0.06, 0.03, 13.75, 2.5, 4, 1.3, 2.5, false};

Char_Data Peach{"Peach", 90, 0.2, 0.1, 0.85, 0.1, 1.2, 0.12, 1.3, 5, 0.7, 2.2, 1.6, 0.7, 1.1, 1.1, 0.7, 2, 0.08, 1.5, 2, 0.07, 0.005, 11.875, 2.2, 4, 1.3, 2.2, false};

Char_Data Pichu{"Pichu", 55, 0.15, 0.1, 1.24, 0.1, 1.8, 0.1, 1.72, 3, 0.8, 2.6, 1.7, 0.8, 1.8, 0.85, 1, 2, 0.11, 1.9, 2.5, 0.05, 0.01, 24.3, 2.6, 2, 1.3, 2.6, true};

Char_Data Pika{"Pika", 80, 0.15, 0.1, 1.24, 0.09, 1.8, 0.1, 1.8, 3, 0.8, 2.6, 1.7, 0.8, 1.8, 0.85, 1, 2, 0.11, 1.9, 2.7, 0.05, 0.01, 12, 2.6, 4, 1.3, 2.6, false};

Char_Data Roy{"Roy", 85, 0.15, 0, 1.2, 0.06, 1.4, 0.07, 1.61, 5, 1, 2.6, 1.5, 0.8, 1.2, 0.9, 0.88, 2, 0.114, 2.4, 2.9, 0.05, 0.005, 11.75, 2.4, 4, 1.3, 0.24, false};

Char_Data Samus{"Samus", 110, 0.3, 0.1, 1, 0.06, 1.86, 0.12, 1.4, 3, 1, 2.1, 1.7, 0.8, 1.3, 0.89, 0.9, 2, 0.066, 1.4, 2.3, 0.0325, 0.01, 16.25, 2.1, 4, 1.3, 2.1, true};

Char_Data Sheik{"Sheik", 90, 0.2, 0.1, 1.2, 0.08, 1.7, 0.12, 1.8, 3, 0.8, 2.8, 2.14, 0.8, 1.4, 0.8, 1.1, 2, 0.12, 2.13, 3, 0.06, 0.04, 11.625, 2.8, 4, 1.3, 2.8, true};

Char_Data Yoshi{"Yoshi", 108 / 111, 0.16, 0.1, 1.15, 0.06, 1.33, 0.1, 1.6, 5, 0.93, 2.5, 1.8, 0.7, 1.5, 1.2, 1.3, 2, 0.093, 1.93, 2.93, 0.048, 0.013, 6, 2.3, 4, 1.3, 2.3, false};

Char_Data Ylink{"Ylink", 85, 0.2, 0.1, 1.2, 0.08, 1.8, 0.12, 1.6, 4, 1, 2.62, 1.5, 0.8, 1.2, 1, 0.88, 2, 0.11, 2.13, 2.2, 0.06, 0.005, 11.625, 2.6, 4, 1.3, 2.6, true};

Char_Data Zelda{"Zelda", 90, 0.2, 0.1, 0.7, 0.1, 1.1, 0.12, 1.1, 6, 0.7, 2.1, 1.6, 0.7, 1.1, 0.95, 0.86, 2, 0.073, 1.4, 1.85, 0.048, 0.005, 11.875, 2.1, 4, 1.3, 2.1, false};
*/

