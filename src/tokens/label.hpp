#pragma once

#include "token.hpp"
#include "../utils/string_utils.hpp"

using namespace basilar::utils;

namespace basilar::tokens {

class Label : public Token {
public:
    Label(RawToken raw) : Token(raw) {}
    string get_type_name() { return "label"; }
    string get_value() { return StringUtils::replace(raw.value, ":", ""); }
};

} // namespace basilar::tokens