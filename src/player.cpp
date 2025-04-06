#include "player.h"
#include <cstdlib>

Player::Player()
{
    numDice = 5;
    diceArray = nullptr;

    populateDiceArray();
}

Player::~Player()
{
    delete[] diceArray;
}

void Player::rollDice(int numDice)
{
    for (int i = 0; i < numDice; ++i)
    {
        diceArray[i].roll();
    }
}

int Player::getDice(int index) const
{
    if (index >= 0 && index < numDice)
        return diceArray[index].getValue();
    return -1;
}

void Player::loseDie()
{
    if (numDice > 0)
        --numDice;
}

int Player::getNumDice() const
{
    return numDice;
}

void Player::populateDiceArray()
{
    if (diceArray != nullptr)
        delete[] diceArray;

    diceArray = new Dice[numDice];

    for (int i = 0; i < numDice; ++i)
    {
        diceArray[i].roll();
    }
}