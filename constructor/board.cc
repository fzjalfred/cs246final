#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "board.h"
#include "tile.h"
#include "element.h"

const int NUM_VERTEX = 53;
const int NUM_EDGE = 70;

enum class Colour { Blue, Red, Orange, Yellow };

const int NUM_PLAYER = 4;

using namespace std;

Board::Board(): td{nullptr} dice{nullptr} {
    for(int i = 0; i <= NUM_VERTEX || i <= NUM_EDGE; i++) {
        if (i <= NUM_VERTEX)
        this->vertices.emplace_back(i);
        if (i <= NUM_EDGE)
        this->edges.emplace_back(i);
        if (i < NUM_PLAYER)
        this->builders.emplace_back(i);
    }

};


