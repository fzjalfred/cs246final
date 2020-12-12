#ifndef _TILE_H_
#define _TILE_H_
#include <memory>
#include "observer.h"
#include "subject.h"


using namespace std;

class Vertex;
class Edge;

class Tile : public Observer, public Subject {
    int num;
    int value;
    int resource;
    bool isGeese;
    vector<shared_ptr<Vertex>> vertices;
    vector<shared_ptr<Edge>> edges;

    public:
    Tile(int num, int value, int resource, bool isGeese = false);
    void attachV(shared_ptr<Vertex>);
    void attachE(shared_ptr<Edge>);
};

#endif
