#include <exception>
#include "element.h"
#include <iostream>
using namespace std;


Vertex::Vertex(int num, char type, int owner): Subject(), Observer(), num(num), type(type), owner(owner) {}

void Vertex::buildRes(int p) {
    if (owner != -1) {
        throw invalid_build();
    }
    this->owner = p;
    this->type = 'B';
}

Edge::Edge(int num, int owner): Subject(), Observer(), num(num), owner(owner) {}


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
    if (owner != -1) {
        throw invalid_build();
    }
    owner = p;
}

int Vertex::getOwner(){
    return owner;
}

int Edge::getOwner(){
    return owner;
}

char Vertex::getResType() {
    return type;
}

int Vertex::getPos() {
    return num;
}

int Edge::getPos() {
    return num;
}
