#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
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

const int NUM_VERTEX = 53;
const int NUM_EDGE = 70;

enum class Colour { Blue, Red, Orange, Yellow };

const int NUM_PLAYER = 4;

class Board {
    shared_ptr<TextDisplay> td;
    shared_ptr<Dice> dice;
    shared_ptr<Builder> curPlayer;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Builder>> builders;
    shared_ptr<Tile> geese;

    public:
<<<<<<< HEAD
    void init(string commandLineOptions) noexcept;
=======
    Board();
    void init() noexcept;
>>>>>>> b8bbd6e2300f0161ade89f91592c54be6fcaaa99
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
    int getDiceNum();
};










#endif
