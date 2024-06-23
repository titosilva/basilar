#pragma once

#include "token_parser.hpp"
#include "regex_parser.hpp"

namespace basilar::tokens::parser {
    const TokenParser Whitespace = RegexParser(R"(\s+)", "whitespace");
    const TokenParser Newline = RegexParser(R"(\n)", "newline");
    const TokenParser Number = RegexParser(R"(\d+)", "number");

    TokenParser JoinWithType(string type);
} // namespace basilar::tokens::parser