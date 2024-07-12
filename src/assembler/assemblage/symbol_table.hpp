#pragma once

#include <string>
#include <unordered_map>
#include <list>

using namespace std;

namespace basilar::assembler::assemblage {

class SymbolTableEntry {
public:
    string name;
    int address;

    list<int> references;
};

class SymbolTable {
public:
    void add_reference_to(string name, int address);
    int get_address(string name);
    
    bool define(string name, int address);
    list<int> get_references(string name);
private:
    unordered_map<string, SymbolTableEntry> __table;
};

}