#include <iostream>
#include <sstream>
#include "builder.h"

Builder::Builder(Colour c, string data) {
    colour = c;
    stringstream ss;
    ss << data;
    int brick;
    int energies;
    int glass;
    int heat;
    int wifi;
    char road;
    if ( ss >> brick >> energies >> glass >> heat >> wifi >> road ) {
        resource.at(0) = brick;
        resource.at(1) = energies;
        resource.at(2) = glass;
        resource.at(3) = heat;
        resource.at(4) = wifi;
        if ( road != 'r') {
            throw ;
        }
    }
    int n;
    while
}