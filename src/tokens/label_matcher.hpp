#pragma once

#include "label.hpp"
#include "token.hpp"
#include "token_matcher.hpp"

namespace basilar::tokens {

class LabelMatcher : public TokenMatcher {
public:
    bool try_match(RawToken raw, Token** outToken) {
        if (raw.source_column_number != 0) return false;
        if (raw.value.size() == 0) return false;
        if (raw.value.back() != ':') return false;

        // TODO: check if the label is valid

        *outToken = new Label(raw);
        return true;
    }
};

} // namespace basilar::tokens