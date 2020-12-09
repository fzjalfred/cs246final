#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <vector>

using namespace std;


class TextDisplay {
    vector<char> theDisplay;
    vector<int> posTile;
    vector<int> posVer;
    vector<int> posEdge;
    public:
    void vist(Edge&);
    void vist(Vertex&);
};


#endif