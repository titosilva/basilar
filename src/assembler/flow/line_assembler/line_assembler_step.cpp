#include "line_assembler_step.hpp"
#include "../../tokens/spec_base.hpp"
#include "../../tokens/common_specs.hpp"

#include <fstream>
#include <iostream>

using namespace std;

using namespace basilar::tokens;

namespace basilar::assembler::flow {

void write_to_file(string file_dest, string content) {
    ofstream file(file_dest, ios::trunc);
    file << content;
    file.close();
}

optional<ParseContext> LineAssemblerStep::run(ParseContext ctx, LineSource*) {
    // TODO: support address expressions (eg. label + 1)
    // to be used with spaces

    int idx = 0;
    string label;
    if (ctx.has_annotation("has_label")) {
        auto token = ctx.get_token_with_type(ParserTypeOf(LabelDef));
        // Remove the colon
        label = token->value.substr(0, token->value.size() - 1);
        idx++;
    }
    
    if (ctx.has_annotation("instruction_call")) {
        auto instruction = ctx.get_annotation("instruction_call");
        idx++;

        auto operands = vector<string>();
        auto tokens = ctx.get_tokens();
        for (uint i = idx; i < tokens.size(); i++) {
            operands.push_back(tokens[i].value);
        }

        __line_handler.handle_instruction(label, instruction, operands);
    }

    if (ctx.has_annotation("directive_call")) {
        auto directive = ctx.get_annotation("directive_call");
        idx++;

        auto operands = vector<string>();
        auto tokens = ctx.get_tokens();
        for (uint i = idx; i < tokens.size(); i++) {
            operands.push_back(tokens[i].value);
        }

        __line_handler.handle_directive(label, directive, operands);
    }

    __line_handler.next_line();

    return nullopt;
    // TODO: handle undefined references
}

void LineAssemblerStep::write_object_file() {
    write_to_file(__file_dest, __line_handler.build_object_code());
}

void LineAssemblerStep::write_debug_file() {
    write_to_file(__file_dest + ".debug", __line_handler.build_debug_code());
}

} // namespace basilar::assembler::flow