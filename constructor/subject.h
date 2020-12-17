#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <memory>
#include <vector>
#include "observer.h"

class Vertex;

class Edge;

using namespace std;

class TextDisplay;

class Subject {
    vector<shared_ptr<Vertex>>* vertices = nullptr;
    vector<shared_ptr<Edge>>* edges = nullptr;
    Observer* td = nullptr;

    public:
    void attach(shared_ptr< vector<shared_ptr<Vertex>> > vertices,
    shared_ptr< vector<shared_ptr<Edge>> > edges,
    shared_ptr<Observer> td);
    void notifyRoad(int n, int p);
    void notifyRes(int n, int p);
    void notifyImprove( int n, int p);
    void notifyBuilder( );

};


#endif
