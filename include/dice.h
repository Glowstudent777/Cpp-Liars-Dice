#ifndef DIE_H
#define DIE_H

#include <cstdlib>
#include <ctime>

class Dice
{
private:
    int sides;
    int value;

public:
    Dice(int numSides = 6);

    void roll();

    int getSides() { return sides; }
    int getValue() { return value; }
};

#endif