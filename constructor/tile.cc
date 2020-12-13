#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "element.h"
#include "tile.h"

extern string getPlayerColour(int);
extern string getPlayerNum(shared_ptr<Builder>);
extern void readPlayer(int&);

using namespace std;

Tile::Tile(int num, int value, int resource, bool isGeese ) : 
    num{num}, value{value}, resource{resource}, isGeese{isGeese} {}

vector<shared_ptr<Builder>> Tile::ownerlist() {
    vector<shared_ptr<Builder>> v;
    for(auto i: vertices) {
        int p = i->getOwner();
        if (p != -1){
            v.emplace_back(builders->at(p));
        }
        
    }
    return v;
}

void Tile::geeseSteal() {
    // geese steal
    for_each(builders->begin(), builders->end(), [](auto i) {
        int total = 0;
        for (auto k : i->resourcelist())
        {
            total += k;
        }
        if (total >= 10)
        {
            i->losehalf();
        }
    });
}

void Tile::geeseMove(int p) {
        if (isGeese == false) {
            isGeese = true;
            // player steal
            vector<shared_ptr<Builder>> stealist(0);
            auto owners = this->ownerlist();
            for (auto &i: owners){
                int total = 0;
                for (auto k: i->resourcelist()){
                    total+=k;
                }
                if (total >= 1) {
                    stealist.emplace_back(i);
                }
            }
            if (stealist.empty()) {
                cout<<"Builder <"<<getPlayerColour(p)<<"> has no builders to steal from.";
            }else {
                string strlist = "";
                for_each(stealist.begin(), stealist.end(), [&strlist](auto i) {
                    strlist += getPlayerColour(i->getPlayerNum());
                });
                cout << "Builder <" << getPlayerColour(p) << "> can choose to steal from [" << strlist << "].";
                cout << "Choose a builder to steal from." << endl;
                int who = -1;
                while (find_if(stealist.begin(), stealist.end(), [who](auto i) {
                           return i->getPlayerNum() == who;
                       }) != stealist.end())
                {
                    readPlayer(who);
                }
                builders->at(p)->steal(stealist.at(who));
            }
        }
        else 
        isGeese = false;

    }

void Tile::attachV(shared_ptr<Vertex> ptr) {
    vertices.emplace_back(ptr);

}

void Tile::attachE(shared_ptr<Edge> ptr) {
    edges.emplace_back(ptr);
}

void Tile::attachB(shared_ptr< vector<shared_ptr<Builder>> > builders) {
    this->builders = builders;
}

