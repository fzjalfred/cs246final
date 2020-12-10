#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "board.h"

using namespace std;


//==========================================Exceptions==========================================================
class UnrecognizedArg : public exception {
    string arg;
    public:
    const char* what() const noexcept {string t="ERROR: unrecognized argument "+arg; return t.c_str();}
};

class MultiArg : public exception {
    string cmd_use;
    string cmd_abd;
    public:
    const char* what() const noexcept {string t = "ERROR: already specified " + cmd_use + ", can't also specify "+ cmd_abd; return t.c_str();}
};

class InvalidOpen : public exception {
    string path;
    public:
    const char* what() const noexcept {string t = "ERROR: Unable to open file " + path + "for board layout."; return t.c_str();}
};

class InvalidFormat : public exception {
    string file;
    public:
    const char* what() const noexcept {string t = "ERROR: "+ file +" has an invalid format."; return t.c_str();}
};
