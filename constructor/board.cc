#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "board.h"

using namespace std;


void Board::init( int curTurn, vector<string>& builderData, vector< pair<int, int> >& board, int geese ) {
    // init edges
    for ( int i = 0; i <= 71; i++) {
        edges.emplace_back(new Edge(i, -1)); // -1 represent no owner
        edges.at(i)->attach(make_shared<vector<shared_ptr<Vertex>>> (vertices),
        make_shared<vector<shared_ptr<Edge>>> (edges), td);
    }
    // init vertices
    for ( int i = 0; i <=53; i++) {
        vertices.emplace_back(new Vertex(i, 'N', -1)); // 'N' represent no residence, -1 represent no owner
        edges.at(i)->attach(make_shared<vector<shared_ptr<Vertex>>> (vertices),
        make_shared<vector<shared_ptr<Edge>>> (edges), td);
    }
    // init tiles
    vector<vector<int>> tileV = {{0,1,4,9,8,3}, {2,3,8,14,13,7}, {4,5,10,16,15,9}, {6,7,13,19,18,12}, {8,9,15,21,20,14}, 
                                    {10,11,17,23,22,16}, {13,14,20,26,25,19}, {15,16,22,28,27,21}, {18,19,25,31,30,24}, {20,21,27,33,32,26}, 
                                    {22,23,29,35,34,28}, {25,26,32,38,37,31}, {27,28,34,40,39,33}, {30,31,37,43,42,36}, {32,33,39,45,44,38}, 
                                    {34,35,41,47,46,40}, {37,38,44,49,48,43}, {39,40,46,51,50,45}, {44,45,50,53,52,49}};
    vector<vector<int>> tileE = {{0,2,7,10,6,1}, {3,6,14,18,13,5}, {4,8,16,19,15,7}, {9,13,21,26,20,12}, {10,15,23,27,22,14}, 
                                    {11,17,25,28,24,16}, {18,22,31,35,30,21}, {19,24,33,36,32,23}, {26,30,38,43,37,29}, {27,32,40,44,39,31}, 
                                    {28,34,42,45,41,33}, {35,39,48,52,47,38}, {36,41,50,53,49,40}, {43,47,55,60,54,46}, {44,49,57,61,56,48}, 
                                    {45,51,59,62,58,50}, {52,56,64,67,63,55}, {53,58,66,68,65,57}, {61,65,70,71,69,64}};
    
    for ( int i = 0; i <= 18; i++) {
        tiles.emplace_back(new Tile(i, board.at(i).second, board.at(i).first));
        for ( auto v: tileV.at(i) ) {
            tiles.at(i)->attachV(vertices.at(v));
        }
        for ( auto e: tileE.at(i) ) {
            tiles.at(i)->attachE(edges.at(e));
        }
        tiles.at(i)->attachB(make_shared<vector<shared_ptr<Builder>>> (builders));
    }

    // init td
    td = make_shared<TextDisplay>(board);

    // init builders
    for ( int i = 0; i < 4; i++) {
        if (builderData.empty()) 
        builders.emplace_back(new Builder( static_cast<Colour>(i), td));
        else
        builders.emplace_back(new Builder( static_cast<Colour>(i), td, builderData.at(i)));
        builders.back()->attach(make_shared<vector<shared_ptr<Vertex>>> (vertices),
        make_shared<vector<shared_ptr<Edge>>> (edges), td);
    }

    // set owner for edge and vetice
    for ( int i = 0; i < 4; i++) {
        vector<int> & temRoad = builders.at(i)->getRoads();
        for ( auto r: temRoad) {
            edges.at(r)->buildRoad(i);
        }
        vector< pair<int, char> > & tmpRes = builders.at(i)->getHousing();
        for ( auto r: tmpRes) {
            vertices.at(r.first)->buildRes(i, r.second);
        }
    }


    // init geese
    this->geese = geese;

    // init dice
    this->dice = make_shared<LoadedDice> ();

}

void Board::setLoad() {
    this->dice = make_shared<LoadedDice>();
}

void Board::setFair() {
    this->dice = make_shared<FairDice>();
}

void Board::roll() {
    this->dice->roll();
}

int Board::getDiceNum() {
    return dice->getNum();
};


void Board::printCurbuilt() {
    string a ="";
    for (auto i: curbuilt) {
        a+=to_string(i);
        a+=" ";
    }
    cout<<"Basements already exist as locations: "<<a<<endl;
}


void Board::buildRes(int pos, int player, bool init) {
    for (auto i: tiles) {
        int v = i->checkVertex(pos);
        if (v == -1) continue;
        if (i->checkAdjRes(v) == true) {
            if (init == 1) {
                throw invalid_build();
            }
            cout<<invalid_build().what()<<endl;
            return;
        } else if (i->checkAdjRoad(v, player) == false && init == 0) {
            cout <<invalid_build().what()<<endl;
            return;
        }
    }
    auto builder = builders.at(player);
    builder -> buyRes(pos, player, init);

    if (vertices.at(pos)->getOwner() != -1 && init == 1) {
        curbuilt.emplace_back(pos);
    }
}

void Board::buildRoad(int pos, int player) {
    for (auto i: tiles) {
        int v = i->checkEdge(pos);
        if (v == -1) continue;
        if (i->checkAdjRes_road(v, player) == false) {
            cout<<invalid_build().what()<<endl;
            return;
        } else if (i->checkAdjRoad_road(v, player) == false) {
            cout <<invalid_build().what()<<endl;
            return;
        }
    }

    auto builder = builders.at(player);
    try {
        builder -> buyRoad(pos, player);
    }
    catch (exception& e) {
        cout<< e.what() <<endl;
    }   
}

void Board::improve(int pos, int player) {
    auto builder =builders.at(player);
    try {
        builder -> buyImprove(pos, player);
    }
    catch (exception& e) {
        cout<< e.what() <<endl;
    }
}


bool Board::checkWinner(int& winner) {
    for (auto i: builders) {
        if (i->getPoint() >= SCORE_TO_WIN) {
            winner = i->getPlayerNum();
            return true;
        }
    }
    return false;
}

void Board::resourceProduce(int dice) {
    cout << "Board resProduce: " << dice << endl;
    for (auto i: tiles) {
        if (dice == i->getTileValue()) {
            i->giveResource();
        }
    }
}

void Board::trade(int i, int who, int give, int take) {
    cin.exceptions(ios::eofbit|ios::failbit);
    if(checkResource(i, give) == false) {

    } else if (checkResource(who, take) == false) {

    } else {
        string colour1 = getPlayerColour(i);
        string colour2 = getPlayerColour(who);
        string resource1 = getResource(give);
        string resource2 = getResource(take);
        cout<<colour1<< "offers "<<colour2<<" one "<<resource1<<" for one "<<resource2
        <<".Does "<<colour2<<" accept this offer?"<<endl;
        string reply;
        cin>>reply;
        to_lowercase(reply);
        if (reply == "yes") {
            builders.at(i).trade(buidlers.at(who), give, take);
        } else {
            cout<<colour2<<" declined the trade."<<endl;
        }
    }
    
}

void Board::printBoard() {
    cout<<*td<<endl;
}

void Board::printStatus() {
    for (auto i: builders) {
        i->printStatus();
    }
}

void Board::printRes(int player) {
    builders.at(player)->printRes();
}

void Board::geeseSteal() {
    tiles.at(geese)->geeseSteal();
}

void Board::setGeese(int n, int p) {
    tiles.at(geese)->geeseMove(p);
    tiles.at(n)->geeseMove(p);
}

void Board::save(string) {

}

