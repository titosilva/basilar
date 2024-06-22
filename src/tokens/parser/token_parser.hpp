#pragma once

#include "token.hpp"
#include "parser_result.hpp"

#include <string>
#include <functional>

using namespace std;

namespace basilar::tokens::parser {

typedef function<ParseResult(ParseContext)> TokenParserFunction;

class TokenParser {
public:
    TokenParser(TokenParserFunction parse_token) : __parse_token(parse_token) {}
    ParseResult parse(ParseContext context) const;
    ParseResult parse(string input) const;

    ParseResult operator()(ParseContext context) const {
        return parse(context);
    }

    ParseResult operator()(string input) const {
        return parse(input);
    }
private:
    TokenParserFunction __parse_token;
};

TokenParser operator|(TokenParser lhs, TokenParser rhs);
TokenParser operator>>(TokenParser lhs, TokenParser rhs);
TokenParser operator<<(TokenParser lhs, TokenParser rhs);

} // namespace basilar::tokens::parser