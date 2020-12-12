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

const int NUM_VERTEX = 53;
const int NUM_EDGE = 70;
const int NUM_TILE = 18;

const int NUM_PLAYER = 4;

const int DICE_MIN = 2;

const int DICE_MAX = 12;


//==========================================Exceptions==========================================================
class MissingArg : public exception {
    string t;
    public:
    explicit MissingArg(string arg, string cmd) {t = "ERROR: "+arg+ " missing "+ cmd +" argument";};
    const char* what() const noexcept override {return t.c_str();}
};

class UnrecognizedArg : public exception {
    string t;
    public:
    explicit UnrecognizedArg(string arg) {t = "ERROR: unrecognized argument "+arg;};
    const char* what() const noexcept override {return t.c_str();}
};

class MultiArg : public exception {
    string t;
    public:
    explicit MultiArg(string cmd_use, string cmd_abd) {t = "ERROR: already specified " + cmd_use + " , can't also specify "+ cmd_abd;};
    const char* what() const noexcept override {return t.c_str();}
};

class InvalidOpen : public exception {
    string t;
    public:
    explicit InvalidOpen(string path) {t = "ERROR: Unable to open file " + path + " for board layout.";};
    const char* what() const noexcept override {return t.c_str();}
};

class InvalidOpenDefault : public exception {
    public:
    const char* what() const noexcept override {return "ERROR: Unable to open file layout.txt for default board layout.";}
};

class InvalidFormat : public exception {
    string t;
    public:
    explicit InvalidFormat(string file) {t = "ERROR: "+ file +" has an invalid format.";};
    const char* what() const noexcept override {return t.c_str();}
};

//==============================================================================================================

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
    void buildRoad(int pos, int player);
    void buildRes(int pos, int player);
    void improve(int pos, int player);
    void trade(string colour, Resource give, Resource take);
    void setGeese(int);
    void stealGeese();
    void next();
    void save(string);
    void setLoad();
    void setFair();
    void roll();
    string getPlayerColour(int i);
    bool checkWinner();
    int getDiceNum();
};


#endif
