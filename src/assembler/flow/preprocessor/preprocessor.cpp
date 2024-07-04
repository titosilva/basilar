#include "preprocessor.hpp"
#include "../../tokens/common_specs.hpp"
#include "../../utils/string_utils.hpp"

// TODO: Remove this
#include <iostream>
using namespace std;

using namespace basilar::tokens;
using namespace basilar::utils;

namespace basilar::assembler::flow {

optional<ParseContext> Preprocessor::run(ParseContext ctx, LineSource* source) {
    // TODO: throw semantic error on each error
    if (ctx.has_annotation("is_equ")) {
        return __handle_equ(ctx, source);
    }

    if (ctx.has_annotation("is_if")) {
        return __handle_if(ctx, source);
    }

    if (ctx.get_tokens().size() > 0) {
        throw runtime_error("Unexpected tokens in preprocessor");
    }

    auto line = ctx.get_remaining_input();
    if (line.length() == 0) {
        source->next_line();
        return nullopt;
    }

    return __try_replace_tokens(ctx, source);
}

optional<ParseContext> Preprocessor::__handle_equ(ParseContext ctx, LineSource*) {
    auto labeldef = ctx.get_token_with_type(ParserTypeOf(LabelDef));
    auto value = ctx.get_token_with_type("notwhitespace");

    cout << "Label: " << labeldef.has_value() << " Value: " << value.has_value() << endl;

    if (!labeldef.has_value() || !value.has_value()) {
        throw runtime_error("Expected label definition and value");
    }

    __definitions[labeldef.value().value] = value.value().value;
    return nullopt;
}

optional<ParseContext> Preprocessor::__handle_if(ParseContext ctx, LineSource* source) {
    int conditional_value = 0;
    auto label_name = ctx.get_token_with_type(ParserTypeOf(Label));
    auto number = ctx.get_token_with_type(ParserTypeOf(Integer));

    if (label_name.has_value()) {
        auto def = __definitions.find(label_name.value().value);
        if (def == __definitions.end()) {
            throw runtime_error("Undefined label in conditional");
        }

        try {
            conditional_value = stoi(def->second);
        } catch (...) {
            conditional_value = def->second.length() > 0 ? 1 : 0;
        }
    } else if(number.has_value()) {
        conditional_value = stoi(number.value().value);
    } else {
        throw runtime_error("Expected label or number in conditional");
    }

    if (conditional_value == 0) {
        source->next_line();
        return nullopt;
    }

    return ctx;
}

optional<ParseContext> Preprocessor::__try_replace_tokens(ParseContext ctx, LineSource*) {
    string new_line;
    auto line = ctx.get_remaining_input();

    while (line.length() > 0) {
        auto next_space = line.find_first_of(" \t");
        auto token = line.substr(0, next_space);

        if (next_space == string::npos) {
            new_line += line;
            break;
        }

        if (token.length() == 0) {
            line = line.substr(next_space + 1);
            continue;
        }

        if (__definitions.find(token) != __definitions.end()) {
            auto value = __definitions[token];
            new_line += value;
        } else {
            new_line += token;
        }

        line = line.substr(next_space + 1);
        new_line += line.length() > 0 ? " " : "";
    }

    return ctx.with_remaining_input(new_line);
}

}  // namespace basilar::assembler::flow