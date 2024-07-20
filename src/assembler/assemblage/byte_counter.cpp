#include "byte_counter.hpp"
#include "assemblage_exception.hpp"
#include "../../utils/string_utils.hpp"
#include "opcodes.hpp"

// TODO: remove this
#include <iostream>
using namespace std;

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
    cout << "Defining label: " << operand << endl;
    auto label = operand.substr(0, operand.size() - 1);
    auto added = __symbol_table.define(label, __program.size());

    if (!added) {
        throw AssemblageException("Label " + label + " already defined");
    }
    cout << "Label: \"" << label << "\" defined at " << __program.size() << endl;

    auto refs = __symbol_table.get_references(label);
    cout << "Refs: " << refs.size() << endl;
    auto address = __symbol_table.get_address(label);

    for (auto ref : refs) {
        __program[ref].first += get_absolute_string(address);
    }
}

void ByteCounter::handle_instruction(string instruction, vector<string> operands) {
    cout << "Instruction: " << instruction << endl;
    auto instr_data = get_utility_string(instruction);
    auto opcode = Opcodes::get(instruction);
    instr_data += get_absolute_string(opcode);
    
    add(instr_data);

    for (auto operand : operands) {
        auto data = get_utility_string(operand);

        auto address = __symbol_table.get_address(operand);
        if (address != -1) {
            data += get_absolute_string(address);
        }

        add(data);
        
        __symbol_table.add_reference_to(operand, __program.size());
    }
}

void ByteCounter::handle_directive(string directive, vector<string> operands) {
    cout << "Directive: " << directive << endl;
    cout << "Operands: " << operands.size() << endl;

    // TODO: support hexadecimals

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

    if (directive == "public") {
        for (auto operand : operands) {
            __symbol_table.set_public(operand);
        }
    }

    if (directive == "extern") {
        for (auto operand : operands) {
            auto label = operand.substr(0, operand.size() - 1);
            cout << "Defining external: " << label << endl;
            __symbol_table.define_external(label);

            auto refs = __symbol_table.get_references(label);

            for (auto ref : refs) {
                __program[ref].first = get_utility_string(label) + get_absolute_string(0);
            }
        }
    }
}

void ByteCounter::next_line() {
    __line++;
}

string ByteCounter::to_human_readable_code() {
    string program = "";
    auto current_line = -1;

    auto address = 0;
    for (auto [data, line] : __program) {
        if (line != current_line) {
            program += "\n";
            current_line = line;
            program += "end " + to_string(address) + ". ";
        }

        address++;
        program += data + " ";
    }

    return program;
}

vector<int> ByteCounter::get_machine_code() {
    vector<int> machine_code;

    for (auto [data, line] : __program) {
        try {
            auto r = StringUtils::rereplace(data, regex{".*\\{(\\d+)\\}a.*"}, "$1");
            auto address = stoi(r);
            machine_code.push_back(address);
        } catch (...) {
            continue;
        }
    }

    return machine_code;
}

string ByteCounter::to_object_code() {
    string object_code;

    object_code += "USO\n";
    auto externals = __symbol_table.enumerate_external_references();
    for (auto [name, address] : externals) {
        object_code += name + "\t" + to_string(address) + "\n";
    }

    object_code += "DEF\n";
    auto publics = __symbol_table.enumerate_public_symbols();
    for (auto [name, address] : publics) {
        object_code += name + "\t" + to_string(address) + "\n";
    }

    object_code += "REAL\n\n";
    // TODO: add references to relative addresses in binary

    auto machine_code = get_machine_code();
    for (auto code : machine_code) {
        object_code += to_string(code) + " ";
    }

    return object_code;
}

} // namespace basilar::assembler::assemblage