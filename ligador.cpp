#include "src/linker/linker.hpp"
using namespace basilar::linker;

#include <filesystem>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " FILE_1 FILE_2" << endl;
        return 1;
    }

    Linker linker(argv[1], argv[2]);
    auto obj = linker.link();

    auto obj_code = obj.build_object_code();

    auto output_file_path = filesystem::path(argv[1]).replace_extension(".e").string();
    ofstream out(output_file_path);
    out << obj_code;
    out.close();

    #if DEBUG
    auto obj_debug = obj.build_debug_code();

    ofstream out_debug(output_file_path+".debug");
    out_debug << obj_debug;
    out_debug.close();
    #endif

    return 0;
}