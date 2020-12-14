#ifndef _TILE_H_
#define _TILE_H_
#include <memory>
#include "builder.h"
#include "observer.h"
#include "subject.h"
#include "arginit.h"


using namespace std;

extern const int NUM_PLAYER;

class Vertex;
class Edge;

class Tile : public Subject {
    int num;
    int value;
    int resource;
    bool isGeese = false;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;
    shared_ptr< vector<shared_ptr<Builder>> > builders;

    public:
    Tile(int num, int value, int resource, bool isGeese = false);
    vector<shared_ptr<Builder>> ownerlist();
    int getTileValue();
    void giveResource();
    void geeseMove(int p);
    void geeseSteal();
    void attachV(shared_ptr<Vertex>);
    void attachE(shared_ptr<Edge>);
    void attachB(shared_ptr< vector<shared_ptr<Builder>> > builders);
};

#endif
