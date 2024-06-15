#pragma once

#include <string>

namespace basilar::tokens {

enum class TokenType {
    LABEL = 1,
    INSTRUCTION = 2,
    OPERAND = 3,
};

class Token {
public:
    Token(TokenType type, std::string value, std::string line, int line_number) : type(type), value(value), line(line), line_number(line_number) {};
    
    TokenType type;
    std::string value;
    std::string line;
    int line_number;
};

} // namespace basilar::tokens