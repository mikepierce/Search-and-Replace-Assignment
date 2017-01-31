
// Mike Pierce
// main.cpp



#include "usefulfstream.h"
#include "TrackingDeque.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;



bool foundone(char*&, usefulfstream&);



int main(int argc, char** argv) {

    // Error check argc
    if(argc != 4) {
        cerr << "Expected exactly three arguments:" << endl
             << "  ./executable oldstring newstring filename" << endl;
        return 1;
    }

    // Declare some stuff
    char*& duncan = argv[1];
    char*& macbeth = argv[2];
    char*& file = argv[3];
    usefulfstream inverness(file);
    if(inverness.fail()) {
        cerr << "Couldn't open file \"" << argv[3] << "\"" << endl;
        return 1;
    }
    TrackingDeque<char> deck;

    // Behold, we begin!
    while(inverness.good()) {
        // If we need to depose the following characters ...
        if(foundone(duncan, inverness)) {
            unsigned i;
            // Run through while we have both duncan and macbeth ...
            for(i = 0; duncan[i] && macbeth[i]; ++i) {
                deck.push_back(macbeth[i]); 
                inverness.jumpg(); // manually ++g
                inverness.put(deck.front()); // auto ++p
                deck.pop_front();
            }
            // ... and if we still have some macbeth ...
            if(macbeth[i]) while(macbeth[i])
                deck.push_back(macbeth[i++]);
            // ... else if we still have some duncan.
            else while(duncan[i++])
                inverness.jumpg();
        }
        // ... else if it's just a normal character.
        else {
            deck.push_back(inverness.get()); // auto ++g 
            inverness.put(deck.front()); // auto ++p 
            if(inverness.good())
                deck.pop_front();
        }
    }
    inverness.clear();
    // If we've still got some characters in the deck to dump ...
    if(!deck.empty() && deck.front() != -1) {
        inverness.jumpp(-1);
        while(!deck.empty() && deck.front() != -1) {
            inverness.put(deck.front());
            deck.pop_front();
        }
    }
    // ... else if we've gotta truncate the end of the file.
    unsigned truncatesize = 0;
    bool truncateflag = false;
    if(inverness.tellp() < inverness.tellg()) {
        truncateflag = true;
        truncatesize = (int)inverness.tellp() - 1;
    }
    
    // Close the file, and truncate it if necessary
    inverness.close();
    if(truncateflag)
        truncate(file, truncatesize);
    


    return 0;
}



// Return true if the current tellg() position in castle
//   is the first character of a sequence of characters matching king
bool foundone(char*& king, usefulfstream& castle) {
    streampos here = castle.tellg();
    bool wefoundtheking = true;
    for(char* i = king; *i; ++i)
        if(*i != castle.get()) {
            wefoundtheking = false;
            break;
        }
    castle.seekg(here);
    return wefoundtheking;
}



