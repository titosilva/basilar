#pragma once

#include "token.hpp"
#include "../../friend_test.hpp"
#include <optional>
#include <vector>

using namespace std;

namespace basilar::tokens::parser {

struct ParseContext {
public:
    ParseContext(string input) : __tokens(vector<Token>()), remaining_input(input) {}
    ParseContext(vector<Token> tokens, string remaining_input) : __tokens(tokens), remaining_input(remaining_input) {}

    vector<Token> get_tokens() { return vector<Token>(__tokens); }

    string remaining_input;

    AllowInternalTestFor(ParseContext);
private:
    vector<Token> __tokens;
};

typedef optional<ParseContext> ParseResult;

ParseResult fail_parse();
ParseResult succeed_parse(vector<Token> tokens, string remaining_input);
ParseResult succeed_parse(Token token, string remaining_input);
ParseResult succeed_parse(ParseContext ctx, string type, string value, string remaining_input);
ParseResult succeed_parse(string type, string value, string remaining_input);
ParseResult succeed_parse(vector<Token> tokens1, vector<Token> tokens2, string remaining_input);
ParseResult combine_results(ParseResult first, ParseResult second);

} // namespace basilar::tokens::parser

