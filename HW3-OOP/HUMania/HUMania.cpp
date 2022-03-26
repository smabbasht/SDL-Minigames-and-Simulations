#include <iostream>
#include "HUMania.hpp"
#include <vector>
using namespace std;

// These are three vectors which will be then used to animate the Unit structures
vector<Unit> bees;
vector<Unit> pigeons;
vector<Unit> butterflies;


/////////////////////     Added Features    //////////////////////////////////
// The program now runs with 7 different background location which are selected randomly which includes different campus locations along with the one provided as default.
// For this purpose, I have added the following code in game.cpp to generate random backgrounds

// string backgrounds[7] = {"Amphitheater.png", "Baithak.png", "Entrance.png", "Garden.png", "Cafeteria.png", "Central_Street.png", "Water_Courtyard.png"};
// int background_select = rand() % 7;
// ::string background_image = backgrounds[background_select];

// You can now control the speed by which the structures move on the screen through speed variable and height and width
// of the produced pigeon, bee or butterfly with speed, width and height variables respectively.
// You can control the size of individual structures which makes it realistic as it makes the relative sizes of pigeon, butterfly and bees nearer to reality.
// Control Variables:

int pigeon_width = 100;
int pigeon_height = 100;
int butterfly_width = 40;
int butterfly_height = 40;
int bee_width = 20;
int bee_height = 20;
int speed = 25;

/////////////////////   Helper Ammendment   //////////////////////////////////
// I have also added a structure variable (int) phase in Unit structure, It faciliates in animating the Unit structures in their three provided phases.


/////////////////////   Helper Functions   //////////////////////////////////
// These functions handles the object once it gets generated through create and draw objects.

Unit MovePigeon(Unit pigeon)
{
    if (pigeon.phase == 1) // Phase gets initialzed with 1 in CreateObject()
    {
        pigeon.srcRect = {7, 88, 155, 103}; // The corresponding area of assets.png is selected
        pigeon.phase++;    // Next phase is selcted so that in the next iteration it will satisfy the condition below thus the next image or phase will be selected
    }
    else if (pigeon.phase == 2)
    {
        pigeon.srcRect = {0, 237, 153, 84}; // The corresponding area of assets.png is selected
        pigeon.phase++;    // Next phase is selcted so that in the next iteration it will satisfy the condition below thus the next image or phase will be selected
    }
    else if (pigeon.phase == 3)
    {
        pigeon.srcRect = {2, 361, 159, 124}; // The corresponding area of assets.png is selected
        pigeon.phase -= 2; // Next phase is selcted so that in the next iteration it will satisfy the condition below thus the next image or phase will be selected
    }
    return pigeon;
}

// The two functions MoveBee() & MoveButterfly operates simlar to MovePigeon.

Unit MoveBee(Unit bee)
{
    if (bee.phase == 1)
    {
        bee.srcRect = {527, 138, 194, 115};
        bee.phase++;
    }
    else if (bee.phase == 2)
    {
        bee.srcRect = {527, 253, 194, 115};
        bee.phase++;
    }
    else if (bee.phase == 3)
    {
        bee.srcRect = {540, 370, 193, 115};
        bee.phase -= 2;
    }
    return bee;
}

Unit MoveButterfly(Unit butterfly)
{
    if (butterfly.phase == 1)
    {
        butterfly.srcRect = {257, 24, 173, 134};
        butterfly.phase++;
    }
    else if (butterfly.phase == 2)
    {
        butterfly.srcRect = {257, 182, 192, 214};
        butterfly.phase++;
    }
    else if (butterfly.phase == 3)
    {
        butterfly.srcRect = {248, 432, 248, 179};
        butterfly.phase -= 2;
    }
    return butterfly;
}


void drawObjects(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    int speed = 15; // this variable can be used to modulate the speed of the Units flying.
    for (int i = 0; i < pigeons.size(); i++)
    {
        pigeons[i] = MovePigeon(pigeons[i]);
        SDL_RenderCopy(gRenderer, assets, &pigeons[i].srcRect, &pigeons[i].moverRect);
        pigeons[i].moverRect.x += speed; // it adds the speed value to x location of Unit object which moves the structure rightwards.
        if (pigeons[i].moverRect.x >= 990){ // if the Unit structure is getting out of the screen container through right, 
            pigeons[i].moverRect.x = 0;     // then it comes in from left side.
        }
    }
    // The loops below operates in a similar fashion
    for (int i = 0; i < bees.size(); i++)
    {
        bees[i] = MoveBee(bees[i]);
        SDL_RenderCopy(gRenderer, assets, &bees[i].srcRect, &bees[i].moverRect);
        bees[i].moverRect.x += speed;
        if (bees[i].moverRect.x >= 990){
            bees[i].moverRect.x = 0;    
        }
    }

    for (int i = 0; i < butterflies.size(); i++)
    {
        butterflies[i] = MoveButterfly(butterflies[i]);
        SDL_RenderCopy(gRenderer, assets, &butterflies[i].srcRect, &butterflies[i].moverRect);
        butterflies[i].moverRect.x += speed;
        if (butterflies[i].moverRect.x >= 990){
            butterflies[i].moverRect.x = 0;    
        }
    }
}

void createObject(int x, int y)
{
    int Unit_selector = rand() % 3;    // Randomizes the generation of pigeon, bee & butterfly
    if (Unit_selector == 0)
    {
        Unit pigeon_gen = {{7, 88, 155, 103}, {x, y, pigeon_width, pigeon_height}}; // initializes the object with desired part of assets.png anf location (mouse_x, mouse_y) with width and height specified.
        pigeon_gen.phase = 1;          // Phase Initialization with 1
        pigeons.push_back(pigeon_gen); // faciliates the modulation & animation of more than one pigeons.
        cout << "Pigeon    produced at: (" << x << ", " << y << ")" << endl; // Outputs the location of generation.
    }
    // The conditions below operates in a similar fashion.
    else if (Unit_selector == 1)
    {
        Unit bee_gen = {{540, 370, 193, 115}, {x, y, bee_width, bee_height}};
        bee_gen.phase = 1;
        bees.push_back(bee_gen); //
        cout << "Bee       produced at: (" << x << ", " << y << ")" << endl;
    }
    else if (Unit_selector == 2)
    {
        Unit butterfly_gen = {{257, 24, 173, 134}, {x, y, butterfly_width, butterfly_height}};
        butterfly_gen.phase = 1;
        butterflies.push_back(butterfly_gen); //
        cout << "Butterfly produced at: (" << x << ", " << y << ")" << endl;
    }
}
