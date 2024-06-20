#include "../../src/tokens/token_types.hpp"
#include "../test_suite.hpp"

#include <string>

using namespace std;
using namespace basilar::tokens;

DefineTestSuiteFor(PreprocessingDirectiveMatcher)

    DefineTest(PreprocessingDirectiveMatcher__Should__ReturnTrue__When__RawTokenIsIfDirective) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "if";

        PreprocessingDirectiveMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
        PreprocessingDirective* label = dynamic_cast<PreprocessingDirective*>(*outToken);
        ASSERT_NE(label, nullptr);
        ASSERT_EQ(label->get_value(), "if");
    }

    DefineTest(PreprocessingDirectiveMatcher__Should__ReturnTrue__When__RawTokenIsEquDirective) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "equ";

        PreprocessingDirectiveMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
        PreprocessingDirective* label = dynamic_cast<PreprocessingDirective*>(*outToken);
        ASSERT_NE(label, nullptr);
        ASSERT_EQ(label->get_value(), "equ");
    }


    DefineTest(PreprocessingDirectiveMatcher__Should__ReturnFalse__When__RawTokenIsNotPreprocessingDirective) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "not_a_directive";

        PreprocessingDirectiveMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_FALSE(result);
    }
EndTestSuite

RunTest(PreprocessingDirectiveMatcher, PreprocessingDirectiveMatcher__Should__ReturnTrue__When__RawTokenIsIfDirective)
RunTest(PreprocessingDirectiveMatcher, PreprocessingDirectiveMatcher__Should__ReturnTrue__When__RawTokenIsEquDirective)
RunTest(PreprocessingDirectiveMatcher, PreprocessingDirectiveMatcher__Should__ReturnFalse__When__RawTokenIsNotPreprocessingDirective)

