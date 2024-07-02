#pragma once

#include "token_parser.hpp"

#include <regex>

namespace basilar::assembler::tokens::parser {

class RegexParser : public TokenParser {
public:
    RegexParser(string re) : RegexParser(re, "r") {}
    RegexParser(string re, string type) : RegexParser(regex("^" + re), type) {}

    RegexParser(regex re, string type) : TokenParser([re, type](ParseContext ctx) -> ParseResult {
        smatch match;

        auto input = ctx.get_remaining_input();
        if (regex_search(input, match, re)) {
            return ctx
                .add_token(type, match.str())
                .with_remaining_input(match.suffix().str());
        }

        return fail_parse();
    }) {}
};

} // namespace basilar::assembler::tokens::parser