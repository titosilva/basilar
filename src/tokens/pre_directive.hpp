#pragma once

#include "token.hpp"

using namespace std;

namespace basilar::tokens {

class PreprocessingDirective : public Token {
public:
    PreprocessingDirective(RawToken raw) : Token(raw) {}
    string get_type_name() { return "preprocessing_directive"; }
    string get_value() { return raw.value; }
};

} // namespace basilar::tokens