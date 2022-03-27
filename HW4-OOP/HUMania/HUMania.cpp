#include <iostream>
#include "HUMania.hpp"

void HUMania::drawObjects()
{
    // call draw functions of all the objects here
    for (int i = 0; i < pigeons.size(); i++) // creating and animating pigeons which have been pushed into
    // their vectors
    {
        pigeons[i]->draw();
        pigeons[i]->fly();
    }

    for (int i = 0; i < bees.size(); i++) // creating and animating bees which have been pushed into
    // their vectors
    {
        bees[i]->draw();
        bees[i]->fly();

        static int bee_count = 1; // for showing bee no. being deleted

        if (!bees[i]->bee_delete())
        { // if bee is out of the screen

            delete bees[i];                                       // the vector of that bee is deleted
            bees.erase(bees.begin() + i);                         // the memory of that specific bee is deleted
            cout << "Bee " << bee_count << " is removed" << endl; // for checking deletion functionality

            bee_count++; // for bee count being popped off
        }
    }

    for (int i = 0; i < butterflies.size(); i++) // creating and animating butterflies which have been pushed into
    // their vectors
    {
        butterflies[i]->draw();
        butterflies[i]->fly();
    }
}

void HUMania::createObject(int x, int y)
{
    std::cout << "Mouse clicked at: " << x << " -- " << y << std::endl;
    int choice; // this is the choice variable which stores the random number between 1 to 3

    choice = 1 + (rand() % 3); // generates no.s b/w 1 to 3

    std::cout << " Choice no. " << choice << endl; // for checking the random logic

    if (choice == 1)
    {                           // if choice is 1, then we push bee into bees vector at the
                                // specific location on screen and a starting state of 0 in state variable
        Bee *b = new Bee(x, y); // creating dynamic object and pushing it into its vector
        bees.push_back(b);
    }

    else if (choice == 2)
    {                                 // if choice is 1, then we push pigeon into pigeons vector at the
                                      // specific location on screen and a starting state of 0 in state variable
        Pigeon *p = new Pigeon(x, y); // creating dynamic object and pushing it into its vector
        pigeons.push_back(p);
    }

    else
    {                                         // if choice is 3, then we push butterfly into butterflies vector at the
                                              // specific location on screen and a starting state of 0 in state variable
        Butterfly *but = new Butterfly(x, y); // creating dynamic object and pushing it into its vector
        butterflies.push_back(but);
    }
}
