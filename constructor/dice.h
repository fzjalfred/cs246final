#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>

class Dice {
    protected:
    int num = -1;
    public:
    virtual void roll(bool&) = 0;
    int getNum();
};

class INVALID_ROLL {};

class LoadedDice: public Dice {
    public:
    void roll( bool &) override;
};

class FairDice: public Dice {
    public:
    void roll(bool &) override;
};

#endif