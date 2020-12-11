#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    int curTurn = 0;
    string b0data = "0 0 0 5 0 r 38 47 43 h 37 T 25 T 30 B";
    string b1data = "0 0 0 0 0 r 56 48 64 h 32 H 44 B";
    string b2data = "11 0 0 0 0 r 24 50 33 41 h 16 H 40 B ";
    string b3data = "0 0 3 0 0 r 27 32 h 20 H 27 H";
    string board = "0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9";
    int geese = 7;

    stringstream ss;
    ss << b0data;
    int brick;
    int energies;
    int glass;
    int heat;
    int wifi;
    char road;
    ss >> brick >> energies >> glass >> heat >> wifi >> road;
    cout << brick << "|" << energies << "|" << glass << "|" << heat << "|" << wifi << "|" << endl;
    int n;
    vector<int> roadData;
    while ( ss >> n ) {
        roadData.push_back(n);
    }
    cout << "road: " ;
    for ( auto r: roadData ) {
        cout << r << " ";
    }
    cout << endl;
    vector< pair<int,char> > resData;
    char type;
    while ( ss >> n >> type ) {
        resData.push_back(make_pair(n, type));
    }
    cout << "Res:" << endl;
    for ( auto n: resData) {
        cout << n.first << " " << n.second << endl;
    }
}