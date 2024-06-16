#pragma once

#include "token.hpp"

namespace basilar::tokens {

class TokenMatcher {
public:
    virtual bool try_match(RawToken raw, Token** outToken) = 0;
};

} // namespace basilar::tokens