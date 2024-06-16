#include "../../src/tokens/label_matcher.hpp"
#include "../test_suite.hpp"

#include <string>

using namespace std;
using namespace basilar::tokens;

DefineTestSuiteFor(LabelMatcher)

    DefineTest(LabelMatcher__Should__ReturnTrue__When__RawTokenIsLabel) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "label:";

        LabelMatcher labelMatcher;
        Token** outToken = new Token*();
        bool result = labelMatcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
    }

    DefineTest(LabelMatcher__Should__ReturnFalse__When__RawTokenDoesNotEndWithColon) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "label";

        LabelMatcher labelMatcher;
        Token** outToken = new Token*();
        bool result = labelMatcher.try_match(raw, outToken);

        ASSERT_FALSE(result);
    }

    DefineTest(LabelMatcher__Should__ReturnFalse__When__RawTokenHasSourceColumnNumber) {
        RawToken raw;
        raw.source_column_number = 1;
        raw.value = "label:";

        LabelMatcher labelMatcher;
        Token** outToken = new Token*();
        bool result = labelMatcher.try_match(raw, outToken);

        ASSERT_FALSE(result);
    }

EndTestSuite

RunTest(LabelMatcher, LabelMatcher__Should__ReturnTrue__When__RawTokenIsLabel)
// RunTest(LabelMatcher, LabelMatcher__Should__ReturnFalse__When__RawTokenDoesNotEndWithColon)
// RunTest(LabelMatcher, LabelMatcher__Should__ReturnFalse__When__RawTokenHasSourceColumnNumber)
