#include "drawing.hpp"

class Bee{
    // declaring variables
    private:
    SDL_Rect srcRect, moverRect;
    int state = 0;
    int prob;
    int hover_time = 10;
    bool hover = false; 
    bool on_screen = true;
    
    public:
        // calling the constructors, draw and fly functions
        void draw();
        void fly();
        Bee();
        Bee(int x, int y); 
        bool bee_delete();
};