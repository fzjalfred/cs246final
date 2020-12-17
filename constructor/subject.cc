#include "subject.h"
#include "observer.h"
#include "element.h"
#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>

void Subject::attach (vector<shared_ptr<Vertex>>*  vertices,
    vector<shared_ptr<Edge>>* edges,
     Observer* td) {
        this->vertices = vertices;
        this->edges = edges;
        this->td = td;
    }

void Subject::notifyRes(int n, int p) {
    vertices->at(n)->buildRes(p);
}

void Subject::notifyRoad(int n, int p) {
    edges->at(n)->buildRoad(p);
}

void Subject::notifyImprove(int n, int p) {
    vertices->at(n)->buildImprove();
}

void Subject::notifyBuilder() {

}

