#pragma once

#include "token.hpp"
#include "parser_result.hpp"

#include <string>
#include <functional>

using namespace std;

namespace basilar::tokens::parser {

typedef function<ParseResult(string)> TokenParserFunction;

class TokenParser {
public:
    TokenParser(TokenParserFunction parse_token) : __parse_token(parse_token) {}

    ParseResult parse(string input) const;
    ParseResult parse(ParseContext context) const;

private:
    TokenParserFunction __parse_token;
};

TokenParser operator|(TokenParser lhs, TokenParser rhs);
TokenParser operator>>(TokenParser lhs, TokenParser rhs);
TokenParser operator<<(TokenParser lhs, TokenParser rhs);

} // namespace basilar::tokens::parser