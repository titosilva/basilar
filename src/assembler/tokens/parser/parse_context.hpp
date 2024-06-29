#pragma once

#include "token.hpp"
#include "../../../friend_test.hpp"
#include <vector>

using namespace std;

namespace basilar::tokens::parser {

struct ParseContext {
public:
    ParseContext(string input) : __tokens(vector<Token>()), __remaining_input(input) {}
    ParseContext(vector<Token> tokens, string remaining_input) : __tokens(tokens), __remaining_input(remaining_input) {}

    vector<Token> get_tokens() const { return vector<Token>(__tokens); }
    const string get_remaining_input() const { return string(__remaining_input); }

    ParseContext add_token(Token token) const {
        auto tokens = get_tokens();
        tokens.push_back(token);
        return ParseContext(tokens, get_remaining_input());
    }

    ParseContext add_token(string type, string value) const {
        return add_token(Token(type, value));
    }

    ParseContext with_remaining_input(string remaining_input) const {
        return ParseContext(get_tokens(), remaining_input);
    }

    ParseContext with_remaining_input_from(ParseContext ctx) const {
        return with_remaining_input(ctx.get_remaining_input());
    }

    ParseContext with_tokens(vector<Token> tokens) const {
        return ParseContext(tokens, get_remaining_input());
    }

    ParseContext reset_tokens() const {
        return ParseContext(vector<Token>(), get_remaining_input());
    }

    ParseContext add_tokens(vector<Token> tokens) const {
        auto new_tokens = get_tokens();
        new_tokens.insert(new_tokens.end(), tokens.begin(), tokens.end());
        return ParseContext(new_tokens, get_remaining_input());
    }

    ParseContext add_tokens(ParseContext ctx) const {
        return add_tokens(ctx.get_tokens());
    }

    AllowInternalTestFor(ParseContext);
private:
    vector<Token> __tokens;
    string __remaining_input;
};

} // namespace basilar::tokens::parser

