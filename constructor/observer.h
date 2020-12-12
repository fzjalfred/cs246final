#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "settings.h"

class Subject;

class Observer {
    public:
    virtual void buildRes(int num, Subject& who);
    virtual void buildRoad(int num, Subject& who);
    virtual void builderObtain(enum Resource type, int num);
    virtual void builderImprove(int);
    virtual void mutator(enum Resource type, int num); 
};

#endif
