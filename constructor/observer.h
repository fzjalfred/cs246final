#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "resource.h"

class Subject;
class Recource;

class Observer {
  public:
    // Pass in the Subject that called the notify method.
    virtual void builfRes( int num, Subject& who ) = 0; 
    virtual void buildRoad( int num, Subject& who ) = 0;
    virtual void builderObtain( Resource ) = 0;
    virtual void buildImprove( int ) = 0;
    virtual void mutator( Resource ) = 0;

    virtual ~Observer() = default;
};

#endif