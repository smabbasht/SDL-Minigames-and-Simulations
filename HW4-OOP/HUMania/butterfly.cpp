#include "butterfly.hpp"

Butterfly::Butterfly() {}

Butterfly::Butterfly(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {256, 24, 174,134};

    // it will display pigeon on x = x touched point, y = y touched point, the size of pigeon is 50 width, 50 height
    moverRect = {x, y, 50, 50};
}

// functionalities

void Butterfly::draw(){
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect); // creates object
    if(move_down == true){ // move down variable is true initially
        // it moves the butterfly at y=x line diagonally down
        if (moverRect.y < 550) {
            moverRect.x += 5;
            moverRect.y += 5;
        }
        // if it hits the bottom, move_down gets false
        else if(moverRect.y > 550){
            prob = 1 + (rand() % 100);
            if (prob <= 33) {
                sitting = true;
            }

            if (sitting_time >= 0 && sitting == true) {
                sitting_time -= 1;
                state = 0;
            }
            else {
                move_down = false;
                sitting_time = 1 + (rand() % 20);
                sitting = false;
            }
        }
         
    }
    // it moves the butterfly at y=x line diagonally up
    else if(move_down == false){
    
        moverRect.x += 5;
        moverRect.y -= 5;

        if (moverRect.y <= 0) {// if it hits the top, move_down gets true and the process repeats
            move_down = true;
        }
    }

    if(moverRect.x > 1000){ // if the object reaches the end of the right screen, the x pixels are set to -30 to have a continuous motion
        moverRect.x = -30;
    }
    fly(); // calling fly function for animation
}

void Butterfly::fly(){    
    if(state == 0){ // the initial state of the butterfly
        srcRect = {256, 24, 174,134};
        state ++; // the state changes to the next state
    }

    else if(state == 1){ // the second state of the butterfly
        srcRect =  {257, 182,192,214};
        state ++;  // the state changes to the next state
    }

    else if(state == 2){ // the final state of the butterfly
        srcRect = {248, 433, 247, 178};
        state -= 2; // the state is resetted and the process repeats
    }
}
