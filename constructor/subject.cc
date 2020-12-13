#include "subject.h"
#include "observer.h"
#include "element.h"
#include <vector>
#include <algorithm>

void Subject::attach (shared_ptr< vector<shared_ptr<Vertex>> > vertices,
    shared_ptr< vector<shared_ptr<Edge>> > edges,
    shared_ptr<Observer> td) {
        this->vertices = vertices;
        this->edges = edges;
        this->td = td;
    }

void Subject::notifyRes(int n, int p) {
    vertices->at(n)->buildRes(p);
}

void Subject::notifyRoad(int n, int p) {
    
}

void Subject::notifyImprove(int n, int p) {

}

void Subject::notifyBuilder() {

}

