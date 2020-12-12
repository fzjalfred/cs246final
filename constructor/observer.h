#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "settings.h"
#include "info.h"

class Subject;

class Observer {
    public:
    virtual void buildRes(int p);
    virtual void buildRoad(int p);
    virtual void builderObtain(enum Resource type, int num);
    virtual void builderImprove(int);
    virtual void mutator(enum Resource type, int num); 
};

#endif
