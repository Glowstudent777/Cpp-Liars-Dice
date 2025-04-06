#ifndef PLAYER_H
#define PLAYER_H

#include "dice.h"

class Player
{
private:
    Dice *diceArray;
    int numDice;

    void populateDiceArray();

public:
    Player();
    ~Player();

    void rollDice(int numDice);
    void loseDie();

    int getDice(int index) const;
    int getNumDice() const;
};

#endif