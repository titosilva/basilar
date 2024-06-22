#pragma once

#include <string>

using namespace std;

namespace basilar::tokens::parser {

class Token {
public:
    Token(string type, string value) : type(type), value(value) {}
    string type;
    string value;
};

} // namespace basilar::tokens::parser