
// Mike Pierce
// main.cpp



#include "substifstream.h"
#include <iostream>
using namespace std;



// This implementation is incomplete.
// Also, it is not quite as clean and polished as it could be.



int main(int argc, char** argv) {

    // Error check argc
    if(argc < 4) {
        cerr << "Expected at least three arguments:" << endl
             << "  ./executable oldstring newstring file1 file2 ..." << endl;
        return 1;
    }

    // Behold, we begin!
    for(int files = 3; files < argc; ++files) {
        substifstream* sfs = new substifstream(argv[1], argv[2], argv[files]);
        if(sfs->fail()) {
            cerr << "Couldn't open file \"" << argv[files]<< "\"" << endl;
            return 1;
        }
        sfs->substitute();
        delete sfs;
    }

    return 0;
}




