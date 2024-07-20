#pragma once

#include "symbol.hpp"

#include <map>
#include <string>
#include <list>
using namespace std;

namespace basilar::objects {

class SymbolTable {
public:
    bool define(string name, int address);
    bool define_external(string name);
    void define_public(string name);
    int refer(string name, int address);
    list<int> get_pending_references(string name);
    map<string, Symbol> get_table();
private:
    map<string, Symbol> __symbols;

    Symbol __default_symbol(string name);
};

} // namespace basilar::objects