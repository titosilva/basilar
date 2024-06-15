#pragma once

#include <string>
#include <vector>
#include <functional>
#include <gtest/gtest.h>

#include "preprocessor.hpp"
#include "token.hpp"
#include "../friend_test.hpp"

namespace basilar::tokens {

class Tokenizer { 
public:
    Tokenizer(const std::string& file_content) : file_content(file_content), current_line(0), current_index(0) {};

    void add_line_preprocessor(Preprocessor preprocessor);

    std::string next_line();
    std::vector<Token> get_tokens() const;
    Token next_token();

    AllowInternalTestFor(Tokenizer);
private:
    std::string __preprocess(const std::string& line);
    void __tokenize(const std::string& line);
    const std::string& file_content;
    int current_line;
    int current_index;
    std::vector<Preprocessor> line_preprocessors;
    std::vector<Token> tokens;

public: // For testing purposes
    std::vector<Preprocessor> get_line_preprocessors() {
        return this->line_preprocessors;
    }
};

std::vector<std::string> split_line_in_spaces_and_tabs(const std::string& line);

} // namespace basilar::tokens