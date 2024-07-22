#pragma once

#include "token.hpp"
#include "../../../friend_test.hpp"
#include "../../../utils/string_utils.hpp"

#include <vector>
#include <map>
using namespace std;

namespace basilar::assembler::tokens::parser {

struct ParseContext {
public:
    ParseContext() : __remaining_input(""), __original_input(""), __line_number(0) {}
    ParseContext(string input, int line_number) : __remaining_input(input), __original_input(input), __line_number(line_number) {}
    
    ParseContext(vector<Token> tokens, string remaining_input, map<string, string> annotations, string original_input, int line_number) 
    : __remaining_input(remaining_input), __original_input(original_input), __line_number(line_number), __tokens(tokens), __annotations(annotations) {}

    vector<Token> get_tokens() const { return vector<Token>(__tokens); }

    optional<Token> get_token_with_type(string type) const {
        auto normalized = StringUtils::lower(type);

        for (auto token : get_tokens()) {
            if (StringUtils::lower(token.type) == normalized) {
                return token;
            }
        }

        return nullopt;
    }

    vector<Token> get_tokens_with_type(string type) const {
        auto normalized = StringUtils::lower(type);
        auto tokens = vector<Token>();

        for (auto token : get_tokens()) {
            if (StringUtils::lower(token.type) == normalized) {
                tokens.push_back(token);
            }
        }

        return tokens;
    }

    const string get_remaining_input() const { return string(__remaining_input); }
    map<string, string> get_annotations() const { return map<string, string>(__annotations); }
    bool has_annotation(string key) const { return __annotations.find(key) != __annotations.end(); }
    string get_annotation(string key) const { return __annotations.at(key); }

    ParseContext add_token(Token token) const {
        auto tokens = get_tokens();
        tokens.push_back(token);
        return ParseContext(tokens, get_remaining_input(), get_annotations(), __original_input, __line_number);
    }

    ParseContext add_token(string type, string value) const {
        return add_token(Token(type, value));
    }

    ParseContext with_remaining_input(string remaining_input) const {
        return ParseContext(get_tokens(), remaining_input, get_annotations(), __original_input, __line_number);
    }

    ParseContext with_remaining_input_from(ParseContext ctx) const {
        return with_remaining_input(ctx.get_remaining_input());
    }

    ParseContext with_tokens(vector<Token> tokens) const {
        return ParseContext(tokens, get_remaining_input(), get_annotations(), __original_input, __line_number);
    }

    ParseContext reset_tokens() const {
        return ParseContext(vector<Token>(), get_remaining_input(), get_annotations(), __original_input, __line_number);
    }

    ParseContext add_tokens(vector<Token> tokens) const {
        auto new_tokens = get_tokens();
        new_tokens.insert(new_tokens.end(), tokens.begin(), tokens.end());
        return ParseContext(new_tokens, get_remaining_input(), get_annotations(), __original_input, __line_number);
    }

    ParseContext add_tokens(ParseContext ctx) const {
        return add_tokens(ctx.get_tokens());
    }

    ParseContext add_annotation(string key, string value) const {
        auto annotations = get_annotations();
        annotations[key] = value;
        return ParseContext(get_tokens(), get_remaining_input(), annotations, __original_input, __line_number);
    }

    ParseContext add_annotation(string key) const {
        return add_annotation(key, "");
    }

    ParseContext with_annotations(map<string, string> annotations) const {
        return ParseContext(get_tokens(), get_remaining_input(), annotations, __original_input, __line_number);
    }

    ParseContext with_annotations_from(ParseContext ctx) const {
        return with_annotations(ctx.get_annotations());
    }

    string get_original_input() const { return string(__original_input); }
    int get_line_number() const { return __line_number; }

    AllowInternalTestFor(ParseContext);
private:
    string __remaining_input;
    string __original_input;
    int __line_number;
    vector<Token> __tokens;
    map<string, string> __annotations;
};

} // namespace basilar::assembler::tokens::parser

