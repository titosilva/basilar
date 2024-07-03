#include "utility_parsers.hpp"

namespace basilar::assembler::tokens::parser {

TokenParser Literal(string value) {
    return TokenParser([value](ParseContext ctx) -> ParseResult {
        if (ctx.get_remaining_input().find(value) != 0) {
            return fail_parse();
        }

        return ctx.add_token("literal", value).with_remaining_input(ctx.get_remaining_input().substr(value.size()));
    });
}

TokenParser Note(string key, string value) {
    return TokenParser([key, value](ParseContext ctx) -> ParseResult {
        return ctx.add_annotation(key, value);
    });
}

} // namespace basilar::assembler::tokens::parser