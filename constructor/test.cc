#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int main(int argc, char* argv[]){
    std::cout << argc << std::endl;
    std::cout << argv[1] << std::endl;
    std::ifstream infile(argv[2]);
    enum resType { BRICK, ENERGY, GLASS, HEAT, WIFI, PARK };
    std::vector< std::pair<std::string, std::string> > layout;
    int r;
    int v;

    while ( infile >> r && infile >> v) {
        std::string tempType;
        std::string tempVal;
        if (infile.fail()) break; 
        switch(r){
            case BRICK : tempType = "  BRICK  ";
            case ENERGY: tempType = "  ENERGY ";
            case GLASS : tempType = "  GLASS  ";
            case HEAT  : tempType = "  HEAT   ";
            case WIFI  : tempType = "  WIFI   ";
            case PARK  : tempType = "  PARK   ";
        }
        if ( v < 10 ) {
            tempVal = " " + std::to_string(v);
        } else {
            tempVal = std::to_string(v);
        }
        layout.push_back(std::make_pair(tempType, tempVal));
    }
    for ( auto n: layout) {
        std::cout << n.first << " " << n.second << std::endl;
    }
}