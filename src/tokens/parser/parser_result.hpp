#pragma once

#include "token.hpp"
#include <optional>
#include <vector>

using namespace std;

namespace basilar::tokens::parser {

struct ParseContext {
public:
    ParseContext(vector<Token> tokens, string remaining_input) : tokens(tokens), remaining_input(remaining_input) {}
    vector<Token> tokens;
    string remaining_input;
};

typedef optional<ParseContext> ParseResult;

ParseResult fail_parse();
ParseResult succeed_parse(vector<Token> tokens, string remaining_input);
ParseResult succeed_parse(Token token, string remaining_input);
ParseResult succeed_parse(string type, string value, string remaining_input);
ParseResult succeed_parse(vector<Token> tokens1, vector<Token> tokens2, string remaining_input);
ParseResult combine_results(ParseResult first, ParseResult second);

} // namespace basilar::tokens::parser

