
// Mike Pierce
// usefulfstream.cpp



#include "usefulfstream.h"



usefulfstream::usefulfstream(const char* c) 
    : std::fstream(c, std::fstream::in | std::fstream::out), putter(0), getter(0) {
        /*should figure out how to pass in the flags*/
}



// Output (putter) streampos related functions
std::streampos usefulfstream::tellp() {
    std::fstream::tellp(); 
    return putter;
}

void usefulfstream::seekp(std::streampos p) {
    std::fstream::seekp(p);
    putter = p;
}

void usefulfstream::jumpp(const int i) {
    putter = (int)putter + i;
}
void usefulfstream::jumpp() {
    putter = (int)putter + 1;
}

std::fstream& usefulfstream::put(char c) {
    std::streampos tmp = std::fstream::tellp();
    std::fstream::seekp(putter);
    std::fstream::put(c);
    jumpp();
    std::fstream::seekp(tmp);
    return *this;
}



// Input (getter) streampos related functions
std::streampos usefulfstream::tellg() {
    std::fstream::tellg(); 
    return getter;
}

void usefulfstream::seekg(std::streampos p) {
    std::fstream::seekg(p);
    getter = p;
}

void usefulfstream::jumpg(const int i) {
    getter = (int)getter + i;
}
void usefulfstream::jumpg() {
    getter = (int)getter + 1;
}

int usefulfstream::get() {
    std::fstream::seekg(getter);
    char c = std::fstream::get();
    jumpg();
    std::fstream::seekg(getter);
    return c;
}

std::fstream& usefulfstream::get(char& c) {
    std::fstream::seekg(getter);
    std::fstream::get(c);
    jumpg();
    std::fstream::seekg(getter);
    return *this;
}



