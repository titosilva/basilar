#include "utility_parsers.hpp"

namespace basilar::tokens::parser {

TokenParser Literal(string value) {
    return TokenParser([value](ParseContext ctx) -> ParseResult {
        if (ctx.get_remaining_input().find(value) != 0) {
            return fail_parse();
        }

        auto new_token = Token("literal", value);
        auto new_tokens = ctx.get_tokens();
        new_tokens.push_back(new_token);
        return succeed_parse(new_tokens, ctx.get_remaining_input().substr(value.size()));
    });
}

TokenParser JoinAs(string type) {
    return TokenParser([type](ParseContext ctx) -> ParseResult {
        auto tokens = ctx.get_tokens();
        string value = "";

        for (auto token : tokens) {
            value += token.value;
        }

        auto newToken = Token(type, value);
        return succeed_parse(newToken, ctx.get_remaining_input());
    });
}

} // namespace basilar::tokens::parser