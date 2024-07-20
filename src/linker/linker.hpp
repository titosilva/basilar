#pragma once

#include "../objects/objects_builder.hpp"
using namespace basilar::objects;

#include <string>
using namespace std;

namespace basilar::linker {

class Linker {
public:
    Linker(string file1, string file2) : __file1(file1), __file2(file2) {}
    ObjectsBuilder link();
private:
    string __file1;
    string __file2;
};

} // namespace basilar::linker