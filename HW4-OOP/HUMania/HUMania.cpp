#include <iostream>
#include "HUMania.hpp"

void HUMania::drawObjects()
{
    // call draw functions of all the objects here
    p1.draw();

}

void HUMania::createObject(int x, int y)
{
    std::cout << "Mouse clicked at: " << x << " -- " << y << std::endl;
}
