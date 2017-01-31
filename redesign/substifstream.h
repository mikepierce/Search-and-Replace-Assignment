
// Mike Pierce
// substifstream.h



#ifndef SUBSTIFSTREAM_H
#define SUBSTIFSTREAM_H

#include <fstream>
#include <iostream>
#include <unistd.h>
#include "TrackingDeque.hpp"



class substifstream : public std::fstream {
    public:
        substifstream(const char*, const char*, const char*);
        void substitute();
        ~substifstream();
        std::streampos tellp();
        void seekp(std::streampos);
        void jumpp(const int);
        void jumpp();
        std::fstream& put(char);
        std::streampos tellg();
        void seekg(std::streampos);
        void jumpg(const int);
        void jumpg();
        int get();
        std::fstream& get(char& c);
    private:
        TrackingDeque<char> deck;
        const char* file;
        enum state_t : char {normal, matching, replacing} state;
        const char* duncan;
        unsigned short dunsize;
        unsigned short dunpos; // state==matching IFF dunpos!=0
        const char* macbeth;
        unsigned short macsize;
        unsigned short macpos;
        std::streampos putter;
        std::streampos getter;
        bool deckdumpmode;
        void foundone(char);
        void foundoneattheend();
        void didntfindone(char);
};



#endif /*SUBSTIFSTREAM_H*/




