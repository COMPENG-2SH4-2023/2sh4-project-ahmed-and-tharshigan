#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        
        // changed in above and beyond
        void movePlayer();

        bool checkSelfCollision();

    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        //Reference to food class
        Food* foodRef;

        // Above and Beyond
        // I am going to manually break down the public movePlayer method.
        // To implement the special food logic, i can repeat code less
        // since i will need to update current head multiple times for special food
        void updateCurrentHead();
        objPos currentHead; // currentHead variable to be shared for special food Above and Beyond feature
};

#endif