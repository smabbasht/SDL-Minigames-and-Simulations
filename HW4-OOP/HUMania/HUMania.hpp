#include<SDL.h>
#include "pigeon.hpp"
#include "bee.hpp"
#include "butterfly.hpp"
#include<vector>
#include<list>
using namespace std;

class HUMania{

    //Right now we're creating one pigeon, 
    Pigeon p1;


    // In the solution you have to create vectors of pigeons, eggs, and nests    
    vector<Pigeon*> pigeons;
    vector<Bee*> bees;
    vector<Butterfly*> butterflies;

    public:

    
    void drawObjects(); 
    void createObject(int, int);

    ~HUMania(){
        while(!pigeons.empty()) {
            delete pigeons.back();
            pigeons.pop_back();
        }

        while(!butterflies.empty()) {
            delete butterflies.back();
            butterflies.pop_back();
        }
    };

};