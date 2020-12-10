#ifndef VERTEX_H
#define VERTEX_H 
#include <string>
#include "element.h"

class Vertex: public Element {
    int num;
    std::string type;
    std::string owner;

    public:
    Vertex( int, std::string );
    void accept( std::shared_ptr<TextDisplay> );
};

#endif
