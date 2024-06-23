#include "utility_parsers.hpp"

namespace basilar::tokens::parser {
    
TokenParser JoinWithType(string type) {
    return TokenParser([type](ParseContext ctx) -> ParseResult {
        auto tokens = ctx.get_tokens();
        string value = "";

        for (auto token : tokens) {
            value += token.value;
        }

        auto newToken = Token(type, value);
        return succeed_parse(newToken, ctx.remaining_input);
    });
}

} // namespace basilar::tokens::parser