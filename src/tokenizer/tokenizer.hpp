#pragma once

#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <string>
#include <vector>

#include "../friend_test.hpp"
#include "formatter.hpp"
#include "../tokens/token.hpp"

using namespace basilar::tokens;

namespace basilar::tokenizer {

class Tokenizer {
   public:

    Tokenizer(std::string file_content) : __file_content(file_content), __current_line_number(0), __current_index(0) {}

    void add_line_formatter(Formatter formatter);
    void with_common_formatters() {
        this->add_line_formatter(RemoveComments);
        this->add_line_formatter(Trim);
        this->add_line_formatter(ToLower);
        this->add_line_formatter(UnifyWhitespace);
        this->add_line_formatter(EmptyBlankLines);
        this->add_line_formatter(RemoveEspacesBeforeColon);
    }

    bool next_line();
    Token* next_token();
    RawToken next_raw_token();

    AllowInternalTestFor(Tokenizer);

   private:
    std::string __read_next_line();
    std::string __format(std::string line);
    void __tokenize(std::string line);
    std::string __file_content;
    int __current_line_number;
    int __current_index;
    std::vector<Formatter> __line_formatters;
    std::queue<Token*> __tokens;
    std::queue<RawToken> __raw_tokens;
};

std::vector<std::string> split_line_in_spaces_and_tabs(const std::string& line);

}  // namespace basilar::tokens