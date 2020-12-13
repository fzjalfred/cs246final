#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>
#include "builder.h"
#include "subject.h"
#include "tile.h"
#include "textdisplay.h"
#include "element.h"
#include "info.h"
#include "dice.h"

using namespace std;


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
    int geese;

    public:
    void init(int, vector<string>&, vector< pair<int, int> >&, int);
    void buildRoad(int pos, int player);
    void buildRes(int pos, int player);
    void improve(int pos, int player);
    void setLoad();
    void setFair();
    void roll();
    int getDiceNum();
    bool checkWinner(int &winner);
    void geeseSteal();
    void setGeese(int n, int p);
    
    void trade(int player, int give, int take);
    void printBoard();
    void printStatus();
    void printRes();
    void save(string);
};

string getPlayerColour(int i);

#endif
