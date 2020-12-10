#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "board.h"

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
    this->dice = make_shared<LoadedDice>();
}

void Board::setFair() {
    this->dice = make_shared<FairDice>();
}

void Board::roll() {
    this->dice->roll();
}

int Board::getDiceNum() {
    return dice->getNum();
};
