#pragma once

#include "symbol.hpp"

#include <map>

using namespace std;

namespace basilar::objects {

class SymbolTable {
public:
    bool define(string name, int address);
    bool define_external(string name);
    void set_public(string name);
    int refer(string name, int address);
    list<int> get_pending_references(string name);
private:
    map<string, Symbol> __symbols;
};

} // namespace basilar::objects