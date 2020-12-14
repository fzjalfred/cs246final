#include "arginit.h"

int readInt(int a, int b) {
    cin.exceptions(ios::eofbit|ios::failbit);
    int m;
    
    while (true) {
        try {
            cin>>m;
            if (m<a || m> b) throw out_of_range("Error: integer out of range");
            return m;
        } catch (out_of_range &r) {
            cout<<r.what()<<endl;
        }
        catch (exception& e) {
            cin.clear();
            string a;
            getline(cin,a);
            cout<<"Error: isn't a valid integer"<<endl;
        }
    }
}

void to_lowercase(string &who) {
    for_each(who.begin(), who.end(), [](auto &i){
        if ('A'<= i && i<= 'Z')
        i += ('a'-'A');
    });
}

void readPlayer(int& pos) {
    pos = -1;
    while (pos == -1)
    {
        string who;
        cin >> who;
        for (int i = 0; i < NUM_PLAYER; i++)
        {
            to_lowercase(who);
            if (who.compare(getPlayerColour(i)) == 0)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
            cout << "Invalid colour" << endl;
        else
            break;
    }
}

void readResource(int& pos) {
    pos = -1;
    while (pos == -1)
    {
        string who;
        cin >> who;
        to_lowercase(who);
        if (who == "brick") pos = 0;
        else if (who == "energy") pos = 1;
        else if (who == "glass") pos = 2;
        else if (who == "heat") pos = 3;
        else if (who == "wifi") pos = 4;
        if (pos == -1)
            cout << "Invalid item." << endl;
        else
            break;
    }
}


string getPlayerColour(int i) {
    Colour c = static_cast<Colour>(i);
    switch (c) {
        case Colour::Blue:
        return "Blue";
        case Colour::Orange:
        return "Orange";
        case Colour::Red:
        return "Red";
        case Colour::Yellow:
        return "Yellow";
    } 
    return "";
}

string getResource(int i) {
    Resource c = static_cast<Resource>(i);
    switch (c) {
        case Resource::BRICK:
        return "BRICK";
        case Resource::ENERGY:
        return "ENERGY";
        case Resource::GLASS:
        return "GLASS";
        case Resource::HEAT:
        return "HEAT";
         case Resource::WIFI:
        return "WIFI";
        case Resource::PARK:
        return "PARK";
    } 
    return "";
}

void layoutInit(string& out, vector<pair<int, int>>& layout, string& file) {
    try {
        vector<pair<int, int>> tmp;
        int counter = 0;
        istringstream iss(out);
        int currFirst;
        int currSecond;
        while ( iss >> currFirst && iss >> currSecond) {
            tmp.emplace_back(currFirst, currSecond);
            counter ++;
        } 
        if ( counter < 19) {
            throw exception();
        }
        layout = tmp;
    } catch (exception &e) {
        throw InvalidFormat(file);
    }
}

void cmdLoadInit(std::ifstream& fin,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file) {
    while (!fin.eof()) {
        string s;
        string out;
        getline(fin, s);
        try {
            //curTurn
            istringstream iss1{s};
            int tmp1;
            iss1 >> tmp1;
            if (tmp1 < 0){
                throw;
            }
            curTurn = tmp1;
            //curData
            for (int i = 0; i < NUM_PLAYER; i++)
            {
                getline(fin, s);
                curData.emplace_back(s);
            }
            //board
            getline(fin, out);
            layoutInit(out, layout, file);
            //geese
            getline(fin, s);
            int tmp2 = stoi(s);
            if (tmp2 < 0 ) {
                throw;
            }
            geese = tmp2;
        } catch (exception& any) {
            throw InvalidFormat(file);
        }
        break;
    }
}

void argsInitial(int len, char**& args,  vector<pair<int, int>>& layout, int& curTurn, vector<string>& curData, int& geese, string& file, bool& isload) {
    int i;
    unsigned seed = 0;
    string out;
    try
    {
        string preCmd = ""; // used in MultiArg exception

        // default cmd
        if ( len == 1) {
            ifstream fin("layout.txt", ios::in); // open file
            if (fin.is_open())
            {
                getline(fin, out);
                file = "layout.txt";
                layoutInit(out, layout, file); //transfer string of layout into numbers we use for next board intialization.
            }
            else
            {
                InvalidOpenDefault e;
                throw e;
            }
        }

        // user give arguments
        for (i = 1; i < len; i++)
        {
            string s = args[i];
            if (s == "-seed") 
            {
                if (++i == len){
                    throw MissingArg(s, "seed");
                }
                seed = stoi(args[i]);
            }
            else if (s == "-load")
            {   
                
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                cout<<"run -board3"<<endl;
                if (++i == len){
                    throw MissingArg(s, "filename");
                }
                
                ifstream fin(args[i], ios::in); // open file
                if (fin.is_open()) {
                    file = args[i];
                    cmdLoadInit(fin, layout, curTurn, curData, geese, file); // intiliaze everything with cmd -load
                } else 
                {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }
                isload = 1;
            }
            else if (s == "-board")
            {   
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                if (++i == len)
                {
                throw MissingArg(s, "filename");
                }
                ifstream fin(args[i], ios::in); // open file
                if (fin.is_open()) {
                    getline(fin, out);
                    file = args[i];
                    layoutInit(out, layout, file); //transfer string of layout into numbers we use for next board intialization.
                } else {
                    string err = args[i];
                    InvalidOpen e(err);
                    throw e;
                }
            }
            else if (s == "-random-board")
            {   
                if (preCmd == "") {
                    preCmd = s;
                } else throw MultiArg(preCmd, s);
                default_random_engine rng{seed};        // random generator
                vector<int> resources = {4,4,4,3,3,3,0,0,0,0,1,1,1,1,2,2,2,2,5};
                vector<int> tiles = {2, 3+rand()%4, 3+rand()%4, 8+rand()%4, 8+rand()%4, 12};
                for ( int i=0; i<13; i++) {
                    tiles.emplace_back(2+rand()%11);
                }
                shuffle(resources.begin(), resources.end(), rng );
                shuffle(tiles.begin(), tiles.end(), rng);
                for(int i=0; i<=18; i++) {
                    layout.emplace_back(resources.at(i), tiles.at(i));
                }  
            }
            else
            {
                UnrecognizedArg e(s);
                throw e;
            }
        }
    }
    catch (invalid_argument &e) {
        cout<<"FLAG 3"<<endl;
        InvalidFormat a(file);
        throw a;
    }
    catch (exception &e)
    {   
        cout<<"FLAG 4"<<endl;
        cout<<e.what()<<endl;
        throw;
    }
} 


