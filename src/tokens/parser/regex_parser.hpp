#pragma once

#include "token_parser.hpp"

#include <regex>

namespace basilar::tokens::parser {

class RegexParser : public TokenParser {
public:
    RegexParser(string re, string type) : RegexParser(regex(re), type) {}

    RegexParser(regex re, string type) : TokenParser([re, type](string input) -> ParseResult {
        smatch match;

        if (regex_search(input, match, re)) {
            return succeed_parse(type, match.str(), match.suffix());
        }

        return fail_parse();
    }) {}
};

} // namespace basilar::tokens::parser