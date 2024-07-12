#include "object_data.hpp"
#include "assemblage_exception.hpp"

namespace basilar::assembler::assemblage {

void ByteCounter::handle_label(string label) {
    auto added = __symbol_table.define(label, __program.size());

    if (!added) {
        throw AssemblageException("Label " + label + " already defined");
    }

    auto refs = __symbol_table.get_references(label);
    auto address = __symbol_table.get_address(label);

    for (auto ref : refs) {
        __program[ref].first = "{" + to_string(address) + "}a";
    }
}

void ByteCounter::handle_instruction(string instruction, vector<string> operands) {
    auto data = "{" + instruction + "}i";
    __program.push_back({data, __line});

    for (auto operand : operands) {
        auto address = __symbol_table.get_address(operand);
        if (address == -1) {
            __symbol_table.add_reference_to(operand, __program.size());
            __program.push_back({"{" + label +"}r", __line});
        } else {
            __program.push_back({"{" + to_string(address) + "}a", __line});
        }
    }

    __line++;
}

void ByteCounter::handle_directive(string directive, vector<string> operands) {
    // TODO: Implement directive handling
    __line++;
}

} // namespace basilar::assembler::assemblage