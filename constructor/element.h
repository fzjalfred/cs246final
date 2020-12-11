#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <memory>
#include <string>

class TextDisplay;

class Element {
    public:
    virtual void accept(std::shared_ptr<TextDisplay>);
};

class Edge : public Element {
    int num;
    bool road;
    int owner;
    public:
    Edge(int, int);
};

class Vertex : public Element {
    int num;
    char type;
    int owner;
    public:
    Vertex(int, char, int);
};

#endif 
