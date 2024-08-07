#pragma once

#include "token_parser.hpp"
#include "../../../exceptions/exceptions.hpp"
using namespace basilar::exceptions;

#include <functional>

using namespace std;

namespace basilar::assembler::tokens::parser {

template <typename... ParamTypes>
using ParserMod = function<TokenParser(TokenParser, ParamTypes...)>;

const ParserMod<> Optional = [](TokenParser parser) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (result.has_value()) {
            return result;
        }

        return ctx;
    });
};

const ParserMod<> Ignored = [](TokenParser parser) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (!result.has_value()) {
            return ctx;
        }

        return ctx.with_remaining_input_from(result.value());
    });
};

const ParserMod<> Hidden = [](TokenParser parser) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (!result.has_value()) {
            return fail_parse();
        }

        return ctx.with_remaining_input_from(result.value());
    });
};

const ParserMod<string> Require = [](TokenParser parser, string message) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (!result.has_value()) {
            throw ParsingException(ctx, message);
        }

        return result;
    });
};

const ParserMod<string> Forbid = [](TokenParser parser, string message) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (result.has_value()) {
            throw ParsingException(ctx, message);
        }

        return ctx;
    });
};

const ParserMod<string> ForbidLex = [](TokenParser parser, string message) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx);

        if (result.has_value()) {
            throw lexycal_exception(ctx, message);
        }

        return ctx;
    });
};

const ParserMod<int> Repeat = [](TokenParser parser, int count) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        vector<Token> tokens;
        ParseContext current_ctx = ctx;

        for (int i = 0; i < count; i++) {
            ParseResult result = parser.parse(current_ctx);

            if (!result.has_value()) {
                return fail_parse();
            }

            current_ctx = result.value();
        }

        return current_ctx;
    });
};

const ParserMod<string> JoinWithType = [](TokenParser parser, string type) -> TokenParser {
    return TokenParser([=](ParseContext ctx) -> ParseResult {
        ParseResult result = parser.parse(ctx.reset_tokens());

        if (!result.has_value()) {
            return fail_parse();
        }

        auto tokens = result.value().get_tokens();
        string value = "";

        for (auto token : tokens) {
            value += token.value;
        }

        return ctx.add_token(type, value).with_remaining_input_from(result.value());
    });
};

} // namespace basilar::assembler::tokens::parser_modifiers
