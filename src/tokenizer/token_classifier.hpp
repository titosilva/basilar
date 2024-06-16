#pragma once

#include <string>

using namespace std;

namespace basilar::tokenizer {

class TokenClassMatcher {
public:
    virtual bool matches(string value, int column) = 0;
}

class LabelMatcher : public TokenClassMatcher {
public:
    bool matches(string value, int column);
}

} // namespace basilar::tokens