#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <sstream>
#include "board.h"

using namespace std;

extern const int NUM_TILE;

extern const int NUM_VERTEX;

extern const int NUM_EDGE;

extern const int NUM_PLAYER;

int main(int argc, char* argv[]) {
    vector< pair<int, int> > layout(0);
    int curTurn = -1;
    vector<string> curData(0);
    int geese = -1;
    
    string file = "";
    int winner = -1;

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
        cout<<board.getTD();
    } catch (exception& e) {
        InvalidFormat a(file);
        cout<<a.what()<<endl;
        return 1;
    }
    
    for( int i = 0; i < NUM_PLAYER && isload == 0;) {
        string prompt = "Builder "+getPlayerColour(i)+" where do you want to build a basement? ";
        cout<<prompt<<endl;
        cout << "> ";
        try {
            cin.exceptions(ios::eofbit|ios::failbit);
            int pos;
            cin>>pos;
            if (pos<0||pos>NUM_VERTEX) throw out_of_range("pos");
            board.buildRes(pos, i, true);
            i++;
        } catch (invalid_build& e) {
            cout<<e.what()<<endl;
            board.printCurbuilt();
        }
        catch (exception& e) {
            cin.clear();
            if (cin.eof()) {
                cout<<"End of file reached."<<endl;
                return 1;
            } else {
                string a;
                getline(cin,a);
                cout<<"Error: "<< prompt << " isn't a valid integer." <<endl;
            }
        }
    }

    for( int i = NUM_PLAYER - 1; i >= 0 && isload == 0;) {
        string prompt = "Builder "+getPlayerColour(i)+" where do you want to build a basement?";
        cout<<prompt<<endl;
        cout << "> ";
        try {
            cin.exceptions(ios::eofbit|ios::failbit);
            int pos;
            cin>>pos;
            if (pos<0||pos>NUM_VERTEX) throw out_of_range("pos");
            board.buildRes(pos, i, true);
            i--;
        } catch (invalid_build& e) {
            cout<<e.what()<<endl;
            board.printCurbuilt();
        }
        catch (exception& e) {
            cin.clear();
            if (cin.eof()) {
                cout<<"End of file reached."<<endl;
                return 1;
            } else {
                string a;
                getline(cin,a);
                cout<<"You cannot build here." <<endl;
                board.printCurbuilt();
            }
        }
    }

    // Game start

    cout<<board.getTD();

    while (!board.checkWinner(winner))
    {
        for (int i = 0; i < NUM_PLAYER; i++)
        {
            cout << "Builder "<<getPlayerColour(i)<<"'s turn." << endl;
            cout << "> ";
            try
            {

                // roll the dice
                while (true)
                {   std::cin >> cmd;
                    if (cmd == "help" )
                    {
                        cout<<"Valid commands:"<<endl;
                        cout<<"~ load : changes current builder's dice type to 'loaded'"<<endl;
                        cout<<"~ fair : changes current builder's dice type to 'fair'"<<endl;
                        cout<<"~ roll : rolls the dice and distributes resources."<<endl;
                        cout<<"~ status : prints the current status of all builders in order from builder 0 to 3."<<endl;
                        cout<<"~ help : prints out the list of commands."<<endl;
                        cout<<"> ";
                    }
                    else if (cmd == "load")
                    {
                        board.setLoad();
                        cout<<"Builder "<<getPlayerColour(i)<<" now has loaded Dice."<<endl;
                        cout << "> ";
                    }
                    else if (cmd == "fair")
                    {
                        board.setFair();
                        cout<<"Builder "<<getPlayerColour(i)<<" now has fair Dice."<<endl;
                        cout << "> ";
                    }
                    else if (cmd == "roll")
                    {
                        bool valid = false;
                        while ( !valid ) {
                            board.roll(valid);
                        }
                        
                        break;
                    }
                    else if (cmd == "status")
                    {
                         board.printStatus();
                         cout << "> ";
                    }
                    else
                    {
                        std::cout << "Invalid command." << std::endl;
                        std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
                        std::cout << "> ";
                    }
                }

                int dice = board.getDiceNum();
                cout<<"Now you have : "<<dice<<endl;
                if (dice == 7) {
                    board.geeseSteal();
                    cout <<"Choose where to place the GEESE."<<endl;
                    cout << "> ";
                    int n = readInt(0, 18);
                    board.setGeese(n, i);
                } else {
                    board.resourceProduce(dice);
                }

                // actions
                
                while (true)
                {
                    cin.exceptions(ios::failbit|ios::eofbit);
                    cout<<"Enter a command"<<endl;
                    cout<<"> ";
                    std::cin >> cmd;
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
                        board.printRes(i);
                    }
                    else if (cmd == "build-road")
                    {
                        while (true) {
                            try {
                                int pos = readInt(0, NUM_EDGE);
                                board.buildRoad(pos, i);
                            } catch (exception& e) {
                                cout<<e.what()<<endl;
                            }
                            break;
                        }
                    }
                    else if (cmd == "build-res")
                    {
                        cout << "main: 230 build-res: "  << endl;
                        while (true) {
                            try {
                                int pos = readInt(0, NUM_VERTEX);
                                cout << "pos: " << pos << endl;
                                board.buildRes(pos, i);
                            } catch (exception& e) {
                                cout<<e.what()<<endl;
                            }
                            break;
                        }
                        
                    }
                    else if (cmd == "improve")
                    {
                        while (true) {
                            try {
                                int pos = readInt(0, NUM_VERTEX);
                                board.improve(pos, i);
                            } catch (exception& e) {
                                cout<<e.what()<<endl;
                            }
                            break;
                        }
                    }
                    else if (cmd == "trade")
                    {
                        
                        int pos = -1;
                        int give;
                        int take;
                        readPlayer(pos);
                        readResource(give);
                        readResource(take);
                        board.trade(i,pos,give,take);
                    }
                    else if (cmd == "next")
                    {
                     cout<<board.getTD();
                     break;
                    }
                    else if (cmd == "save")
                    {   
                        string saveFile;
                        cin>>saveFile;
                        board.save(i, saveFile);
                    }
                    else
                    {
                        std::cout << "Invalid command." << std::endl;
                    }
                }
            }
            catch (exception& e)
            {
                if (cin.eof()) {
                    cout<<"End of file reached."<<endl;
                    board.save(i, "backup.sv");
                    return 1;
                }
                cout<<e.what()<<endl;

            }
        }
    }
}
