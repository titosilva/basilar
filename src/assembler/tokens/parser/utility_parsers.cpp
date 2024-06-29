#include "utility_parsers.hpp"

namespace basilar::tokens::parser {

TokenParser Literal(string value) {
    return TokenParser([value](ParseContext ctx) -> ParseResult {
        if (ctx.get_remaining_input().find(value) != 0) {
            return fail_parse();
        }

        return ctx.add_token("literal", value).with_remaining_input(ctx.get_remaining_input().substr(value.size()));
    });
}

TokenParser JoinAs(string type) {
    return TokenParser([type](ParseContext ctx) -> ParseResult {
        auto tokens = ctx.get_tokens();
        string value = "";

        for (auto token : tokens) {
            value += token.value;
        }

        return ctx.reset_tokens().add_token(type, value);
    });
}

} // namespace basilar::tokens::parser