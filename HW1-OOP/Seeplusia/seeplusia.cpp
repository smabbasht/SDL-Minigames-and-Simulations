// 		   || Include Statements
#include "seeplusia.hpp"
#include "mover.hpp"

// 		   || Provided Variables
int applesLeft = 20, nCrystalsFound = 0;
string gameState  = "Running";
string currentState = "Enchanted Forest";

/*		   || Helper Variables
These boolean variables keep the track of whether the crytal from a particular location
is already retrieved or not. Thus, they prevent from the error of any crytal being counted
more than once. 																		*/
bool undead_crystal_retrieved = false;
bool hill_crystal_retrieved = false;
bool despair_crystal_retrieved = false;
bool tunnel_crystal_retrieved = false; 
int apples_req;	 /* apples_req undergoes a repeated update depending upon
the apples required to move to a particular location from current location. */ 

/*			   || Assumptions
Below are the assumptions that were taken to complete the game as for some situations,
the scenario or rules weren't explicitly stated;

	1. If the Warrior is at Bridge of Death and she has crystals less than 4 then the gameState turns to "Lost" 
	as we don't have route indiacted by an arrow on Bridge of Death except that going to Wizard's Castle and 
	he can't pass by Bridge of Death to Wizard's Castle unless she ha 4 crystals so in either case he'll die 
	eventually so charging 1 apple for every move (as moves in all four directions are invalid in this condition) 
	and then gradually getting the apples zero and then making him die doesn't make sense.

	2. If the Warrior is at Eisten Tunnel and she hasn't collected three crytals necessary for passing through
	the Tunnel then if she presses UP key then the warrior remains there but the apples required for the
	move gets deducted as the charge for invalid move.    */

/*	 	 	   || Helper Functions
These functions basically handle almost everything in the game logic from the gameState,
currentState .,.,.,. to permitting the movement of the warrior etc. They alo internally call 
the moveSouth(), moveNorth(), moveEast() & moveWest() functions.

Every function is related to a particular location and handles everything related to that like
non-allowance and applying charge of invalid moves, crystal retrieval (wherever applicable), and movement
of warrior dynamic to the location thus every helper function is sufficient to handle the makeMove() provided
the warrior is in the location corresponding to the helper function.
Hence, they are then conditionally called in the makeMove function										*/

void Enchanted_Forest(string direction){
	if (direction == "West" || direction == "North"){ // Check for Invalid Moves
		apples_req = 1; 
		if (applesLeft >= apples_req){ // Check if the warrior has the required apples left or not
			applesLeft -= apples_req; } // deducts the invalid move charge while the currentState remains unchanged
		else{ 						  // If warrior doesn't have required apples then she will die
			applesLeft = 0;
			gameState = "Lost";}}
	else if (direction == "East"){
		apples_req = 1;  			// apples required for travelling to the location in East
		if (applesLeft >= apples_req){ // Check if the warrior has the required apples left or not
			currentState = "Sands of Quick"; // Changes the currentState to the location warrior is moving to
			moveEast(); // moves the warrior
			applesLeft -= apples_req; // deducts the apples_req from total applesLeft
			gameState = "Lost"; }     // As the warrior dies at Sand of Quick due to quickand thus changing gameState to "Lost"
		else {  					// If warrior doesn't have required apples then she will die
			applesLeft = 0;
			gameState = "Lost";}}

	else if (direction == "South"){
		apples_req = 3;  			// apples required for travelling to the location in South
		if (applesLeft >= apples_req){ // Check if the warrior has the required apples left or not
			currentState = "Wampire Cove"; // Changes the currentState to the location warrior is moving to
			moveSouth(); // moves the warrior 
			applesLeft -= apples_req;} // deducts the required apples from total apples
		else {
			applesLeft = 0;
			gameState = "Lost";}}
// All the functions below have similar implementation so the documented code above can be referenced for any of them.
}

void Wampire_Cove(string direction){
	if (direction == "North"){
		apples_req = 3;
		if (applesLeft >= apples_req){
			currentState = "Enchanted Forest";
			moveNorth();
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	else if (direction == "South"){
		apples_req = 3;
		if (applesLeft >= apples_req){
			currentState = "Werewolf Hill";
			moveSouth();
			applesLeft -= apples_req;
			if (hill_crystal_retrieved == false){ // checks if the crystal has already retrieved or not
				hill_crystal_retrieved = true;   // if the crystal isn't retrieved yet then it changes the retrieved bool to variable yes
				nCrystalsFound++;}}	// increases the nCrystalFound
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	else if (direction == "East"){
		apples_req = 1;
		if (applesLeft >= apples_req){	
			if (undead_crystal_retrieved == false){
				undead_crystal_retrieved = true; 
				nCrystalsFound++;}

			currentState = "Marsh of Undead";
			moveEast();
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}			
	else if (direction == "West"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Swamps of Despair";
			moveWest();
			applesLeft -= apples_req;
			if (despair_crystal_retrieved == false){
				despair_crystal_retrieved = true;
				nCrystalsFound++;}}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}}

void Marsh_of_Undead(string direction){
		if (direction == "South"){
			apples_req = 1;
			if (applesLeft >= apples_req){
				currentState = "Apples Orchad";
				moveSouth();
				applesLeft+=5;}
			else{
				gameState = "Lost";
				applesLeft = 0;
			}}
		else if (direction == "East" || direction == "South"){
			apples_req = 1;
			if (applesLeft >= apples_req){
				currentState = "Marsh of Undead";
				applesLeft -= apples_req;}
			else {
				applesLeft = 0;
				gameState = "Lost";
			}}
		else if (direction == "West"){
			apples_req = 1;
			if (applesLeft >= apples_req){
				currentState = "Wampire Cove";
				moveWest();
				applesLeft -= apples_req; }
			else {
				applesLeft = 0;
				gameState = "Lost"; }}}

void Apples_Orchad(string direction){
	if (direction == "East" || direction == "South" || direction == "North"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Apples Orchad";
			applesLeft -= apples_req;}
		else {
			applesLeft = 0;
			gameState = "Lost";
		}}
	else if (direction == "West"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Werewolf Hill";
			moveWest();
			applesLeft -= apples_req;
			if (hill_crystal_retrieved == false){
				hill_crystal_retrieved = true;
				nCrystalsFound++;}}
		else {
			applesLeft = 0;
			gameState = "Lost";
		}}}

void Werewolf_Hill(string direction){
	if (direction == "East" || direction == "South"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Werewolf Hill";
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	if (direction == "West"){
		apples_req = 2;
		if (applesLeft >= apples_req){
			gameState == "Running";
			currentState = "Elvin Waterfall";
			moveWest();
			applesLeft-=2;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	if (direction == "North"){
		apples_req = 3;
		if (applesLeft >= apples_req){
			currentState = "Wampire Cove";
			moveNorth();
			applesLeft-=2;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}}

void Elvin_Waterfall(string direction){
	if (direction == "North" || direction == "South"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Elvin Waterfall";
			applesLeft -= apples_req;}
		else {
			applesLeft = 0;
			gameState = "Lost"; }}
	if (direction == "West"){
		apples_req = 2;
		if (applesLeft >= apples_req){
			currentState = "Eisten Tunnel";
			moveWest();
			if (tunnel_crystal_retrieved == false){
				tunnel_crystal_retrieved = true;
				nCrystalsFound++;}
			applesLeft-=2;}
		else {
			applesLeft = 0;
			gameState = "Lost";
	}}
	if (direction == "East"){
		apples_req = 2;
		if (applesLeft >= apples_req){
			currentState = "Werewolf Hill";
			moveEast();
			applesLeft-=2;
			if (hill_crystal_retrieved == false){
				hill_crystal_retrieved = true;
				nCrystalsFound++;}}
		else {
		applesLeft = 0;
		gameState = "Lost";
	}}}

void Swamps_of_Despair(string direction){
	if (direction == "West" || direction == "South"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Swamps of Despair";
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	if (direction == "East"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Wampire Cove";
			moveEast();
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	if (direction == "North"){
		apples_req = 1;
		if (nCrystalsFound == 4){ // Implementing Assumption no.1 (Check whether the warrior has 4-required crystals or not)
			if (applesLeft >= apples_req){
				currentState = "Bridge of Death";
				moveNorth();
				applesLeft -= apples_req;}
			else{
				applesLeft = 0;
				gameState = "Lost";}}
		else{ // If the warrior doesn't have the required crytals then she will eventually die since there' no back arrow(route)
			moveNorth();
			applesLeft = 0;
			gameState = "Lost";
		}}}

void Bridge_of_Death(string direction){
	if (direction == "East" || direction == "North" || direction == "South"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Bridge of Death";
			applesLeft -= apples_req;}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}
	else if (direction == "West"){
		apples_req = 5; 
		if (applesLeft >= apples_req){
			if (nCrystalsFound == 4){
				gameState = "Won";
				currentState = "Wizard's Castle";
				applesLeft-=apples_req;
				moveWest();}
			else{
				gameState = "Lost";
			}}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}}

void Eisten_Tunnel(string direction){
	if (direction == "West" || direction == "South"){
		apples_req = 1;
		if (applesLeft >= apples_req){
			currentState = "Eisten Tunnel";
			applesLeft -= apples_req;}
		else {
			applesLeft = 0;
			gameState = "Lost";}}
	
	else if (direction == "East"){
		apples_req = 2;
		if (applesLeft >= apples_req){
			currentState = "Elvin Waterfall";
			moveEast();
			applesLeft-=apples_req;}
		else {
			applesLeft = 0;
			gameState = "Lost"; }}
	
	else if (direction == "North"){
		apples_req = 10;
		if (applesLeft >= apples_req){
			if (nCrystalsFound >= 3){  // Check whether the required crystals are collected in order to move to the Wizard's Castle
				gameState = "Won";	   // Changes the gameState to "Won"
				currentState = "Wizard's Castle";
				moveNorth();		   // Calls the moveNorth twice as two regular jumps are
				moveNorth(); }
			applesLeft-=apples_req;
			if (applesLeft < 1){
				gameState = "Lost";
				applesLeft = 0;
			}}
		else{
			applesLeft = 0;
			gameState = "Lost";
		}}}


/*	       || Main FunctionS
As stated earlier, every function can handle the move and it's related logic if the warrior
is in the location corresponding to the function so these functions are called here if the condition
of warrior being in the location of that helper function satisfies.
*/
void makeMove(string direction){
	
	if (currentState == "Enchanted Forest")
		Enchanted_Forest(direction);

	else if (currentState == "Wampire Cove")
		Wampire_Cove(direction);

	else if (currentState == "Marsh of Undead")
		Marsh_of_Undead(direction);

	else if (currentState == "Apples Orchad")
		Apples_Orchad(direction);

	else if (currentState == "Werewolf Hill")
		Werewolf_Hill(direction);

	else if (currentState == "Elvin Waterfall")
		Elvin_Waterfall(direction);

	else if (currentState == "Eisten Tunnel")
		Eisten_Tunnel(direction);

	else if (currentState == "Swamps of Despair")
		Swamps_of_Despair(direction);

	else if (currentState == "Bridge of Death")
		Bridge_of_Death(direction);}

