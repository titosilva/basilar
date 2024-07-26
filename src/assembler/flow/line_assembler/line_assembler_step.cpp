#include "line_assembler_step.hpp"
#include "../../tokens/spec_base.hpp"
#include "../../tokens/common_specs.hpp"

#include <fstream>
using namespace std;

using namespace basilar::tokens;

namespace basilar::assembler::flow {

void write_to_file(string file_dest, string content) {
    ofstream file(file_dest, ios::trunc);
    file << content;
    file.close();
}

optional<ParseContext> LineAssemblerStep::run(ParseContext ctx, LineSource*) {
    __line_handler.set_line_number(ctx.get_line_number());

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

    return nullopt;
}

void LineAssemblerStep::write_object_file() {
    write_to_file(__file_dest, __line_handler.build_object_code());
}

void LineAssemblerStep::write_debug_file() {
    write_to_file(__file_dest + ".debug", __line_handler.build_debug_code());
}

void LineAssemblerStep::check_consistency() {
    __line_handler.check_consistency();
}

} // namespace basilar::assembler::flow