#include "symbol_table.hpp"

// TODO: remove this
#include <iostream>
using namespace std;

namespace basilar::assembler::assemblage {

void SymbolTable::add_reference_to(string name, int address) {
    if (__table.find(name) == __table.end()) {
        __table[name] = SymbolTableEntry();
        __table[name].name = name;
        __table[name].address = -1;
    }

    __table[name].references.push_back(address);
}

bool SymbolTable::define(string name, int address) {
    if (__table.find(name) == __table.end()) {
        __table[name] = SymbolTableEntry();
        __table[name].name = name;
        __table[name].address = address;
        return true;
    }

    cout << "SymbolTable::define: " << name << " already defined" << endl;

    if (__table[name].address != -1) {
        return false;
    }

    __table[name].address = address;
    return true;
}

int SymbolTable::get_address(string name) {
    if (__table.find(name) == __table.end()) {
        return -1;
    }

    return __table[name].address;
}

list<int> SymbolTable::get_references(string name) {
    if (__table.find(name) == __table.end()) {
        return list<int>();
    }

    return __table[name].references;
}

} // namespace basilar::assembler::assemblage