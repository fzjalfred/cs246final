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
    explicit UnrecognizedArg(string arg): arg(arg) {};
    const char* what() const noexcept {string t="ERROR: unrecognized argument "+arg; return t.c_str();}
};

class MultiArg : public exception {
    string cmd_use;
    string cmd_abd;
    public:
    explicit MultiArg(string a, string b): cmd_use(a), cmd_abd(b) {};
    const char* what() const noexcept {string t = "ERROR: already specified " + cmd_use + ", can't also specify "+ cmd_abd; return t.c_str();}
};

class InvalidOpen : public exception {
    string path;
    public:
    explicit InvalidOpen(string path): path(path) {};
    const char* what() const noexcept {string t = "ERROR: Unable to open file " + path + "for board layout."; return t.c_str();}
};

class InvalidFormat : public exception {
    string file;
    public:
    explicit InvalidFormat(string file): file(file) {};
    const char* what() const noexcept {string t = "ERROR: "+ file +" has an invalid format."; return t.c_str();}
};

//==============================================================================================================


void cmdLoadInit(std::ifstream& fin, string& layout, int& curTurn, string& curData, int& geese) {
    while (!fin.eof()) {
        string s;
        getline(fin, s);
        int tmp;
        //curTurn
        try {
            tmp = stoi(s);
            if (curTurn < 0 ) throw;
        } catch (invalid_argument& e) {
            throw;
        }
        curTurn = tmp;
        
        //curData
        for (int i = 1; i < NUM_PLAYER; i++) {
            getline(fin, s);
            curData+=s;
        }
        //board
        getline(fin, layout);
        //geese
        getline(fin, s);
        try {
            tmp = stoi(s);
            if (curTurn < 0 ) throw;
        } catch (invalid_argument& e) {
            throw;
        }

    }
}


void argsInitial(int len, char**& args, string& layout, int& curTurn, string& curData, int& geese) {
    int i;
    try
    {
        string firstCom; // used in MultiArg exception
        string secondCom; // ...
        for (i = 1; i < len; i++)
        {
            string s = args[i];
            if (s == "-seed")
            {
            }
            else if (s == "-load")
            {

                ifstream fin(args[i++], ios::in); // open file

                if (fin.is_open()) {
                    cmdLoadInit(fin, layout, curTurn, curData, geese);
                } else 
                {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }

            }
            else if (s == "-board")
            {
                ifstream fin(args[i++], ios::in); // open file

                if (fin.is_open()) {
                    getline(fin, layout);
                } else {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }
            }
            else if (s == "-random-board")
            {
            }
            else
            {
                UnrecognizedArg e(s);
                throw e;
            }
        }
    }
    catch (invalid_argument &e) {
        string err = args[i];
        InvalidOpen a(err);
        throw a;
    }
    catch (exception &e)
    {
        throw e;
    }
} 

int main(int argc, char* argv[]) {
    string layout;
    int curTurn = -1;
    string curData = "";
    int geese = -1;

    // argument passing
    try {
        argsInitial(argc, argv, layout, curTurn, curData, geese);
    } catch (exception& e) {
        cout << e.what() <<endl;
        return 1;
    }
    

    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Board board;

    // commmand-line arguments
    if (argc < 2) {

    }
    try {

        // command-line options
        
        while (std::cin>>cmd) {
            if (cmd == "load") {
                board.setLoad();
            }
            else if (cmd == "fair") {
                board.setFair();
            }
            else if (cmd == "roll") {
                board.roll();
            }
            else if (cmd == "board") {}
            else if (cmd == "status") {}
            else if (cmd == "residences") {}
            else if (cmd == "build-road") {
                int pos;
                std::cin>>pos;
            } 
            else if (cmd == "build-res") {
                int pos;
                std::cin>>pos;
            }
            else if (cmd == "improve") {
                int pos;
                std::cin>>pos;
            }
            else if (cmd == "trade") {
                int pos;
                string give, take;
                std::cin>>pos>>give>>take;
            }
            else if (cmd == "next") {}
            else if (cmd == "save") {
                string file;
                std::cin>>file;
            }
            else if (cmd == "help") {}
            else {
                std::cout<< "Invalid command."<<std::endl;
            }
        }
    } catch (ios::failure &) {} 
}
