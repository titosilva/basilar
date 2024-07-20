#pragma once

#include "../../objects/objects_builder.hpp"
using namespace basilar::objects;

#include <string>
using namespace std;

namespace basilar::linker {

class ObjectsReader {
public:
    ObjectsReader(string source) : __source(source) {}
    ObjectsBuilder read();
private:
    uint __current_index = 0;
    string __source;
    ObjectsBuilder __objects_builder;
};

} // namespace basilar::linker