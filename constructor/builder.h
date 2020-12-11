#ifndef __BUILDER_H__
#define __BUILDER_H__
#include <string>
#include <vector>
#include "observer.h"
#include "subject.h"

enum class Colour;

using namespace std;

class Builder : public Observer, public Subject {
    Colour colour;
    int points;
    vector<int> resource = {5, 0};
    vector<int> roads;
    vector<pair<int, string>> housing;
    public:
    Builder(Colour, string = "0 0 0 0 0 r h ");
    void notifyRoad(int num);
    void notifyRes(int num);
    void builderObtain(Resource);
    void notifyImprove(int);
    void trade(int give, int take, Builder& other);
};


#endif
