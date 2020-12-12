#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>
#include "builder.h"
#include "tile.h"
#include "observer.h"
#include "element.h"
#include "subject.h"
#include "textdisplay.h"
#include "dice.h"

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
    shared_ptr<Builder> curPlayer;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Builder>> builders;
    shared_ptr<Tile> geese;

    public:
    void init(int, vector<string>&, vector< pair<int, int> >&, int);
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
    void roll();
    Colour getPlayer(int num);
    int getDiceNum();
};


#endif
