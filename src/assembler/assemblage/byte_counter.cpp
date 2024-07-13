#include "byte_counter.hpp"
#include "assemblage_exception.hpp"
#include "../utils/string_utils.hpp"

#include <iostream>

using namespace std;

using namespace basilar::utils;

namespace basilar::assembler::assemblage {

string get_utility_string(string utility) {
    return "(" + utility + ")";
}

string get_absolute_string(int address) {
    return "{" + to_string(address) + "}a";
}

void ByteCounter::add(string data) {
    __program.push_back({data, __line});
}

void ByteCounter::handle_label(string operand) {
    auto label = operand.substr(0, operand.size() - 1);
    auto added = __symbol_table.define(label, __program.size());

    if (!added) {
        throw AssemblageException("Label " + label + " already defined");
    }
    cout << "Label: " << label << " defined at " << __program.size() << endl;

    auto refs = __symbol_table.get_references(label);
    cout << "Refs: " << refs.size() << endl;
    auto address = __symbol_table.get_address(label);

    for (auto ref : refs) {
        __program[ref].first += get_absolute_string(address);
    }
}

void ByteCounter::handle_instruction(string instruction, vector<string> operands) {
    add(get_utility_string(instruction));

    for (auto operand : operands) {
        auto address = __symbol_table.get_address(operand);
        auto data = get_utility_string(operand);

        if (address == -1) {
            __symbol_table.add_reference_to(operand, __program.size());
            cout << "Undefined reference: " << operand << " at " << __program.size() << endl;
        } else {
            data += get_absolute_string(address);
        }

        add(data);
    }
}

void ByteCounter::handle_directive(string directive, vector<string> operands) {
    cout << "Directive: " << directive << endl;
    cout << "Operands: " << operands.size() << endl;
    if (directive == "const") {
        for (auto operand : operands) {
            add(get_absolute_string(stoi(operand)));
        }
    }

    if (directive == "space") {
        if (operands.size() != 1) {
            add(get_absolute_string(0));
        } else {
            auto size = stoi(operands[0]);
            for (auto i = 0; i < size; i++) {
                add(get_absolute_string(0));
            }
        }
    }
}

void ByteCounter::next_line() {
    __line++;
}

string ByteCounter::get_human_readable_program() {
    string program = "";
    auto current_line = 0;

    for (auto [data, line] : __program) {
        if (line != current_line) {
            program += "\n";
            current_line = line;
        }

        program += data + " ";
    }

    return program;
}

vector<int> ByteCounter::get_machine_code() {
    vector<int> machine_code;

    for (auto [data, line] : __program) {
        machine_code.push_back(stoi(data));
    }

    return machine_code;
}

} // namespace basilar::assembler::assemblage