#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    int curTurn = 0;
    string b0data = "0 0 0 5 0 r 47 43 h 37 T 25 K 30 B";
    string b1data = "0 0 0 0 0 r 56 48 64 h 32 H 44 B";
    string b2data = "11 0 0 0 0 r 24 50 33 41 h 16 H 40 B ";
    string b3data = "0 0 3 0 0 r 27 32 h 20 H 27 H";
    string b4data = "1 2 3 4 5 r h ";
    string board = "0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9";
    int geese = 7;

    string test;
    test = b0data;
    int rPos = test.find("r");
    int hPos = test.find("h");
    vector<int> rescource;
    vector<int> road;
    vector< pair<int, char> > residence;
    try {
        if ( rPos == string::npos || hPos == string::npos || rPos >= hPos) throw exception();
        string resourceData = test.substr(0, rPos);
        string roadData = test.substr(rPos, hPos-rPos);
        string houseData = test.substr(hPos);
        cout << "|" << resourceData << "|" << roadData << "|" << houseData << "|" << endl;

        int resourceDataCounter = 0;
        istringstream iss1(resourceData);
        int currInt;
        while ( iss1 >> currInt) {
            rescource.push_back(currInt);
            resourceDataCounter ++;
        } 
        if ( resourceDataCounter != 5 ) {
            throw exception();
        }

        char cmd;

        istringstream iss2(roadData);
        if ( iss2 >> cmd &&  cmd == 'r') {
            int curr;
            while ( iss2 >> curr) {
                road.push_back( curr );
            }
            if ( iss2.fail() && !iss2.eof() ) {
                throw exception();
            }
        } else {
            throw exception();
        }

        istringstream iss3(houseData);
        if ( iss3 >> cmd && cmd == 'h') {
            int currFirst;
            char currSecond;
            while ( iss3 >> currFirst && iss3 >> currSecond ) {
                if ( currSecond != 'B' && currSecond != 'H' && currSecond != 'T') {
                    throw exception();
                }
                residence.push_back(make_pair(currFirst, currSecond));
            }
            if ( iss3.fail() && !iss3.eof() ) {
                throw exception();
            }
        } else {
            throw exception();
        }

        
    } catch (...) {

    }

    for (auto res: rescource) {
        cout << res << " ";
    }
    cout << endl;
    cout << "road: " ;
    for (auto r: road) {
        cout << r << " ";
    }
    cout << endl;
    cout << "house: ";
    for (auto r: residence) {
        cout << r.first << " " << r.second << ", ";
    }
    cout << endl;
    int points = 0;
    for ( auto h: residence) {
        if ( h.second == 'B' ) {
            points += 1;
        }
        if ( h.second == 'H' ) {
            points += 2;
        }
        if ( h.second == 'T' ) {
            points += 3;
        }
    }
    cout << "points: " << points << endl;

}