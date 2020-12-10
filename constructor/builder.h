#ifndef __BUILDER_H__
#define __BUILDER_H__
#include <string>
#include <vector>
#include "observer.h"
#include "subject.h"


using namespace std;

class Resource {
    std::string colour;
    int num;
    public:
    void print();
};

enum class Colour;

class Builder : public Observer, public Subject {
    Colour colour;
    int points;
    Resource brick;
    Resource energy;
    Resource glass;
    Resource heat;
    Resource wifi;
    Resource park;
    std::vector<int> roads;
    std::vector<pair<int, std::string>> housing;
    public:
    Builder(int);
    void notifyRoad(int num);
    void notifyRes(int num);
    void builderObtain(Resource);
    void notifyImprove(int);
    void trade(Resource& give, Resource take, Builder& other);


};


#endif
