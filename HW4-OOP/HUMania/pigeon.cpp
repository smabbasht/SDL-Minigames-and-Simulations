#include "pigeon.hpp"
// pigeon implementation will go here.

Pigeon::Pigeon(){}

Pigeon::Pigeon(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {7,88,160,103};

    // it will display pigeon on x = 30, y = 40 location, the size of pigeon is 50 width, 60 height
    moverRect = {x, y, 50, 50};
}


void Pigeon::draw(){
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    moverRect.x += 5;   // this moves the pigeon

    // i have implemented additional function of sweeping in pigeon.

    int prob = 1 + (rand() % 100); // this calculates probablity of pigeon sweeping.

    if (prob == 1) {  // if probablity is 1 then pigeon would sweep
        sweeping = true;
    }

    if (sweeping) {
        if (sweeping_time >= 0) {  // until the sweeping time is 0. The pigeon would sweep at state 0
            sweeping_time --; state = 0;  
        }
        else {
            sweeping_time = 1 + (rand() % 7);   // sweeping time is also random 
            sweeping = false;  
        }
    }

    if(moverRect.x > 1000){ // if the object reaches the end of the right screen, the x pixels are set to -30 to have a continuous motion
        moverRect.x = -10;
    }

    fly(); // calling fly function for animation
}

void Pigeon::fly(){
    // 
    if(state == 0){// the initial state of the pigeon
        srcRect = {7, 88 ,155,103};
        state ++; // the state changes to the next state
    }

    else if(state == 1){ // the second state of the pigeon
        srcRect = {0,237,153,84};
        state ++; // the state changes to the next state
    }

    else if(state == 2){ // the final state of the pigeon
        srcRect = {2,361,159,124};
        state -= 2;// the state is resetted and the process repeats
    }
}


