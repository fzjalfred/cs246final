#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <memory>

class TextDisplay;

class Element {
  public:
    virtual void accept( std::shared_ptr<TextDisplay> ) = 0; 
};

#endif