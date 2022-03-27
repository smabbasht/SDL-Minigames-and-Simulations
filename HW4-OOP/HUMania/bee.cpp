#include <SDL.h>
#include "bee.hpp"

// constructors

Bee::Bee() {}

Bee::Bee(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {63, 619, 151, 166};

    // it will display pigeon on x = x touched point, y = y touched point, the size of pigeon is 50 width and height
    moverRect = {x, y, 50, 50};
}
// functionalities

void Bee::draw(){
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect); // creates object

    
    if(moverRect.x > 1000){ // if the bee escapes the screen
        on_screen = false; // it turns false, hence, bee_delete will be called to delete it
    }

    prob = 1 + (rand() % 100); // generates no.s b/w 0 to 100

    if (prob == 1) { // 1% probability for hovering
        hover = true; // bee hovers
    }

    if(hover == true){ // hovering phenomenon
        if(hover_time > 0){ // if the hover_time is not 0, it stucks their till it gets 0
            hover_time -=1;
        }

        else if(hover_time == 0){ // when hover_time is 0, bee moves again
            moverRect.x += 5;
            hover = false; // now bee doesn't hover
        }
    }

    else{ // when hover_state is false, it keeps on moving to the right
        moverRect.x += 5;
        // hover_state = false; // the state is maintained to be false aka move right
    }

    fly(); // calling fly function for animation
}

bool Bee::bee_delete(){ // returns bool value for the bee on screen or not for it's deletion
    return on_screen;
}

void Bee::fly(){
    
    if(state == 0){// the initial state of the bee
        srcRect = {63, 619, 151, 166};
        state ++;// the state changes to the next state
    }

    else if(state == 1){// the second state of the bee
        srcRect = {234, 630, 163, 162};
        state ++;// the state changes to the next state
    }

    else if(state == 2){// the last state of the bee
        srcRect = {409, 650, 171, 147};
        state -= 2;// the state is resetted and the process repeats
    }

}