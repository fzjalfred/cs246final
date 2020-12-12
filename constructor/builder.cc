#include <iostream>
#include <sstream>
#include <exception>
#include "builder.h"
#include "info.h"

using namespace std;


Builder::Builder(Colour c, string data) {

    // init colour
    colour = c;


    unsigned int rPos = data.find("r");
    unsigned int hPos = data.find("h");
    if ( rPos == string::npos || hPos == string::npos || rPos >= hPos) throw exception();
    string resourceData = data.substr(0, rPos);
    string roadData = data.substr(rPos, hPos-rPos);
    string houseData = data.substr(hPos);
    cout << "|" << resourceData << "|" << roadData << "|" << houseData << "|" << endl;

    // init resource
    int resourceDataCounter = 0;
    istringstream iss1(resourceData);
    int currInt;
    while ( iss1 >> currInt) {
        resource.push_back(currInt);
        resourceDataCounter ++;
    } 
    if ( resourceDataCounter != 5 ) {
        throw exception();
    }

    char cmd;

    // init roads
    istringstream iss2(roadData);
    if ( iss2 >> cmd &&  cmd == 'r') {
        int curr;
        while ( iss2 >> curr) {
            roads.push_back( curr );
        }
        if ( iss2.fail() && !iss2.eof() ) {
            throw exception();
        }
    } else {
        throw exception();
    }

    // init houseData
    istringstream iss3(houseData);
    if ( iss3 >> cmd && cmd == 'h') {
        int currFirst;
        char currSecond;
        while ( iss3 >> currFirst && iss3 >> currSecond ) {
            if ( currSecond != 'B' && currSecond != 'H' && currSecond != 'T') {
                throw exception();
            }
            housing.emplace_back(make_pair(currFirst, currSecond));
        }
        if ( iss3.fail() && !iss3.eof() ) {
            throw exception();
        }
    } else {
        throw exception();
    }

    // init points
    points = 0;
    for ( auto h: housing) {
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

}

void Builder::buyRes(int n, int p) {
    int& brick = this->resource[static_cast<int>(Resource::BRICK)];
    int& energy = this->resource[static_cast<int>(Resource::ENERGY)];
    int& glass = this->resource[static_cast<int>(Resource::GLASS)];
    int& wifi = this->resource[static_cast<int>(Resource::WIFI)];
    if (brick >= 1 && energy >= 1 && glass >=1 && wifi >= 1) {
        this->notifyRes(n, p);
    } else {
        cout<<"You do not have enough resources."<<endl;
    }
}
