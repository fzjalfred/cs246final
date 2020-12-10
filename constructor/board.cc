#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "board.h"
#include "tile.h"
#include "element.h"
#include "dice.h"


using namespace std;

Board::Board() {
    for(int i = 0; i <= NUM_VERTEX || i <= NUM_EDGE; i++) {
        if (i <= NUM_VERTEX)
        this->vertices.emplace_back(i);
        if (i <= NUM_EDGE)
        this->edges.emplace_back(i);
        if (i < NUM_PLAYER)
        this->builders.emplace_back(Builder {i});
    }
    curPlayer = this->builders.front();
}

void Board::setLoad() {
    dice = make_shared<Dice> (new LoadedDice());
}

void Board::setFair() {
    dice = make_shared<Dice> (new FairDice());
}

void Board::roll() {
    dice->roll();
}

int Board::getDiceNum() {
    return dice->getNum();
};
