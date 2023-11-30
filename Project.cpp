#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000 // 0.1s

//Game mechanics object
GameMechs* myGM;

//Player object
Player *myPlayer;

//Food object
Food *foodObj;

// bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(20, 10); //26x13 board

    myPlayer = new Player(myGM);

    foodObj = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());

    //tempPos represents player initial position
    objPos tempPos;

    //Passing player position to tempPos
    myPlayer->getPlayerPos(tempPos);

    //Generating initial food coordinate
    foodObj->generateFood(tempPos);

}

void GetInput(void)
{
    myGM->getInput();

    //Creating tempPos object to store player position
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    //Regenerate food position when 'r' is pressed
    if (myGM->getInput() == 'r'){
        foodObj->generateFood(tempPos);
    }

}

void RunLogic(void)
{
    //If statement to check if exit key was pressed
    if(myGM->getInput() == ' '){
        myGM->setExitTrue(); //NOTE: ASK IF exitFlag should be set to true in updatePlayerDir() because already calling getInput in that method
    }

    //Else statement to change direction of player based on key pressed
    else{
        //Class method to update player direction
        myPlayer->updatePlayerDir();
        //Class method to move player based on player direction
        myPlayer->movePlayer();
    }

    myGM->clearInput(); //Resetting input to 0
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    //Local variables and objects
    int totalRows = myGM->getBoardSizeY();
    int totalCols = myGM->getBoardSizeX();
    //Creating object of objPos class
    objPos playerPos, foodPos;
    //Calling method to pass player position to playerPos object
    myPlayer->getPlayerPos(playerPos);
    foodObj->getFoodPos(foodPos);

    //For loop to iterate through every row of game board
    for(int row=0; row<totalRows; row++){
        //For loop to iterate through every column per row
        for(int col=0; col<totalCols; col++){
          //If statements to check if printing first or last row of game board
          if(row == 0 || row == totalRows-1){
            MacUILib_printf("%c", '#');
          }

          else{
            //If statement to print border if in first or last column
            if(col == 0 || col == totalCols-1){
                MacUILib_printf("%c", '#');
            }

            //Else if to print player if at player position
            else if(playerPos.x == col && playerPos.y == row){
                MacUILib_printf("%c", playerPos.symbol);
            }

            //Else if to print food if at food position
            else if(foodPos.x == col && foodPos.y == row){
                MacUILib_printf("%c", foodPos.symbol);
            }

            //Else to print space if no other character occupies that space
            else{
                MacUILib_printf("%c", ' ');
            }
          }  
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n, Food Pos: <%d, %d>\n", myGM->getScore(), playerPos.x, playerPos.y, foodPos.x, foodPos.y);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    //Deallocating memory of objects created on the heap
    delete myGM;
    delete myPlayer;
    delete foodObj;

    MacUILib_uninit();
}
