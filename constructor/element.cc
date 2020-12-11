#include "element.h"

Vertex::Vertex(int num, char type, int owner): num(num), type(type), owner(owner) {}

Edge::Edge(int num, int owner): num(num), road(false), owner(owner) {}
