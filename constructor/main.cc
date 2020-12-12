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
        try {
            //curTurn
            int tmp1 = stoi(s);
            if (tmp1 < 0)
                throw;
            curTurn = tmp1;
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
            int tmp2 = stoi(s);
            if (tmp2 < 0 ) throw;
            geese = tmp2;
        } catch (exception& any) {
            throw InvalidFormat(file);
        }
    }
}


void argsInitial(int len, char**& args,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file, bool& isload) {
    int i;
    unsigned seed = 0;
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
                file = "layout.txt";
                layoutInit(out, layout, file); //transfer string of layout into numbers we use for next board intialization.
            }
            else
            {
                InvalidOpenDefault e;
                throw e;
            }
        }

        // user give arguments
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
                isload = 1;
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

inline int readInt(int a, int b) {
    cin.exceptions(ios::eofbit|ios::failbit);
    int m;
    while (true) {
        try {
            cin>>m;
            if (m<a || m> b) throw out_of_range("Error: integer out of range");
            return m;
        } catch (out_of_range &r) {
            cout<<r.what()<<endl;
        }
        catch (exception& e) {
            cout<<"Error: isn't a valid integer"<<endl;
        }
    }
}

int main(int argc, char* argv[]) {
    vector< pair<int, int> > layout(0);
    int curTurn = -1;
    vector<string> curData(0);
    int geese = -1;
    string file = "";

    bool isload = 0;
    // argument passing
    try {
        argsInitial(argc, argv, layout, curTurn, curData, geese, file, isload);
    } catch (exception& e) {
        cout << e.what() <<endl;
        return 1;
    }
    
    //initialize board by mutating the blank board.
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
    
    
    for( int i = 0; i < NUM_PLAYER && isload == 0;) {
        string prompt = "Builder <"+board.getPlayerColour(i);+">, where do you want to build a basement?";
        cout<<prompt<<endl;
        try {
            int pos;
            cin>>pos;
            if (pos<0||pos>NUM_VERTEX) throw out_of_range("pos");
            board.buildRes(pos, i);
            i++;
        }
        catch (exception& e) {
            if (cin.eof()) {
                cout<<"End of file reached."<<endl;
                return;
            } else
            cout<<"Error"<< prompt << " isn't a valid integer." <<endl;
        }
    }

    for( int i = NUM_PLAYER - 1; i >= 0 && isload == 0;) {
        string prompt = "Builder <"+board.getPlayerColour(i);+">, where do you want to build a basement?";
        cout<<prompt<<endl;
        try {
            int pos;
            cin>>pos;
            if (pos<0||pos>NUM_VERTEX) throw out_of_range("pos");
            board.buildRes(pos, i);
            i--;
        } catch (exception& e) {
            if (cin.eof()) {
                cout<<"End of file reached."<<endl;
                return;
            }
            cout<<"Error"<< prompt << " isn't a valid integer." <<endl;
        }
    }

    // Game start

    while (!board.checkWinner())
    {
        for (int i = 0; i < NUM_PLAYER; i++)
        {
            cout << "builder " + board.getPlayerColour(i) + "'s turn." << endl;
            try
            {

                // roll the dice
                while (std::cin >> cmd)
                {
                    if (cmd == "help" )
                    {
                        cout<<"Valid commands:"<<endl;
                        cout<<"~ load : changes current builder's dice type to 'loaded'"<<endl;
                        cout<<"~ fair : changes current builder's dice type to 'fair'"<<endl;
                        cout<<"~ roll : rolls the dice and distributes resources."<<endl;
                        cout<<"~ status : prints the current status of all builders in order from builder 0 to 3."<<endl;
                        cout<<"~ help : prints out the list of commands."<<endl;
                    }
                    else if (cmd == "load")
                    {
                        board.setLoad();
                    }
                    else if (cmd == "fair")
                    {
                        board.setFair();
                    }
                    else if (cmd == "roll")
                    {
                        board.roll();
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid command." << std::endl;
                    }
                }

                // actions
                cout<<"Enter a command"<<endl;
                while (std::cin >> cmd)
                {
                    if (cmd == "help" )
                    {
                        cout<<"Valid commands:"<<endl;
                        cout<<"~ board : prints the current board."<<endl;
                        cout<<"~ status : prints the current status of all builders in order from builder 0 to 3."<<endl;
                        cout<<"~ residences : prints the residences the current builder has currently completed."<<endl;
                        cout<<"~ build - road <road#> : attempts to builds the road at <road#>."<<endl;
                        cout<<"~ build - res <housing#> : attempts to builds a basement at <housing#>."<<endl;
                        cout<<"~ improve <housing#> : attempts to improve the residence at <housing#>."<<endl;
                        cout<<"~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>."<<endl;
                        cout<<"~ market <sell> <buy> : attempts to sell resources on the market, giving four resource of type <sell> and receiving one resource of type <buy>."<<endl;
                        cout<<"~ next : passes control onto the next builder in the game."<<endl;
                        cout<<"~ save <file> : saves the current game state to <file>."<<endl;
                        cout<<"~ help : prints out the list of commands."<<endl;
                    }
                    else if (cmd == "load")
                    {
                        board.setLoad();
                    }
                    else if (cmd == "fair")
                    {
                        board.setFair();
                    }
                    else if (cmd == "roll")
                    {
                        board.roll();
                    }
                    else if (cmd == "board")
                    {
                        board.printBoard();
                    }
                    else if (cmd == "status")
                    {
                        board.printStatus();
                    }
                    else if (cmd == "residences")
                    {
                        board.printRes();
                    }
                    else if (cmd == "build-road")
                    {
                        int pos = readInt(0, NUM_EDGE);
                        board.buildRoad(pos, i);
                    }
                    else if (cmd == "build-res")
                    {
                        int pos = readInt(0, NUM_VERTEX);
                        board.buildRes(pos, i);
                    }
                    else if (cmd == "improve")
                    {
                        int pos = readInt(0, NUM_VERTEX);
                        board.improve(pos, i);
                    }
                    else if (cmd == "trade")
                    {
                        
                        int pos = -1;
                        while(pos == -1) {
                            string who;
                            cin>>who;
                            for(int i = 0; i<NUM_PLAYER; i++) {
                                if (who.compare(board.getPlayerColour(i)) == 0) {
                                    pos = i;
                                    break;
                                }
                            }
                            cout<<"Invalid colour"<<endl;
                        }
                        
                        string give, take;
                        std::cin >> give >> take;
                    }
                    else if (cmd == "next")
                    {
                        break;
                    }
                    else if (cmd == "save")
                    {   
                        string saveFile;
                        cin>>saveFile;
                        board.save(saveFile);
                    }
                    else
                    {
                        std::cout << "Invalid command." << std::endl;
                    }
                }
            }
            catch (ios::failure &)
            {
                cout<<"End of file reached."<<endl;
                board.save("backup.sv");
                return 1;
            }
        }
    }
}
