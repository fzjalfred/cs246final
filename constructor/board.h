#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>
#include "arginit.h"
#include "subject.h"
#include "tile.h"
#include "info.h"
#include "builder.h"
#include "textdisplay.h"
#include "element.h"
#include "dice.h"

using namespace std;


class Board {
    shared_ptr<TextDisplay> td;
    shared_ptr<Dice> dice;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Builder>> builders;
    vector<int> curbuilt;
    int geese;

    public:
    void init(int, vector<string>&, vector< pair<int, int> >&, int);
    void buildRoad(int pos, int player, bool init = false);
    void buildRes(int pos, int player, bool init = 0);
    void improve(int pos, int player);
    void setLoad();
    void setFair();
    void roll(bool &);
    int getDiceNum();
    bool checkWinner(int &winner);
    void geeseSteal();
    void setGeese(int n, int p);
    void market(int r1, int r2, int p);
    
    TextDisplay& getTD() {return *td;};
    void resourceProduce(int dice);
    void printCurbuilt();
    void trade(int i, int who, int give, int take);
    void printBoard();
    void printStatus();
    void printRes(int player);
    void save(int i, string sv);
    
};



#endif
