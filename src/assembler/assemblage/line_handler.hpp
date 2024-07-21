#pragma once

#include "../../objects/objects_builder.hpp"

using namespace basilar::objects;

namespace basilar::assembler::assemblage {

class LineHandler {
    public:
    void handle_label(string label);
    void handle_instruction(string label, string instruction, vector<string> operands);
    void handle_directive(string label, string directive, vector<string> operands);

    string build_object_code();
    string build_debug_code();

    void next_line();
    void check_consistency();
private:
    ObjectsBuilder __objects_builder;
};

} // namespace basilar::assembler::assemblage