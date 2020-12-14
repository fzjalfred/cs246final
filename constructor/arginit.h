#ifndef _ARGINIT_H_
#define _ARGINIT_H_
#include <string>
#include <memory>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <sstream>
#include "info.h"

using namespace std;


//==========================================Exceptions==========================================================
class MissingArg : public exception {
    string t;
    public:
    explicit MissingArg(string arg, string cmd) {t = "ERROR: "+arg+ " missing "+ cmd +" argument";};
    const char* what() const noexcept override {return t.c_str();}
};

class UnrecognizedArg : public exception {
    string t;
    public:
    explicit UnrecognizedArg(string arg) {t = "ERROR: unrecognized argument "+arg;};
    const char* what() const noexcept override {return t.c_str();}
};

class MultiArg : public exception {
    string t;
    public:
    explicit MultiArg(string cmd_use, string cmd_abd) {t = "ERROR: already specified " + cmd_use + " , can't also specify "+ cmd_abd;};
    const char* what() const noexcept override {return t.c_str();}
};

class InvalidOpen : public exception {
    string t;
    public:
    explicit InvalidOpen(string path) {t = "ERROR: Unable to open file " + path + " for board layout.";};
    const char* what() const noexcept override {return t.c_str();}
};

class InvalidOpenDefault : public exception {
    public:
    const char* what() const noexcept override {return "ERROR: Unable to open file layout.txt for default board layout.";}
};

class InvalidFormat : public exception {
    string t;
    public:
    explicit InvalidFormat(string file) {t = "ERROR: "+ file +" has an invalid format.";};
    const char* what() const noexcept override {return t.c_str();}
};

class invalid_build : public exception {
    public:
    const char* what() const noexcept override {return "You cannot build here.";}
};



//==============================================================================================================

int readInt(int a, int b);
void to_lowercase(string &who);
void readPlayer(int& pos);
void readResource(int& pos);
string getPlayerColour(int i);
string getResource(int i);

void layoutInit(string& out, vector<pair<int, int>>& layout, string& file);

void cmdLoadInit(std::ifstream& fin,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file);

void argsInitial(int len, char**& args,  vector<pair<int, int>>& layout, int& curTurn,
 vector<string>& curData, int& geese, string& file, bool& isload);



#endif

