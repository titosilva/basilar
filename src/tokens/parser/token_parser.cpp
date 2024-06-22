#include "token_parser.hpp"

using namespace std;

namespace basilar::tokens::parser {

ParseResult TokenParser::parse(string input) const {
    return __parse_token(input);
}

ParseResult TokenParser::parse(ParseContext context) const {
    auto r = parse(context.remaining_input);

    if (!r.has_value()) {
        return fail_parse();
    }

    return succeed_parse(context.tokens, r.value().tokens, r.value().remaining_input);
}

TokenParser operator|(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](string input) -> ParseResult {
        ParseResult result = lhs.parse(input);

        if (result.has_value()) {
            return result;
        }

        return rhs.parse(input);
    });
}

TokenParser operator>>(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](string input) -> ParseResult {
        ParseResult result = lhs.parse(input);
        if (!result.has_value()) {
            return nullopt;
        }

        return rhs.parse(result.value());
    });
}

TokenParser operator<<(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](string input) -> ParseResult {
        ParseResult result = lhs.parse(input);
        if (!result.has_value()) {
            return nullopt;
        }

        ParseResult rightResult = rhs.parse(result.value());
        if (!rightResult.has_value()) {
            return result;
        }

        return rightResult;
    });
}

} // namespace basilar::tokens::parser