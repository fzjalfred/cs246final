#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <algorithm>
#include <memory>
#include "builder.h"
#include "tile.h"
#include "observer.h"
#include "element.h"
#include "subject.h"
#include "textdisplay.h

using namespace std;

class TextDisplay;
class Dice;
class Builder;
class Tile;
class Vertex;
class Edge;

class Board {
    shared_ptr<TextDisplay> td;
    shared_ptr<Dice> dice;
    curPlayer: &Builder;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Builder>> builders;
    geese& Tile;

    public:
    void init() noexcept;
    void printBoard();
    void printStatus();
    void printRes();
    void buildRoad(int);
    void buildRes(int);
    void improve();
    void trade(stirng colour, Resource give, Resource take);
    void setGeese(int);
    void stealGeese();
    void next();
    void save(string);
    void setLoad();
    void setFair();
    int roll();
}










#endif

