#include "token_parser.hpp"
#include <iostream>

using namespace std;

namespace basilar::tokens::parser {

ParseResult TokenParser::parse(ParseContext ctx) const {
    return __parse_token(ctx);
}

ParseResult TokenParser::parse(string input) const {
    return parse(ParseContext{input});
}

TokenParser operator|(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = lhs.parse(ctx);

        if (result.has_value()) {
            return result;
        }

        return rhs.parse(ctx);
    });
}

TokenParser operator>>(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = lhs.parse(ctx);
        if (!result.has_value()) {
            cout << "Failed to parse left side of >> operator\n" << endl;
            return nullopt;
        }

        cout << "Parsed left side of >> operator\n" << endl;
        return rhs.parse(result.value());
    });
}

TokenParser operator<<(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = lhs.parse(ctx);
        if (!result.has_value()) {
            return nullopt;
        }

        ParseResult rightResult = rhs.parse(result.value());
        if (!rightResult.has_value()) {
            cout << "Failed to parse right side of << operator\n" << endl;
            return result;
        }

        cout << "Parsed right side of << operator\n" << endl;
        return rightResult;
    });
}

} // namespace basilar::tokens::parser