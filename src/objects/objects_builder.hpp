#pragma once

#include "memory.hpp"
#include "memory_entry.hpp"
#include "symbol_table.hpp"
#include "symbol.hpp"

#include <map>
#include <string>
using namespace std;

namespace basilar::objects {

class ObjectsBuilder {
public:
    void refer(string name);
    void define(string name);
    void define_external(string name);
    void set_public(string name);
    void absolute(int value);

    string build_debug_file();
    string build_object_file();
private:
    Memory __memory;
    SymbolTable __symbol_table;
};

} // namespace basilar::objects
