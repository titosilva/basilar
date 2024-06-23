#pragma once

#include "token_parser.hpp"
#include "parsing_exception.hpp"

#include <functional>

using namespace std;

namespace basilar::tokens::parser {

template <typename... ParamTypes>
using ParserMod = function<TokenParser(TokenParser, ParamTypes...)>;

const ParserMod<> Optional = [](TokenParser parser) -> TokenParser {
    return TokenParser([parser](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (result.has_value()) {
            return result;
        }

        return ctx;
    });
};

const ParserMod<> Ignore = [](TokenParser parser) -> TokenParser {
    return TokenParser([parser](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (!result.has_value()) {
            return ctx;
        }

        return succeed_parse(ctx.get_tokens(), result.value().remaining_input);
    });
};

const ParserMod<string> Required = [](TokenParser parser, string message) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (!result.has_value()) {
            throw ParsingException(message);
        }

        return result;
    });
};

} // namespace basilar::tokens::parser_modifiers
