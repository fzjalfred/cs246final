#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <memory>
#include <exception>
#include <string>
#include "observer.h"
#include "subject.h"
#include "arginit.h"

class TextDisplay;

class Element {
    public:
    //virtual void accept(std::shared_ptr<TextDisplay>) = 0;
};

class Edge : public Element, public Subject, public Observer {
    int num;
    int owner = -1;
    public:
    Edge(int, int);
    int getOwner();
    int getPos();
    void buildRoad(int p) ;
};

class Vertex : public Element, public Subject, public Observer {
    int num;
    char type;
    int owner = -1;
    public:
    Vertex(int, char, int);
    int getOwner();
    int getPos();
    char getResType();
    void buildRes(int p, char type = 'N') ;
    void buildImprove() ;
};

#endif 
