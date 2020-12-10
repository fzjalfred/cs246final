#include <iostream>
#include <string>
#include "board.h"
using namespace std;


int main(int argc, char* argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Board board;

    try {
        while (std::cin>>cmd) {
            if (cmd == "load") {
                board.setLoad();
            }
            else if (cmd == "fair") {
                board.setFair();
            }
            else if (cmd == "roll") {
                board.roll();
            }
            else if (cmd == "board") {}
            else if (cmd == "status") {}
            else if (cmd == "residences") {}
            else if (cmd == "build-road") {
                int pos;
                std::cin>>pos;
            } 
            else if (cmd == "build-res") {
                int pos;
                std::cin>>pos;
            }
            else if (cmd == "improve") {
                int pos;
                std::cin>>pos;
            }
            else if (cmd == "trade") {
                int pos;
                string give, take;
                std::cin>>pos>>give>>take;
            }
            else if (cmd == "next") {}
            else if (cmd == "save") {
                string file;
                std::cin>>file;
            }
            else if (cmd == "help") {}
            else {
                std::cout<< "Invalid command."<<std::endl;
            }
        }
    } catch (ios::failure &) {} 
}
