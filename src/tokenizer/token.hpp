#pragma once

#include <string>

namespace basilar::tokens {

enum class TokenType {
    
};

struct Token {
    TokenType type;
    std::string value;

    std::string raw;
    std::string line;
    int line_number;
};

} // namespace basilar::tokens