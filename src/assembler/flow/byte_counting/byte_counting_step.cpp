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
    auto annotations = ctx.get_annotations();
    for (auto annotation : annotations) {
        cout << "Annotation: " << annotation.first << " Value: " << annotation.second << endl;
    }
    
    if (ctx.has_annotation("has_label")) {
        auto token = ctx.get_token_with_type(ParserTypeOf(LabelDef));
        auto label = token->value;
        __byte_counter.handle_label(label);
    }

    if (ctx.has_annotation("instruction_call")) {
        auto instruction = ctx.get_annotation("instruction_call");
        auto operands = vector<string>();

        for (auto token : ctx.get_tokens_with_type(ParserTypeOf(Label))) {
            operands.push_back(token.value);
        }

        __byte_counter.handle_instruction(instruction, operands);
    }

    if (ctx.has_annotation("directive_call")) {
        auto directive = ctx.get_annotation("directive_call");
        auto operands = vector<string>();

        int idx = 1;
        if (ctx.has_annotation("has_label")) {
            idx++;
        }

        auto tokens = ctx.get_tokens();
        for (int i = idx; i < tokens.size(); i++) {
            operands.push_back(tokens[i].value);
        }

        __byte_counter.handle_directive(directive, operands);
    }

    __byte_counter.next_line();

    write_to_file(__file_dest, __byte_counter.get_human_readable_program());
    return nullopt;

    // TODO: handle undefined references
}

} // namespace basilar::assembler::flow