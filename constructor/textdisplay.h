#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <vector>
#include <string>
#include <iostream>
#include "observer.h"

using namespace std;

class Edge;
class Vertex;

class TextDisplay: public Observer{
    vector<string> v;
    vector<string> e;
    vector<string> tRes;
    vector<string> tVal;

    public:
    TextDisplay(vector< pair<int, int> > &);
    void visit(Edge&);
    void visit(Vertex&);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);


#endif
