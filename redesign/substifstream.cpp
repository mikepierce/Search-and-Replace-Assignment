
// Mike Pierce
// substifstream.cpp



#include "substifstream.h"



substifstream::substifstream(const char* d, const char* m, const char* f)
: std::fstream(f, std::fstream::in | std::fstream::out), file(f), //...
  state(normal), duncan(d), dunpos(0), macbeth(m), macpos(0), //...
  putter(0), getter(0), deckdumpmode(false) {
    dunsize = macsize = 0;
    while(duncan[dunsize])
        ++dunsize;
    while(macbeth[macsize])
        ++macsize;
}

void substifstream::substitute() {
    char ch;
    while(get(ch).good() || (!deck.empty() /*&& deck.front() != -1*/)) {
        // std::cerr << "ch= " << ch
        //           << " tellp()= " << tellp()
        //           << " tellg()= " << tellg()
        //           << " dunpos= " << dunpos
        //           << " dunsize= " << dunsize
        //           << " good()= " << good()
        //           << " deck.front()= " << deck.front()
        //           << " deck.size()= " << deck.size() << std::endl;
        if(!dunpos/*we are not matching*/) {
            if(ch == duncan[dunpos]) {
                ++dunpos;
            }
            else {/*it is just a character*/
                put(ch);
            }
            continue;
        }
        else {/*we are currently matching*/
            if(dunpos == dunsize) {
                foundone(ch);
            }
            else if(ch == duncan[dunpos]/*its a match*/) {
                ++dunpos;
            }
            else {/*its only a partial match ... bummer*/
                didntfindone(ch);
            }
        }
    }
    if(dunsize < macsize && ch != '\0') // THIS IS NOT CLEAN
        put(ch);
    if(dunpos == dunsize)
        foundoneattheend();

}

void substifstream::foundone(char c) {
    unsigned i;
    for(i = 0; duncan[i] && macbeth[i]; ++i)
        put(macbeth[i]);
    if(macbeth[i]) while(macbeth[i])
        put(macbeth[i++]);
    if(c == duncan[0])
        dunpos = 1;
    else {
        put(c);
        dunpos = 0;
    }
}

void substifstream::foundoneattheend() {
    unsigned i;
    for(i = 0; duncan[i] && macbeth[i]; ++i)
        put(macbeth[i]);
    if(macbeth[i]) while(macbeth[i])
        put(macbeth[i++]);
    dunpos = 0;
}

void substifstream::didntfindone(char c) {
    put(duncan[0]);
    unsigned i;
    unsigned short dunmax = dunpos;
    --dunpos;
    for(i = 1; i < dunmax ; ++i, --dunpos) {
        if((duncan[i] == duncan[0]) && (c == duncan[dunpos])) {
            dunpos++;
            return;
        }
        else
            put(duncan[i]);
    }
    if(c == duncan[0]) {
        ++dunpos;
        return;
    }
    put(c);
}

substifstream::~substifstream() {
    std::fstream::close();
    if(tellp() < tellg())
        truncate(file, (int)tellp());
}


// Output (putter) streampos related functions
std::streampos substifstream::tellp() {
    std::fstream::tellp();
    return putter;
}

void substifstream::seekp(std::streampos p) {
    std::fstream::seekp(p);
    putter = p;
}

void substifstream::jumpp(const int i) {
    putter = (int)putter + i;
}
void substifstream::jumpp() {
    putter = (int)putter + 1;
}

std::fstream& substifstream::put(char c) {
    std::streampos tmp = std::fstream::tellp();
    bool mynotgoodflag = false;
    std::fstream::seekp(putter);
    if(tellg() <= tellp()) {
        std::fstream::seekg(getter);
        int tempura = std::fstream::get();
        if(good()) {
            jumpg();
            deck.push_back((char)tempura);
        }
        else
            mynotgoodflag = true;
    }
    clear();
    std::fstream::seekp(putter);
    std::fstream::put(c);
    if(mynotgoodflag)
        std::fstream::setstate(std::fstream::goodbit);
    jumpp();
    std::fstream::seekp(tmp);
    return *this;
}



// Input (getter) streampos related functions
std::streampos substifstream::tellg() {
    std::fstream::tellg();
    return getter;
}

void substifstream::seekg(std::streampos p) {
    std::fstream::seekg(p);
    getter = p;
}

void substifstream::jumpg(const int i) {
    getter = (int)getter + i;
}
void substifstream::jumpg() {
    getter = (int)getter + 1;
}

int substifstream::get() {
    std::streampos tmp = std::fstream::tellg();
    std::fstream::seekg(getter);
    int tempura = std::fstream::get();
    if(good()) {
        deck.push_back((char)tempura);
        jumpg();
    }
    int c = deck.front();
    if(!deck.empty())
        deck.pop_front();
    std::fstream::seekg(tmp);
    return c;
}

std::fstream& substifstream::get(char& c) {
    std::streampos tmp = std::fstream::tellg();
    std::fstream::seekg(getter);
    int tempura = std::fstream::get();
    if(good()) {
        deck.push_back((char)tempura);
        jumpg();
    }
    c = deck.front();
    if(!deck.empty())
        deck.pop_front();
    std::fstream::seekg(tmp);
    return *this;
}



