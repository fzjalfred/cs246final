#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <memory>
#include <vector>

using namespace std;

class TextDisplay;
class Observer;

class Subject {
    shared_ptr< vector<shared_ptr<Observer>> > vertices;
    shared_ptr< vector<shared_ptr<Observer>> > edges;
    shared_ptr<Observer> td;

    public:
    virtual void attach(shared_ptr< vector<shared_ptr<Observer>> > vertices,
    shared_ptr< vector<shared_ptr<Observer>> > edges,
    shared_ptr<Observer> td);
    void notifyRoad(int n, int p);
    void notifyRes(int n, int p);
    void notifyImprove( int n, int p);
    void notifyBuilder( );

};


#endif
