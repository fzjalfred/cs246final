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
    std::string owner;
    public:
    Edge(int num);
};

class Vertex : public Element {
    int num;
    std::string type;
    std::string owner;
    public:
    Vertex(int num);
};

#endif 
