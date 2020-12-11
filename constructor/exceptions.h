#include <exception>
#include <string>

using namespace std;

//==========================================Exceptions==========================================================
class MissingArg : public exception {
    string arg;
    public:
    explicit MissingArg(string arg): arg(arg) {};
    const char* what() const noexcept {string t="ERROR: "+arg+ " missing seed argument"; return t.c_str();}
};

class UnrecognizedArg : public exception {
    string arg;
    public:
    explicit UnrecognizedArg(string arg): arg(arg) {};
    const char* what() const noexcept {string t="ERROR: unrecognized argument "+arg; return t.c_str();}
};

class MultiArg : public exception {
    string cmd_use;
    string cmd_abd;
    public:
    explicit MultiArg(string a, string b): cmd_use(a), cmd_abd(b) {};
    const char* what() const noexcept {string t = "ERROR: already specified " + cmd_use + ", can't also specify "+ cmd_abd; return t.c_str();}
};

class InvalidOpen : public exception {
    string path;
    public:
    explicit InvalidOpen(string path): path(path) {};
    const char* what() const noexcept {string t = "ERROR: Unable to open file " + path + "for board layout."; return t.c_str();}
};

class InvalidOpenDefault : public exception {
    public:
    const char* what() const noexcept {return "ERROR: Unable to open file layout.txt for default board layout.";}
};

class InvalidFormat : public exception {
    string file;
    public:
    explicit InvalidFormat(string file): file(file) {};
    const char* what() const noexcept {string t = "ERROR: "+ file +" has an invalid format."; return t.c_str();}
};

//==============================================================================================================