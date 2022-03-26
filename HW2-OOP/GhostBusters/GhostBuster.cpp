#include "GhostBuster.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Currently rows and columns are set to 8, however your game implementation should work for any other number
const int rows = 8, cols = 8;

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
char* grid = NULL;

// Ghost will be placed over this location
int ghostRow, ghostCol;

// *****************************************************************************************************
// No change zone: Don't change anything until the next stars line
// *****************************************************************************************************

// Don't Change it: Screen width and height values
const int width = 1000, height = 600;

// Don't Change: This function is dealing with SDL and currently it's complete. Don't change anything here
void drawOneBlock(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col, char sym){
    int xbox = width/cols;
    int ybox = height/rows;
    SDL_Rect src;
    switch(sym){
        case 'L': src = {141, 7, 104, 113}; break;
        case 'S': src = {427, 12, 129, 103}; break;
        case 'T': src = {268, 10, 130, 111}; break;
        case 'B': src = {0, 3, 114, 111}; break;
        case 'G': src = {571, 0, 123, 121}; break;
        case 'Z': src = {571, 0, 25, 25}; break;
        case 'F': src = {707, 16, 90, 86}; break;
    }
    SDL_Rect mov = { xbox*col, ybox*row, xbox - 10, ybox - 10};
    SDL_RenderCopy(renderer, texture, &src, &mov);
}

void drawBlocks(SDL_Renderer* renderer, SDL_Texture* texture){
    // Call drawOneBlock for all of the blocks of grid
    // for example to draw a snake over block (3, 5) you call it this way:
    // drawOneBlock(renderer, texture, 3, 5, 'S');
    if(grid == NULL) return;
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            drawOneBlock(renderer, texture, i, j, grid[i*cols+j]);
        }   
    }
}

// *****************************************************************************************************
// No change zone ends here
// *****************************************************************************************************



// To Do zone: 

bool ended = false;


// Helper Variable & Containers

// Animals is an Array which will be used to faciliate random selection of Snake, Turtle and Bunny when distance > 4
char animals[3]= {'S', 'B', 'T'};

// These are the heights and widths of each block
int block_width = width/cols;
int block_height = height/rows;

// This is an **extra featuere** which returns the number of clicks at the end of the game
int clicks;


// Functions

void initialize(){
    // Create memory for grid here, it should be one dimensional array.
    // The memory should be rows*cols size.
    // Initialize entire grid with 'L' so that locks are displayed all over
    // generate two random numbers and store in ghostRow and ghostCol variables
    // the modulus ensures that the random number remains in the range of the grid index
    
    grid = new char[rows*cols];
    
    for (int i=1; i <= (rows*cols); i++){
        *(grid+i-1) = 'L';
    }
    
    // Ghost Locations random assignment, Modulus ensures that the values remains in the range whereas +1 tackles 0.
    ghostRow = rand()%(rows)+1; 
    ghostCol = rand()%(cols)+1;

    // clicks initialized as ZERO
    clicks = 0; 
    
    // Ghost Report. (Prolific for doing the debug)
    cout << "Ghost Col: " << ghostCol << " -- Ghost Row: " << ghostRow << endl;

}

void huntGhost(int x, int y){
    // this function is called every time you click on the screen
    // x, y are screen coordinates, you need to identify the block from these coordinates and using screen width and height values
    // each block size is width/cols x height/rows
    // according to game rules you need to put appropriate character in the grid for that block
    // Place 'S' to draw a snake
    // place 'T' to draw a turtle
    // place 'B' to draw a bunny

    // Condition to enable freeze of the game if game ends (ended == true)
    if (ended == false){

        // clicked row and col computes the row and column of click using the co-ordinate which is then divided by height and width
        int clicked_row = (y/block_height)+1;
        int clicked_col = (x/block_width)+1;

        // gridindex gives the index of the clicked element, It does so by first adding all elements of rows except the last one
        // then it simply adds the no. of elements in the last row. (-1 is here since indices start with zero)
        int gridindex = (clicked_row-1)*cols + clicked_col - 1;

        // distance calculates the distance of clicked block from the Ghost Block using the standard formula.
        int distance = sqrt(pow((clicked_row-ghostRow),2) + pow((clicked_col-ghostCol),2));
        
        /*
        By Following the Solution.exe, I removed the snippet below
        
        // The standard distance formula fails for elements in diagnol with the ghost block. 
        // Here is a fix which computes the correct value upto second level.
        if (pow((clicked_row-ghostRow),2)==(pow((clicked_col-ghostCol),2))){
            distance = sqrt(pow((clicked_row-ghostRow),2) + pow((clicked_col-ghostCol),2)-pow((clicked_row-ghostRow),2));
        }*/
        
        // Click Report (Very Helpful while debugging)
        cout << "x: " << x << " -- y: " << y << endl; 
        cout << "Clicked Col: " << clicked_col << " -- Clicked Row: " << clicked_row << endl;
        cout << "Distance from Ghost is: " << distance << endl;
        
        // Conditions for displaying appropriate images:
        // For Snake, Distance should be less than or equals to 1
        if (distance<=1){
            *(grid + gridindex) = 'S';    
        }
        // For Turtle, 2 <= distance <=3
        else if (distance<=3){
            *(grid + gridindex) = 'T';    
        }
        // For Bunny, distance should be 4
        else if (distance==4){
            *(grid + gridindex) = 'B';    
        }
        // When distance is beyond 4, then we choose randomly between the three animals using the randomized index
        // on a pre-defined array
        else{
            int x = rand()%3; // x faciliates the random selection between 'S', 'T' & 'B'
            *(grid + gridindex) = animals[x];
        }
    // increment in click
    clicks++;    
    }}

void bustGhost(int x, int y){
    // this function is called when you right-click
    // it should work only one time, and you decide whether game is won or failed
    // once the game is won/failed, nothing in game should change anymore.
    // according to game rules you need to put appropriate character in the grid for that block
    // place 'S' to draw snake, when the game is won
    // place 'F' to draw failed symbol, when the game is failed

    if (ended == false){
        // increment in click
        clicks++;

        // Already explained
        int clicked_row = (y/block_height)+1;
        int clicked_col = (x/block_width)+1;
        int gridindex = (clicked_row-1)*cols + clicked_col - 1;

        // Checking whether the click targets the Ghost, if it does, the player wins
        if ((clicked_row==ghostRow)&&(clicked_col==ghostCol)){
            // Displaying Ghost
            *(grid + gridindex) = 'G';
            // Number of Clicks Report
            cout << "You Won in just " << clicks << " clicks....!!!!";
            // game ends....!
            ended = true;
        }
        else{
            // Displaying 'Failed' sign
            *(grid + gridindex) = 'F';
            // Number of Clicks Report
            cout << "This attempt took " << clicks << " clicks.\nBetter Luck Next Time";
            // game ends....!
            ended = true;
        }
    }
}


void quitGhostBuster(){
    // delete the grid here
    delete [] grid;
}