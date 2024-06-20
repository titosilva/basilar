#pragma once

#include <string>
#include "token.hpp"

using namespace std;

namespace basilar::tokens {

class ConstOperand : public Token {
public:
    ConstOperand(RawToken raw, int parsed) : Token(raw), __parsed(parsed) {}
    string get_type_name() { return "const_operand"; }
    string get_value() { return raw.value; }
    int get_int_value() { return __parsed; }

private:
    int __parsed;
};

} // namespace basilar::tokens