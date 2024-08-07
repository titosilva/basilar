#pragma once

#include <string>
#include <list>
using namespace std;

namespace basilar::objects {

class Symbol {
public:
    string name;
    int address;

    bool is_public;
    bool is_external;

    list<int> pending_references;

    int definition_line;
};

} // namespace basilar::objects