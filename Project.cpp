#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000 // 0.1s

//Game mechanics object
GameMechs* myGM;
//Player object
Player *myPlayer;
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

}

void GetInput(void)
{
    myGM->getInput();
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    //Local variables and objects
    int totalRows = myGM->getBoardSizeY();
    int totalCols = myGM->getBoardSizeX();
    //Creating object of objPos class
    objPos tempPos;
    //Calling method to pass player position to tempPos object
    myPlayer->getPlayerPos(tempPos);

    //For loop to iterate through every row of game board
    for(int row=0; row<totalRows; row++){
        //For loop to iterate through every column per row
        for(int col=0; col<totalCols; col++){
          //If statements to check if printing first or last row of game board
          if(row == 0 || row == totalRows-1){
            MacUILib_printf("%c", '#');
          }

          else{
            if(col == 0 || col == totalCols-1){
                MacUILib_printf("%c", '#');
            }

            else if(tempPos.x == col && tempPos.y == row){
                MacUILib_printf("%c", tempPos.symbol);
            }

            else{
                MacUILib_printf("%c", ' ');
            }
          }  
        }
        MacUILib_printf("\n");
    }

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

    MacUILib_uninit();
}
