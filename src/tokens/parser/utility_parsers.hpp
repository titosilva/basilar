#pragma once

#include "token_parser.hpp"
#include "regex_parser.hpp"

namespace basilar::tokens::parser {
    TokenParser Literal(string value);
    TokenParser JoinAs(string type);

    const TokenParser Whitespace = RegexParser(R"(\s+)", "whitespace");
    const TokenParser Newline = RegexParser(R"(\n)", "newline");
    const TokenParser Number = RegexParser(R"(\d+)", "number");
    const TokenParser End = TokenParser([](ParseContext ctx) -> ParseResult {
        if (ctx.remaining_input.empty() || ctx.remaining_input == "\n") {
            return succeed_parse(ctx, "end", ctx.remaining_input, "");
        }

        return fail_parse();
    });
} // namespace basilar::tokens::parser