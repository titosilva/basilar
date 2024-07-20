#include "src/linker/linker.hpp"
using namespace basilar::linker;

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <file1> <file2> <outfile>" << endl;
        return 1;
    }

    Linker linker(argv[1], argv[2]);
    auto obj = linker.link();

    auto obj_code = obj.build_object_code();

    ofstream out(argv[3]);
    out << obj_code;
    out.close();

    #if DEBUG
    auto obj_debug = obj.build_debug_code();

    ofstream out_debug(string(argv[3])+".debug");
    out_debug << obj_debug;
    out_debug.close();
    #endif

    return 0;
}