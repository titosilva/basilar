#pragma once

#include <string>

using namespace std;

namespace basilar::objects {

class MemoryEntry {
public:
    int value;
    bool is_absolute;

    // Will not be used by the linker
    string debug_info;
    int line;
    int displacement;
};

}