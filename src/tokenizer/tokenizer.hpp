#pragma once

#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <string>
#include <vector>

#include "../friend_test.hpp"
#include "formatter.hpp"
#include "../tokens/parser/parser.hpp"

using namespace basilar::tokens::parser;

namespace basilar::tokenizer {

class Tokenizer {
   public:

    Tokenizer(std::string file_content) : __file_content(file_content), __current_line_number(0), __current_index(0) { }

    void add_line_formatter(Formatter formatter);
    void with_parser(TokenParser parser);

    void with_common_formatters() {
        this->add_line_formatter(RemoveComments);
        this->add_line_formatter(Trim);
        this->add_line_formatter(ToLower);
        this->add_line_formatter(UnifyWhitespace);
        this->add_line_formatter(EmptyBlankLines);
        this->add_line_formatter(RemoveEspacesBeforeColon);
    }

    bool next_line();
    ParseContext parse_current_line();

    AllowInternalTestFor(Tokenizer);

   private:
    std::string __read_next_line();
    std::string __format(std::string line);
    std::string __file_content;
    int __current_line_number;
    int __current_index;
    std::vector<Formatter> __line_formatters;
    TokenParser __parser;
    std::string __line;
    ParseContext __parse(std::string line);
};

}  // namespace basilar::tokens