#pragma once

#include <string>
#include <unordered_map>
#include <list>
#include <vector>
#include <utility>

using namespace std;

namespace basilar::assembler::assemblage {

class SymbolTableEntry {
public:
    string name;
    int address;

    bool is_public;
    bool is_external;

    list<int> references;
};

class SymbolTable {
public:
    void add_reference_to(string name, int address);
    int get_address(string name);
    
    bool define(string name, int address);
    bool define_external(string name);
    list<int> get_references(string name);
    void set_public(string name);

    vector<pair<string, int>> enumerate_external_references();
    vector<pair<string, int>> enumerate_public_symbols();
private:
    unordered_map<string, SymbolTableEntry> __table;
};

}