#include <exception>
#include "element.h"

using namespace std;

class base_exist : public exception {
    string t;
    public:
    explicit base_exist(int n) {t = "Basements already exist as locations: " + to_string(n);};
    const char* what() const noexcept override {return t.c_str();}
};

Vertex::Vertex(int num, char type, int owner): num(num), type(type), owner(owner) {}

void Vertex::buildRes(int p) {
    if (owner == -1) {
        throw base_exist(this->num);
    }
    this->owner = p;
    this->type = 'B';
}

Edge::Edge(int num, int owner): num(num), road(false), owner(owner) {}
