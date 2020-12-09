#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer {
    public:
    virtual void buildRes(int num, Subject& who);
    virtual void buildRoad(int num, Subject& who);
    virtual void builderObtain(Resource);
    virtual void builderImprove(int);
    virtual void mutator(Resource&); 
};

#endif
