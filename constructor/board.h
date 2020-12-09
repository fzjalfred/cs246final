#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "builder.h"
#include "tile.h"
#include "observer.h"
#include "element.h"
#include "subject.h"
#include "textdisplay.h"
#include "resource.h"

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
    Builder & curPlayer;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Builder>> builders;
    Tile & geese;

    public:
    void init(string commandLineOptions) noexcept;
    void printBoard();
    void printStatus();
    void printRes();
    void buildRoad(int);
    void buildRes(int);
    void improve();
    void trade(string colour, Resource give, Resource take);
    void setGeese(int);
    void stealGeese();
    void next();
    void save(string);
    void setLoad();
    void setFair();
    int roll();
};

#endif
