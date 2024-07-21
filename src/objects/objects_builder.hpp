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
    // Used during the assembly process
    void refer(string name, int displacement = 0);
    void define(string name);
    void define_external(string name);
    void set_public(string name);

    // Used during the linking process
    void add_reference(string name, int address);
    void add_definition(string name, int address);
    void rellocate(int base_address);
    void resolve();
    void link(ObjectsBuilder& other);

    // Used during both assembly and linking
    void absolute(int value);
    void relative(int value);

    int get_current_address();
    void write_debug_info(int address, string info);
    void append_debug_info(string info);

    void next_line();

    string build_debug_code();
    string build_object_code();

    void check_consistency();
private:
    Memory __memory;
    SymbolTable __symbol_table;
};

void debug_log_symbol_table(SymbolTable& symbol_table);

} // namespace basilar::objects
