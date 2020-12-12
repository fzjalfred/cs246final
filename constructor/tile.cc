#include "tile.h"

Tile::Tile(int num, int value, int resource, bool isGeese ) : 
    num{num}, value{value}, resource{resource}, isGeese{isGeese} {}

void Tile::attachV(shared_ptr<Vertex> ptr) {
    vertices.emplace_back(ptr);

}

void Tile::attachE(shared_ptr<Edge> ptr) {
    edges.emplace_back(ptr);
}