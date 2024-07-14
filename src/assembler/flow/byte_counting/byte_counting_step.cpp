#include "byte_counting_step.hpp"
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

optional<ParseContext> ByteCountingStep::run(ParseContext ctx, LineSource*) {
    // TODO: support address expressions (eg. label + 1)
    // to be used with spaces
    
    if (ctx.has_annotation("instruction_call")) {
        if (ctx.has_annotation("has_label")) {
            auto token = ctx.get_token_with_type(ParserTypeOf(LabelDef));
            auto label = token->value;
            __byte_counter.handle_label(label);
        }

        auto instruction = ctx.get_annotation("instruction_call");
        auto operands = vector<string>();

        for (auto token : ctx.get_tokens_with_type(ParserTypeOf(Label))) {
            operands.push_back(token.value);
        }

        __byte_counter.handle_instruction(instruction, operands);
    }

    if (ctx.has_annotation("directive_call")) {
        auto directive = ctx.get_annotation("directive_call");

        string label;
        bool has_label = false;
        int idx = 1;
        if (ctx.has_annotation("has_label")) {
            has_label = true;
            idx++;
            auto token = ctx.get_token_with_type(ParserTypeOf(LabelDef));
            label = token->value;
        }

        if (directive != "extern") {
            if (has_label) {
                __byte_counter.handle_label(label);
            }

            auto operands = vector<string>();
            auto tokens = ctx.get_tokens();
            for (int i = idx; i < tokens.size(); i++) {
                operands.push_back(tokens[i].value);
            }
            
            __byte_counter.handle_directive(directive, operands);
        } else {
            __byte_counter.handle_directive(directive, vector<string>({label}));
        }
    }

    __byte_counter.next_line();

    // TODO: change to write only in the end
    write_to_file(__file_dest + ".debug", __byte_counter.to_human_readable_code());

    auto object_code = __byte_counter.to_object_code();
    write_to_file(__file_dest, object_code);
    return nullopt;

    // TODO: handle undefined references
}

} // namespace basilar::assembler::flow