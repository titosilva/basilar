#pragma once

#include <string>

#include "token.hpp"
#include "token_matcher.hpp"
#include "../utils/string_utils.hpp"

using namespace std;
using namespace basilar::utils;

namespace basilar::tokens {

class ConstOperandMatcher : public TokenMatcher {
public:
    bool try_match(RawToken raw, Token** outToken) {
        if (raw.value.size() == 0) return false;

        int parsed;
        if (StringUtils::try_parse_int(raw.value, &parsed)) {
            *outToken = new ConstOperand(raw, parsed);
            return true;
        }

        if (raw.value.substr(0, 2) == "0x" && StringUtils::try_parse_int(raw.value.substr(2), &parsed, 16)) {
            *outToken = new ConstOperand(raw, parsed);
            return true;
        }

        return false;
    }
};

} // namespace basilar::tokens