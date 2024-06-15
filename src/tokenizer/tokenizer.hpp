#pragma once

#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <string>
#include <vector>

#include "../friend_test.hpp"
#include "preprocessor.hpp"
#include "token.hpp"

namespace basilar::tokens {

class Tokenizer {
   public:

    Tokenizer(std::string file_content) : __file_content(file_content), __current_line_number(0), __current_index(0) {}

    void add_line_preprocessor(Preprocessor preprocessor);
    void with_common_preprocessors() {
        this->add_line_preprocessor(Trim);
        this->add_line_preprocessor(ToLower);
        this->add_line_preprocessor(UnifyWhitespace);
    }

    bool next_line();
    Token next_token();

    AllowInternalTestFor(Tokenizer);

   private:
    std::string __read_next_line();
    std::string __preprocess(std::string line);
    void __tokenize(std::string line);
    std::string __file_content;
    int __current_line_number;
    int __current_index;
    std::vector<Preprocessor> __line_preprocessors;
    std::queue<Token> __tokens;

   public:  // For testing purposes
    std::vector<Preprocessor> get_line_preprocessors() {
        return this->__line_preprocessors;
    }
};

std::vector<std::string> split_line_in_spaces_and_tabs(const std::string& line);

}  // namespace basilar::tokens