#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <memory>
#include <vector>

using namespace std;

class TextDisplay;


class Subject {
    vector<shared_ptr<Observer>>* tiles_ptr;
    vector<shared_ptr<Observer>>* builders_ptr;
    shared_ptr<Observer> td;

    public:
    virtual void AttachRoad( Observer *);
    virtual void AttachRes( Observer *);
    virtual void AttachImprove( Observer *);
    virtual void AttachBuilder( Observer *);
    virtual void notifyRoad( );
    virtual void notifyRes( );
    virtual void notifyImprove( );
    virtual void notifyBuilder( );

};


#endif
