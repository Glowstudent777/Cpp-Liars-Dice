#include <cstdlib>
#include <ctime>
#include "dice.h"

using namespace std;

Dice::Dice(int numSides)
{
    unsigned seed = time(0);

    srand(seed);

    sides = numSides;

    roll();
}

void Dice::roll()
{
    const int MIN_VALUE = 1;

    value = (rand() % (sides - MIN_VALUE + 1)) + MIN_VALUE;
}