#include "builder.h"


using namespace std;

Builder::Builder(Colour c, shared_ptr<TextDisplay> td, string data) {

    // init colour
    colour = c;


    unsigned int rPos = data.find("r");
    unsigned int hPos = data.find("h");
    if ( rPos == string::npos || hPos == string::npos || rPos >= hPos) throw exception();
    string resourceData = data.substr(0, rPos);
    string roadData = data.substr(rPos, hPos-rPos);
    string houseData = data.substr(hPos);

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

    // textdisplay update
    this->td = td;
    // update road
    string owner;
    if ( c == Colour::Blue) {
        owner = "B";
    } else if ( c == Colour::Red) {
        owner = "R";
    } else if ( c == Colour::Orange) {
        owner = "O";
    } else {
        owner = "Y";
    }
    for ( auto r: roads) {
        td->update("e", r, owner, "R");
    }
    for ( auto h: housing) {
        td->update("v", h.first, owner, string(1,h.second));
    }

}

void Builder::losehalf() {
    std::vector<int> v;
    for(int i = 0; i < 5; i++) { // 5 types of resources
        for (int n = this->resource[i]; n != 0; n--) { // number of each type.
            v.emplace_back(i); 
        }
    }
	// use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    int half = v.size()/2;
    vector<int> lost (5);
    for (int i = 0; i < half; i++) {
        lost.at(v.at(i)) += 1;
    }
    for (int i = 0; i < 5; i++) {
        this->resource.at(i) -= lost.at(i);
        cout<<"<"<<lost.at(i)<<"> <"<<getResource(i)<<">"<<endl;
    }

}

const vector<int> Builder::resourcelist() {
    return this->resource;
}

void Builder::steal(shared_ptr<Builder> who) {
    std::vector<int> v;
    for(int i = 0; i < 5; i++) { // 5 types of resources
        for (int n = who->resource[i]; n != 0; n--) { // number of each type.
            v.emplace_back(i); 
        }
    }

	// use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    who->resource[v[0]] -= 1;
    this->resource[v[0]] += 1;
    cout<<"Builder <"<<getPlayerColour(this->getPlayerNum())<<"> steals <"<<getResource(v[0])
    <<"> from builder <"<<getPlayerColour(who->getPlayerNum())<<">."<<endl;
}

class no_enough_resources : public exception {
    public:
    const char* what() const noexcept override {return "You do not have enough resources.";}
};

void Builder::buyRes(int n, int p, bool init) {
    if (init) {
        this->notifyRes(n, p);
        return;
    } //initialization
    int& brick = this->resource[static_cast<int>(Resource::BRICK)];
    int& energy = this->resource[static_cast<int>(Resource::ENERGY)];
    int& glass = this->resource[static_cast<int>(Resource::GLASS)];
    int& wifi = this->resource[static_cast<int>(Resource::WIFI)];
    if (brick >= 1 && energy >= 1 && glass >=1 && wifi >= 1) {
        try {
            this->notifyRes(n, p);
        } catch (exception &e) {
            cout<<e.what()<<endl;
            return;
        }
        housing.emplace_back(n,'B');
        brick--;
        energy--;
        glass--;
        wifi--;
        sort(housing.begin(), housing.end(), [](auto i, auto j) {
        return i<j;
    });
        this->points += 1;
        string player;
        if ( p == 0) {
            player = "B";
        } else if ( p == 1) {
            player = "R";
        } else if ( p == 2) {
            player = "O";
        } else {
            player = "Y";
        }
        td->update("v", n, player, "B");
    } else {
        cout<<"You do not have enough resources."<<endl;
    }
}

void Builder::buyRoad(int n, int p) {
    int& heat = this->resource[static_cast<int>(Resource::HEAT)];
    int& wifi = this->resource[static_cast<int>(Resource::WIFI)];
    if (heat>=1 && wifi >= 1) {
        try {
            this->notifyRoad(n, p);
        } catch (exception &e) {
            cout<<e.what()<<endl;
            return;
        }
        roads.emplace_back(n);
        this->points += 1;
        string player;
        if ( p == 0) {
            player = "B";
        } else if ( p == 1) {
            player = "R";
        } else if ( p == 2) {
            player = "O";
        } else {
            player = "Y";
        }
        td->update("e", n, player, "R");
        sort(roads.begin(), roads.end());
    } else {
        cout<<"You do not have enough resources."<<endl;
    }
}


void Builder::buyImprove(int n, int p) {
    vector< pair<int, char> >::iterator f = find_if(housing.begin(), housing.end(),[n](auto i) { 
        if(get<0>(i) == n) return true;
        else return false;
    });
    char& cur = get<1>(*f);
    int& brick = this->resource[static_cast<int>(Resource::BRICK)];
    int& energy = this->resource[static_cast<int>(Resource::ENERGY)];
    int& glass = this->resource[static_cast<int>(Resource::GLASS)];
    int& wifi = this->resource[static_cast<int>(Resource::WIFI)];
    int& heat = this->resource[static_cast<int>(Resource::HEAT)];
    if (f == housing.end()) {
        cout<<"Invalid residence."<<endl;
    } else if (cur == 'T') {
        cout<< "You can't improve that building."<<endl;
    } else if (cur == 'H') {
        if (glass>=2 && heat >= 3) {
            try {
                this->notifyImprove(n, p);
            } catch (exception &e) {
              cout<<e.what()<<endl;
              return;
            }
            glass-=2;
            heat-=3;
            this->points += 2;
            this->points += 1;
            string player;
            if ( p == 0) {
                player = "B";
            } else if ( p == 1) {
                player = "R";
            } else if ( p == 2) {
                player = "O";
            } else {
                player = "Y";
            }
            td->update("v", n, player, "T");
        } else {
            cout<<"You do not have enough resources."<<endl;
            cout<<endl<<"The cost to improve a Basement to a House is two GLASS and three HEAT resource."<<endl;
            cout<<"The cost to improve a House to a Tower is three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT."<<endl;
        }
        
    } else if (cur == 'B') {
        if (brick >= 3 && energy >=2 && glass >= 2 && wifi>=1 && heat >=2) {
            this->notifyImprove(n, p);
            brick -=3;
            energy -=2;
            glass -=2;
            wifi -=1;
            heat -=2;
            this->points += 3;
            string player;
            if ( p == 0) {
                player = "B";
            } else if ( p == 1) {
                player = "R";
            } else if ( p == 2) {
                player = "O";
            } else {
                player = "Y";
            }
            td->update("v", n, player, "H");
        } else {
            cout<<"You do not have enough resources."<<endl;
            cout<<endl<<"The cost to improve a Basement to a House is two GLASS and three HEAT resource."<<endl;
            cout<<"The cost to improve a House to a Tower is three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT."<<endl;
        }
    }
}


int Builder::getPlayerNum() {
        return static_cast<int> (colour);
}

int Builder::getPoint() {
        return this->points;
}

void Builder::gain(int r, int num) {
    this->resource.at(r) += num;
}


void Builder::printStatus(){
    string text = "Builder " +getPlayerColour(static_cast<int>(colour)) +
    "    has "+to_string(points)+" building points, "+to_string(resource.at(0))+
    " BRICK, "+to_string(resource.at(1))+" ENERGY, "+to_string(resource.at(2))+" GLASS, "+to_string(resource.at(3))+" HEAT, "+to_string(resource.at(4))+" WIFI.";
    cout<<text<<endl;
}

void Builder::printRes() {
    cout<<getPlayerColour(static_cast<int> (colour))<<" has built: "<<endl;
    for (auto i: housing) {
        cout<< i.first <<" "<< i.second;
    }
}

vector<int> & Builder::getRoads(){
    return this->roads;
}
vector<pair<int,char>> & Builder::getHousing(){
    return this->housing;
}
