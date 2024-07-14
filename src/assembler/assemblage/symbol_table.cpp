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

void SymbolTable::set_public(string name) {
    if (__table.find(name) == __table.end()) {
        __table[name] = SymbolTableEntry();
        __table[name].name = name;
        __table[name].address = -1;
    }

    __table[name].is_public = true;
}

bool SymbolTable::define_external(string name) {
    if (__table.find(name) == __table.end()) {
        __table[name] = SymbolTableEntry();
        __table[name].name = name;
        __table[name].address = 0;
        __table[name].is_external = true;
        return true;
    }

    if (__table[name].address != -1) {
        return false;
    }

    __table[name].address = 0;
    __table[name].is_external = true;
    return true;
}

list<int> SymbolTable::get_references(string name) {
    if (__table.find(name) == __table.end()) {
        return list<int>();
    }

    return __table[name].references;
}

vector<pair<string, int>> SymbolTable::enumerate_external_references() {
    vector<pair<string, int>> externals;

    for (auto [name, entry] : __table) {
        if (!entry.is_external) {
            continue;
        }

        for (auto ref : entry.references) {
            externals.push_back({name, ref});
        }
    }

    return externals;
}

vector<pair<string, int>> SymbolTable::enumerate_public_symbols() {
    vector<pair<string, int>> publics;

    for (auto [name, entry] : __table) {
        if (!entry.is_public) {
            continue;
        }

        publics.push_back({name, entry.address});
    }

    return publics;
}

} // namespace basilar::assembler::assemblage