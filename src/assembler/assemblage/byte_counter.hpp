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

    string get_human_readable_program();
    vector<int> get_machine_code();
private:
    int __line = 0;
    vector<pair(string, int)> __program; // <code, source line>
    SymbolTable __symbol_table;
};

} // namespace basilar::assembler::assemblage