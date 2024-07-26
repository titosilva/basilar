#include "line_handler.hpp"
#include "opcodes.hpp"
#include "../../utils/logger.hpp"
#include "../../utils/string_utils.hpp"
#include "../../exceptions/lexycal_exception.hpp"
using namespace basilar::exceptions;

#include <utility>
#include <string>
using namespace std;

namespace basilar::assembler::assemblage {

pair<string, int> parse_operand(string operand) {
    if (!StringUtils::has(operand, "+")) {
        return {operand, 0};
    }

    auto parts = StringUtils::split(operand, "+");
    int displacement = 0;
    if (!StringUtils::try_parse_int(parts[1], &displacement)) {
        throw lexycal_exception("Bad integer " + parts[1]);
    }

    return {parts[0], displacement};
}

void LineHandler::handle_label(string operand) {
    LOG_DEBUG("Handling label definition: " + operand);
    __objects_builder.define(operand);
}

void LineHandler::handle_instruction(string label, string instruction, vector<string> operands) {
    if (label != "") {
        handle_label(label);
    }

    LOG_DEBUG("Handling instruction " + instruction + " with " + to_string(operands.size()) + " operands");

    __objects_builder.absolute(Opcodes::get(instruction));
    __objects_builder.append_debug_info(instruction);
    if (label != "") {
        __objects_builder.append_debug_info("def:" + label);
    }

    for (auto operand : operands) {
        auto [name, displacement] = parse_operand(operand);
        __objects_builder.refer(name, displacement);
        __objects_builder.append_debug_info(operand);
    }
}

void LineHandler::handle_directive(string label, string directive, vector<string> operands) {
    LOG_DEBUG("Handling directive " + directive + " with " + to_string(operands.size()) + " operands");

    if (directive == "extern") {
        LOG_DEBUG("Defining external: " + label);
        __objects_builder.define_external(label);

        return;
    }

    if (label != "") {
        handle_label(label);
    }

    if (directive == "const") {
        auto operand = operands[0];
        __objects_builder.absolute(StringUtils::parse_int(operand));

        if (label != "") {
            __objects_builder.append_debug_info("def:" + label);
        }
    }

    if (directive == "space") {
        uint size = operands.size() > 0 ? StringUtils::parse_int(operands[0]) : 1;

        __objects_builder.absolute(0);
        if (label != "") {
            __objects_builder.append_debug_info("def:" + label);
        }

        for (uint i = 1; i < size; i++) {
            __objects_builder.absolute(0);
        }
    }

    if (directive == "public") {
        auto operand = operands[0];
        __objects_builder.set_public(operand);
    }
}

string LineHandler::build_object_code() {
    return __objects_builder.build_object_code();
}

string LineHandler::build_debug_code() {
    return __objects_builder.build_debug_code();
}

void LineHandler::next_line() {
    __objects_builder.next_line();
}

void LineHandler::set_line_number(int line_number) {
    __objects_builder.set_line_number(line_number);
}

void LineHandler::check_consistency() {
    __objects_builder.check_consistency();
}

} // namespace basilar::assembler::assemblage