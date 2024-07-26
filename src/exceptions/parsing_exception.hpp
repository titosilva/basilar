#pragma once

#include "../src/assembler/tokens/parser/parse_context.hpp"
#include "../utils/logger.hpp"
using namespace basilar::assembler::tokens::parser;

#include <string>
#include <optional>
using namespace std;

namespace basilar::exceptions {

class ParsingException : public exception {
public:
    ParsingException(string message) : message(message) {}
    ParsingException(ParseContext ctx, string message) : message(message), ctx(ctx) {}
    string message;
    
    optional<ParseContext> ctx;

    char const* what() const noexcept override {
        return message.c_str();
    }

    string get_message() const {
        if (ctx.has_value()) {
            auto msg = "Syntax error at line " + to_string(ctx.value().get_line_number()) + ": " + message;
            
            if (ctx.value().get_original_input().size() > 0) {
                auto line = ctx.value().get_original_input();
                auto pos = line.size() - ctx.value().get_remaining_input().size();
                msg += "\n\t" + line + "\n\t" + string(pos, ' ') + "^";
            }

            for (auto token : ctx.value().get_tokens()) {
                LOG_DEBUG("Token: " + token.value);
            }

            LOG_DEBUG("Remaining input: " + ctx.value().get_remaining_input());
            LOG_DEBUG("Original input: " + ctx.value().get_original_input());

            return msg.c_str();
        }

        return message.c_str();
    }
};

} // namespace basilar::assembler::tokens::parser