#ifndef __BUILDER_H__
#define __BUILDER_H__
#include <string>
#include <vector>
#include <exception>
#include "observer.h"
#include "subject.h"

enum class Colour;

using namespace std;

class Builder : public Observer, public Subject {
    Colour colour;
    int points;
    vector<int> resource;
    vector<int> roads;
    vector< pair<int, char> > housing;
    public:
    Builder(Colour, string = "0 0 0 0 0 r h ");
    vector<int> & getRoads();
    vector< pair<int, char> > & getHousing();
    void buyRoad(int n, int p);
    void buyRes(int n, int p);
    //void builderObtain(enum Resource type, int num);
    void buyImprove(int n, int p);
    //void trade(int give, int take, Builder& other);
    int getPlayerNum() {
        return static_cast<int> (colour);
    };
    int getPoint() {
        return this->points;
    }
    const vector<int> resourcelist();
    void losehalf();
    void steal(shared_ptr<Builder>);
};


#endif
