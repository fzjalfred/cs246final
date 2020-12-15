#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include "info.h"
#include "dice.h"

extern const int DICE_MIN;

extern const int DICE_MAX;

int Dice::getNum() {
    return this->num;
}


void LoadedDice::roll( bool & valid )
{
    int dice;
    std::cout << "Input a roll between "+std::to_string(DICE_MIN)+" and "+std::to_string(DICE_MAX)+":" << std::endl;
    std::cout << "> ";
    while (true)
    {
        try
        {

            std::cin >> dice;
            if (dice < DICE_MIN || dice > DICE_MAX || std::cin.fail() == true)
                throw INVALID_ROLL{};
            this->num = dice;
            valid = true;
            return;
        }
        catch (INVALID_ROLL)
        {
            std::cout << "Invalid roll "<< dice << "."<< std::endl;
            return;
        }
    }
}

void FairDice::roll(bool & valid) {
    std::vector<int> v;
    for (int i = DICE_MIN; i <= DICE_MAX; i++) v.emplace_back(i);
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    this->num = v[0];
    valid = true;
    return;
}

