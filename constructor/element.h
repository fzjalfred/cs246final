#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <memory>
#include <exception>
#include <string>
#include "observer.h"
#include "subject.h"

class TextDisplay;

class Element {
    public:
    //virtual void accept(std::shared_ptr<TextDisplay>) = 0;
};

class Edge : public Element, public Subject, public Observer {
    int num;
    bool road;
    int owner = -1;
    public:
    Edge(int, int);
    int getOwner() override;
    void buildRoad(int p) ;
};

class Vertex : public Element, public Subject, public Observer {
    int num;
    char type;
    int owner = -1;
    public:
    Vertex(int, char, int);
    int getOwner() override;
    void buildRes(int p) ;
    void buildImprove(int p) ;
};

#endif 
