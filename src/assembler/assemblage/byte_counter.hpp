#pragma once

#include "symbol_table.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

namespace basilar::assembler::assemblage {

class ByteCounter {
public:
    void handle_label(string label);
    void handle_instruction(string instruction, vector<string> operands);
    void handle_directive(string directive, vector<string> operands);
    void next_line();
    void add(string data);

    vector<int> get_machine_code();
    
    string to_human_readable_code();
    string to_object_code();
private:
    int __line = 0;
    // TODO: remove string obsession and use a struct or class
    vector<pair<string, int>> __program; // <code, source line>
    SymbolTable __symbol_table;
};

} // namespace basilar::assembler::assemblage