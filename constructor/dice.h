#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>

class Dice {
    protected:
    int num;
    public:
    virtual void roll();
};

class INVALID_ROLL: public Dice {};

class LoadedDice: public Dice {
    public:
    void roll();
};

class FairDice: public Dice {
    public:
    void roll() {};
};

#endif