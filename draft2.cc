#include <iostream>
#include <memory>
#include <map>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

class Dice {
    protected:
    int num = -1;
    public:
    Dice() {};
    virtual void roll();
    //int getNum();
};

class INVALID_ROLL {};

class LoadedDice: public Dice {
    public:
    LoadedDice(): Dice() {};
    void roll() override;
};

class FairDice: public Dice {
    public:
    FairDice(): Dice() {};
    void roll() override;
};

/*
int Dice::getNum() {
    return this->num;
}*/

void LoadedDice::roll()
{
    std::cout << "Input a roll between 2 and 12:" << std::endl;
    int dice;
    try
    {
         
        std::cin >> dice;
        if (dice < 2 || dice > 12 || cin.fail() == true)
            throw INVALID_ROLL();
    }
    catch (INVALID_ROLL)
    {
        std::cout << "Invalid roll." << std::endl;
        return;
    }
    this->num =dice;
}

void FairDice::roll() {
    std::vector<int> v{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    this->num = v[0];
}


int main() {
  //shared_ptr<Dice> a;
  //a = make_shared<LoadedDice> ();
  LoadedDice* a;
  a = new LoadedDice();

}