#pragma once

#include <string>

using namespace std;

namespace basilar::tokens {

class PreprocessingDirectiveMatcher : public TokenMatcher {
public:
    bool try_match(RawToken raw, Token** outToken) {
        if (raw.value.size() == 0) return false;
        
        if (raw.value == "if" && raw.source_column_number == 0) {
            *outToken = new PreprocessingDirective(raw);
            return true;
        }

        if (raw.value == "equ" && (raw.source_column_number == 1 || raw.source_column_number == 0)) {
            *outToken = new PreprocessingDirective(raw);
            return true;
        }

        return false;
    }
};

} // namespace basilar::tokens