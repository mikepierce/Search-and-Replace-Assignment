
// Mike Pierce
// usefulfstream.h



#ifndef USEFULSTREAM_H
#define USEFULSTREAM_H



#include <fstream>



class usefulfstream : public std::fstream {
    public:
        usefulfstream(const char*);
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
        std::streampos putter;
        std::streampos getter;
};



#endif /*USEFULSTREAM_H*/



