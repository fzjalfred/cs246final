#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include "board.h"

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

//==============================================================================================================


void layoutInit(string& out, vector<pair<int, int>>& layout, string& file) {
    try {
        vector<pair<int, int>> tmp;
        for (int i = 1; i <= 2 * (NUM_TILE + 1); i += 2)
        {
            tmp.emplace_back(out[i], out[i + 1]);
        }
    } catch (exception &e) {
        throw InvalidFormat(file);
    }
}

void cmdLoadInit(std::ifstream& fin,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file) {
    while (!fin.eof()) {
        string s;
        string out;
        getline(fin, s);
        int tmp;
        try {
            //curTurn
            tmp = stoi(s);
            if (curTurn < 0)
                throw;
            curTurn = tmp;
            //curData
            for (int i = 1; i < NUM_PLAYER; i++)
            {
                getline(fin, s);
                curData.emplace_back(s);
            }
            //board
            getline(fin, out);
            layoutInit(out, layout, file);
            //geese
            getline(fin, s);
            tmp = stoi(s);
            if (curTurn < 0 ) throw;
            geese = tmp;
        } catch (exception& any) {
            throw InvalidFormat(file);
        }
    }
}


void argsInitial(int len, char**& args,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file) {
    int i;
    unsigned seed;
    string out;
    try
    {
        string preCmd = ""; // used in MultiArg exception

        // default cmd
        if ( len == 1) {
            ifstream fin("layout.txt", ios::in); // open file
            if (fin.is_open())
            {
                getline(fin, out);
                file = args[i];
                layoutInit(out, layout, file); //transfer string of layout into numbers we use for next board intialization.
            }
            else
            {
                InvalidOpenDefault e;
                throw e;
            }
        }

        // user give cmds
        for (i = 1; i < len; i++)
        {
            string s = args[i];
            if (s == "-seed") 
            {
                if (++i == len){
                    throw MissingArg(s, "seed");
                }
                seed = stoi(args[i]);
            }
            else if (s == "-load")
            {   
                
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                cout<<"run -board3"<<endl;
                if (++i == len){
                    throw MissingArg(s, "filename");
                }
                
                ifstream fin(args[i], ios::in); // open file
                if (fin.is_open()) {
                    file = args[i];
                    cmdLoadInit(fin, layout, curTurn, curData, geese, file); // intiliaze everything with cmd -load
                } else 
                {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }

            }
            else if (s == "-board")
            {   
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                if (++i == len)
                {
                throw MissingArg(s, "filename");
                }
                ifstream fin(args[i], ios::in); // open file
                if (fin.is_open()) {
                    getline(fin, out);
                    file = args[i];
                    layoutInit(out, layout, file); //transfer string of layout into numbers we use for next board intialization.
                } else {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }
            }
            else if (s == "-random-board")
            {   
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                std::default_random_engine rng{seed};        // random generator
                vector<int> resources = {0,1,2,3,4,5};
                vector<int> tiles;
                for(int i=0; i<= NUM_TILE;i++) {
                    tiles.emplace_back(i);
                }
                shuffle(tiles.begin(), tiles.end(), rng);
                for(int i=0; i <= NUM_TILE;i++) {
                    shuffle(resources.begin(), resources.end(), rng);
                    layout.emplace_back(resources[0],tiles[i]);
                }
            }
            else
            {
                UnrecognizedArg e(s);
                throw e;
            }
        }
    }
    catch (invalid_argument &e) {
        InvalidFormat a(file);
        throw a;
    }
    catch (exception &e)
    {
        throw;
    }
} 

int main(int argc, char* argv[]) {
    vector< pair<int, int> > layout(0);
    int curTurn = -1;
    vector<string> curData(0);
    int geese = -1;
    string file = "";

    // argument passing
    try {
        argsInitial(argc, argv, layout, curTurn, curData, geese, file);
    } catch (exception& e) {
        cout << e.what() <<endl;
        return 1;
    }
    

    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Board board;
    try {
        board.init(curTurn, curData, layout, geese);
    } catch (exception& e) {
        InvalidFormat a(file);
        cout<<a.what()<<endl;
        return 1;
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
