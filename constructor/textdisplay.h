#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H 
#include <iostream>
#include <string>
#include "observer.h"

class Board;

class TextDisplay: public Observer {
    // Grid of characters representing state of the cells. '_' => dead, 'X' => alive
    std::vector<std::vector<char>> theDisplay;

 public:
    explicit TextDisplay( size_t n );

    // Cell/Grid tells text display that status for a Cell has changed and needs to be updated.
    virtual void notify( Subject & whoNotified ) override;

    // Outputs the grid of characters.
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

std::ostream &operator<<(std::ostream &out, const Resource &r);

#endif