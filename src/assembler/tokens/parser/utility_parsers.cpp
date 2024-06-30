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

} // namespace basilar::tokens::parser