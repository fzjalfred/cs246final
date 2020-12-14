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
    vector<string> geese;

    public:
    TextDisplay(vector< pair<int, int> > &, int geese = -1);
    //void visit(Edge&);
    //void visit(Vertex&);

    void update(string type, int pos, string builder, string buildingtype);
    void setGeese(int currPos, int setPos);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);


};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);


#endif
