#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "element.h"
#include "tile.h"

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
    if (isGeese == false)
    {
        isGeese = true;
        // player steal
        vector<shared_ptr<Builder>> stealist(0);
        auto owners = this->ownerlist();
        for (auto &i : owners)
        {
            int total = 0;
            for (auto k : i->resourcelist())
            {
                total += k;
            }
            if (total >= 1)
            {
                stealist.emplace_back(i);
            }
        }
        if (stealist.empty())
        {
            cout << "Builder <" << getPlayerColour(p) << "> has no builders to steal from.";
        }
        else
        {
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

int Tile::getTileValue() {
    return value;
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

void Tile::giveResource() {
    cout << "Tile giveRes" << endl;
    vector<pair<bool, vector<int>>> sum(NUM_PLAYER);
    for (auto &i: sum) {
        i.first = false;
        i.second = vector<int> (NUM_RESOURCE, 0);
    }
    cout<<"flag 2"<<endl;
    bool nogain = 1;
    for (auto &i: vertices) {
        int owner = i->getOwner();
        if (owner == -1) continue;
        else nogain = 0;
        char type = i->getResType();
        switch (type) {
            case 'B':
            sum.at(owner).first = true;
            sum.at(owner).second.at(resource) += 1;
            break;
            case 'H':
            sum.at(owner).first = true;
            sum.at(owner).second.at(resource) += 2;
            break;
            case 'T':
            sum.at(owner).first = true;
            sum.at(owner).second.at(resource) += 3;
            break;
        }
    }
    if (nogain == 1) {
        cout<<"No builders gained resources."<<endl;
    } else {
        cout<<"flag 3"<<endl;
        for (int i = 0; i < NUM_PLAYER; i++) {
            if (sum.at(i).first == true) {
                cout<<"Builder "<<getPlayerColour(i)<<" gained:"<<endl;
                for (int c = 0; c < NUM_RESOURCE; c++) {
                    int num = sum.at(i).second.at(c);
                    string type = getResource(c);
                    builders->at(i)->gain(c, num);
                    cout<< num << type << endl;
                }
            }
        }
    }
}

int Tile::checkVertex(int p) {
    for (int i= 0; i<6; i++) {
        if (vertices.at(i)->getPos() == p) {
            return i;
        }
    }
    return -1;
}

int Tile::checkEdge(int p) {
    for (int i= 0; i<6; i++) {
        if (edges.at(i)->getPos() == p) {
            return i;
        }
    }
    return -1;
}

bool Tile::checkAdjRes(int v) {
    int back;
    int forward;
    if (v == 0) {
        back = 5;
        forward = 1;
    } else if (v == 5) {
        back = 4;
        forward = 0;
    } else {
        back = v-1;
        forward = v+1;
    }
    int a1 = vertices.at(back)->getOwner();
    int a2 = vertices.at(forward)->getOwner();
    if (a1 == -1 && a2 == -1) {
        return false;
    } else return true;
}


bool Tile::checkAdjRoad(int v, int player) {
    int back;
    int forward;
    if (v == 0) {
        back = 5;
        forward = 0;
    } 
    else {
        back = v-1;
        forward = v;
    }
    int a1 = edges.at(back)->getOwner();
    int a2 = edges.at(forward)->getOwner();
    if (a1 == player || a2 == player) return true;
    else return false;
}

bool Tile::checkAdjRes_road(int v, int player) {
    int back;
    int forward;
    if (v == 0) {
        back = 5;
        forward = 0;
    } 
    else {
        back = v-1;
        forward = v;
    }
    int a1 = vertices.at(back)->getOwner();
    int a2 = vertices.at(forward)->getOwner();
    if (a1 == player || a2 == player) return true;
    else return false;

}

bool Tile::checkAdjRoad_road(int v, int player){
    int back;
    int forward;
    if (v == 0) {
        back = 5;
        forward = 1;
    } else if (v == 5) {
        back = 4;
        forward = 0;
    } else {
        back = v-1;
        forward = v+1;
    }
    int a1 = edges.at(back)->getOwner();
    int a2 = edges.at(forward)->getOwner();
    if (a1 == player || a2 == player) return true;
    else return false;
}



