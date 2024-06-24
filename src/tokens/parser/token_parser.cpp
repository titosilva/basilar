#include "token_parser.hpp"
#include "utility_parsers.hpp"

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

TokenParser operator|(TokenParser lhs, string rhs) {
    return lhs | Literal(rhs);
}

TokenParser operator|(string lhs, TokenParser rhs) {
    return Literal(lhs) | rhs;
}

TokenParser operator>>(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = lhs.parse(ctx);
        if (!result.has_value()) {
            return nullopt;
        }

        return rhs.parse(result.value());
    });
}

TokenParser operator>>(TokenParser lhs, string rhs) {
    return lhs >> Literal(rhs);
}

TokenParser operator>>(string lhs, TokenParser rhs) {
    return Literal(lhs) >> rhs;
}

TokenParser operator<<(TokenParser lhs, TokenParser rhs) {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = lhs.parse(ctx);
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

TokenParser operator<<(TokenParser lhs, string rhs) {
    return lhs << Literal(rhs);
}

TokenParser operator<<(string lhs, TokenParser rhs) {
    return Literal(lhs) << rhs;
}

TokenParser operator+(TokenParser lhs, TokenParser rhs) {
    return lhs >> rhs;
}

TokenParser operator+(TokenParser lhs, string rhs) {
    return lhs + Literal(rhs);
}

TokenParser operator+(string lhs, TokenParser rhs) {
    return Literal(lhs) + rhs;
}

} // namespace basilar::tokens::parser