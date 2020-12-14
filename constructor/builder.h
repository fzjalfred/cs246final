#ifndef __BUILDER_H__
#define __BUILDER_H__
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <exception>
#include "observer.h"
#include "subject.h"
#include "info.h"
#include "arginit.h"
#include "textdisplay.h"

enum class Colour;

using namespace std;

class Builder : public Observer, public Subject {
    Colour colour;
    int points;
    vector<int> resource;
    vector<int> roads;
    vector< pair<int, char> > housing;
    shared_ptr<TextDisplay> td;
    public:
    Builder(Colour, shared_ptr<TextDisplay>, string = "0 0 0 0 0 r h ");
    vector<int> & getRoads();
    vector< pair<int, char> > & getHousing();
    void buyRoad(int n, int p);
    void buyRes(int n, int p, bool init = 0);
    void gain(int r, int num);
    void buyImprove(int n, int p);
    //void trade(int give, int take, Builder& other);
    int getPlayerNum();
    int getPoint();
    const vector<int> resourcelist();
    void losehalf();
    void steal(shared_ptr<Builder>);
    
    void printStatus();
    void printRes();
};


#endif
