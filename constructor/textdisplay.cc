#include "textdisplay.h"

TextDisplay::TextDisplay() {
    // init v
    for(int i = 0; i <= 53; i++){
        if ( i < 0) {
            v.emplace_back(" " + to_string(i));
        } else {
            v.emplace_back(to_string(i));
        }
    }
    // init e
    for(int i = 0; i <= 71; i++){
        if ( i < 0) {
            e.emplace_back(" " + to_string(i));
        } else {
            e.emplace_back(to_string(i));
        }
    }

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    out << "                    |" + td.v.at(0) + "|--" + td.e.at(0) + "--|" + td.v.at(1) + "|                    " << endl;
    out << "                      |         |                     " << endl;
    out << "                     " + td.e.at(1) + "    0   " + td.e.at(2) + "                     " << endl;
    out << "                      |" + td.tRes.at(0) + "|                     " << endl;
    out << "          |" + td.v.at(2) + "|--" + td.e.at(3) + "--|" + td.v.at(3) + "|" + td.tVal.at(0) + "|" + td.v.at(4) + "|--" + td.e.at(4) + "--|" + td.v.at(5) + "|          " << endl;
    out << "            |         |         |         |           " << endl;
    out << "           " + td.e.at(5) + "    1   " + td.e.at(6) + "        " + td.e.at(7) + "    2   " + td.e.at(8) + "           " << endl;
    out << "            |" + td.tRes.at(1) + "|         |" + td.tRes.at(2) + "|           " << endl;
    out << "|" + td.v.at(6) + "|--" + td.e.at(9) + "--|" + td.v.at(7) + "|" + td.tVal.at(1) + "|" + td.v.at(8) + "|--" + td.e.at(10) + "--|" + td.v.at(9) + td.tVal.at(2) + "|" + td.v.at(10) + "|--" + td.e.at(11) + "--|" + td.v.at(11) + "| " << endl;
    out << "  |         |         |         |         |         | " << endl;
    out << " " + td.e.at(12) + "    3   " + td.e.at(13) + "        " + td.e.at(14) + "    4   " + td.e.at(15) + "        " + td.e.at(16) + "    5   " + td.e.at(17) + " " << endl;
    out << " |" + td.tRes.at(3) + "|         |" + td.tRes.at(4) + "|         |" + td.tRes.at(5) + "| " << endl;
    out << "|" + td.v.at(12) + "|" + td.tVal.at(3) + "|" + td.v.at(13) + "|--" + td.e.at(18) + "--|" + td.v.at(14) + "|" + td.tVal.at(4) + "|" + td.v.at(15) + "|--" + td.e.at(19) + "--|" + td.v.at(16) + "|" + td.tVal.at(5) + "|" + td.e.at(17) + "| " << endl;
    out << "  |         |         |         |         |         | " << endl;
    out << " " + td.e.at(20) + "        " + td.e.at(21) + "    6   " + td.e.at(22) + "        " + td.e.at(23) + "    7   " + td.e.at(24) + "        " + td.e.at(25) + " " << endl;
    out << "  |         |" + td.tRes.at(6) + "|         |" + td.tRes.at(7) + "|         | " << endl;
    out << "|" + td.v.at(18) + "|--" + td.e.at(26) + "--|" + td.v.at(19) + "|" + td.tVal.at(6) + "|" + td.v.at(20) + "|--" + td.e.at(27) + "--|" + td.v.at(21) + td.tVal.at(7) + "|" + td.v.at(22) + "|--" + td.e.at(28) + "--|" + td.v.at(23) + "| " << endl;
    out << " |         |         |         |         |         | " << endl;
    out << " " + td.e.at(29) + "    8   " + td.e.at(30) + "        " + td.e.at(31) + "    9   " + td.e.at(32) + "        " + td.e.at(33) + "   10   " + td.e.at(34) + " " << endl;
    out << " |" + td.tRes.at(8) + "|         |" + td.tRes.at(9) + "|         |" + td.tRes.at(10) + "| " << endl;
    out << "|" + td.v.at(24) + "|" + td.tVal.at(8) + "|" + td.v.at(25) + "|--" + td.e.at(35) + "--|" + td.v.at(26) + "|" + td.tVal.at(9) + "|" + td.v.at(27) + "|--" + td.e.at(36) + "--|" + td.v.at(28) + "|" + td.tVal.at(10) + "|" + td.e.at(29) + "| " << endl;
    out << "  |         |         |         |         |         | " << endl;
    out << " " + td.e.at(37) + "        " + td.e.at(38) + "   11   " + td.e.at(39) + "        " + td.e.at(40) + "   12   " + td.e.at(41) + "        " + td.e.at(42) + " " << endl;
    out << "  |         |" + td.tRes.at(11) + "|         |" + td.tRes.at(12) + "|         | " << endl;
    out << "|" + td.v.at(30) + "|--" + td.e.at(43) + "--|" + td.v.at(31) + "|" + td.tVal.at(11) + "|" + td.v.at(32) + "|--" + td.e.at(44) + "--|" + td.v.at(33) + td.tVal.at(12) + "|" + td.v.at(34) + "|--" + td.e.at(45) + "--|" + td.v.at(35) + "| " << endl;
    out << "  |         |         |         |         |         | " << endl;
    out << " " + td.e.at(46) + "   13   " + td.e.at(47) + "        " + td.e.at(48) + "   14   " + td.e.at(49) + "        " + td.e.at(50) + "   15   " + td.e.at(51) + " " << endl;
    out << " |" + td.tRes.at(13) + "|         |" + td.tRes.at(14) + "|         |" + td.tRes.at(15) + "| " << endl;
    out << "|" + td.v.at(36) + "|" + td.tVal.at(13) + "|" + td.v.at(37) + "|--" + td.e.at(52) + "--|" + td.v.at(38) + "|" + td.tVal.at(14) + "|" + td.v.at(39) + "|--" + td.e.at(53) + "--|" + td.v.at(40) + "|" + td.tVal.at(15) + "|" + td.e.at(41) + "| " << endl;
    out << "  |         |         |         |         |         | " << endl;
    out << " " + td.e.at(54) + "        " + td.e.at(55) + "   16   " + td.e.at(56) + "        " + td.e.at(57) + "   17   " + td.e.at(58) + "        " + td.e.at(59) + " " << endl;
    out << "  |         |" + td.tRes.at(16) + "|         |" + td.tRes.at(17) + "|         | " << endl;
    out << "|" + td.v.at(42) + "|--" + td.e.at(60) + "--|" + td.v.at(43) + "|" + td.tVal.at(16) + "|" + td.v.at(44) + "|--" + td.e.at(61) + "--|" + td.v.at(45) + td.tVal.at(17) + "|" + td.v.at(46) + "|--" + td.e.at(62) + "--|" + td.v.at(47) + "| " << endl;
    out << "            |         |         |         |           " << endl;
    out << "           " + td.e.at(63) + "        " + td.e.at(64) + "   18   " + td.e.at(65) + "        " + td.e.at(66) + "           " << endl;
    out << "            |         |" + td.tRes.at(18) + "|         |           " << endl;
    out << "          |" + td.v.at(48) + "|--" + td.e.at(67) + "--|" + td.v.at(49) + "|" + td.tVal.at(18) + "|" + td.v.at(50) + "|--" + td.e.at(68) + "--|" + td.v.at(51) + "|          " << endl;
    out << "                      |         |                     " << endl;
    out << "                     " + td.e.at(69) + "        " + td.e.at(70) + "                     " << endl;
    out << "                      |         |                     " << endl;
    out << "                    |" + td.v.at(52) + "|--" + td.e.at(71) + "--|" + td.v.at(53) + "| " << endl;
    return out;
}