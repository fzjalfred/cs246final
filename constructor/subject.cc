#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>

void Subject::attach (shared_ptr< vector<shared_ptr<Observer>> > vertices,
    shared_ptr< vector<shared_ptr<Observer>> > edges,
    shared_ptr<Observer> td) {
        this->vertices = vertices;
        this->edges = edges;
        this->td = td;
}

void Subject::notifyRes(int n, int p) {
    vertices->at(n)->buildRes(p);
}
