#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    //Initial player starting position
    playerPos.setObjPos(5,5,'*'); //CHANGE INITIAL POSITION once board is set
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    //NOTE: input not defined - get input from a method in GameMech class using the reference pointer to GameMech class defined in private data members
    switch(input){
        
        case 'w':
            if(myDir != UP && myDir != DOWN){
                myDir = UP;
            }
            break;
        
        case 'a':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = LEFT;
            }
            break;

        case 's':
            if(myDir != UP && myDir != DOWN){
                myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = RIGHT;
            }
            break;

    }        
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //NOTE: COL_SIZE is the max number of columns in gameboard
    //      ROW_SIZE is max number of rows in gameboard
    switch(myDir){
        case UP:
            //Subtracting y position by 1 to move player object up by one
            playerPos.y--;
            
            //If statement to check if player reaches top of the game board
            if(playerPos.y == 0){
                //player.y = COL-SIZE-2
            }

            break;

        case DOWN:
            playerPos.y++;

            //If statement to check if player reaches bottom of the game board
            // if (playerPos.y == COL_SIZE-1){
            //     playerPos.y = 1;
            // }

            break;

        case LEFT:

            playerPos.x--;

            //If statement to check if player reaches the left border of game board
            if (playerPos.x == 0){
                //playerPos.x = ROW_SIZE-2;
            }

            break;

        case RIGHT:

            playerPos.x++;

            //If statement to check if player reaches the right border of game board
            // if (playerPos.x == ROW_SIZE-1){
            //     playerPos.x = 1;
            // }

            break;
    }
}

