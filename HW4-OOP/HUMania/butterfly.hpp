#include "drawing.hpp"


class Butterfly{
    // declaring variables
    SDL_Rect srcRect, moverRect;
    int state = 0;
    int prob = 0;
    bool sitting = false;
    int sitting_time = 1 + (rand() % 20);
    bool move_down = true;

    public:
        // calling the constructors, draw and fly functions
        void draw();
        void fly();
        Butterfly();
        Butterfly(int x, int y); 
};