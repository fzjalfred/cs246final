#include <exception>
#include "element.h"
#include <iostream>
using namespace std;

class base_exist : public exception {
    string t;
    public:
    explicit base_exist(int n) {t = "Basements already exist as locations: " + to_string(n);};
    const char* what() const noexcept override {return t.c_str();}
};

Vertex::Vertex(int num, char type, int owner): Subject(), Observer(), num(num), type(type), owner(owner) {}

void Vertex::buildRes(int p) {
    if (owner != -1) {
        throw base_exist(this->num);
    }
    this->owner = p;
    this->type = 'B';
}

Edge::Edge(int num, int owner): Subject(), Observer(), num(num), road(false), owner(owner) {}


void Vertex::buildImprove() {
    switch (this->type) {
        case 'B':
        this->type = 'H';
        break;
        case 'H':
        this->type = 'T';
        break;
    }
    return;
}


void Edge::buildRoad(int p) {
    road = true;
    owner = p;
}

int Vertex::getOwner(){
    return owner;
}

int Edge::getOwner(){
    return owner;
}
