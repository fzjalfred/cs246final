#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <memory>
#include <vector>

using namespace std;

class TextDisplay;

class Resource;

class Subject {
    vector<shared_ptr<Observer>>& tiles_ptr;
    vector<shared_ptr<Observer>>& builders_ptr;
    shared_ptr<TextDisplay> td;
};


#endif
