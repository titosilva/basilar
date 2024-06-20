#include "../../src/tokens/token_types.hpp"
#include "../test_suite.hpp"

#include <string>

using namespace std;
using namespace basilar::tokens;

DefineTestSuiteFor(ConstOperandMatcher)

    DefineTest(ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsConstOperand) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "123";

        ConstOperandMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
        ConstOperand* label = dynamic_cast<ConstOperand*>(*outToken);
        ASSERT_NE(label, nullptr);
        ASSERT_EQ(label->get_value(), "123");
        ASSERT_EQ(label->get_int_value(), 123);
    }

    DefineTest(ConstOperandMatcher__Should__ReturnFalse__When__RawTokenIsNotConstOperand) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "not_a_const_operand";

        ConstOperandMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_FALSE(result);
    }

    DefineTest(ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsHexConstOperand) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "0x7b";

        ConstOperandMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
        ConstOperand* label = dynamic_cast<ConstOperand*>(*outToken);
        ASSERT_NE(label, nullptr);
        ASSERT_EQ(label->get_value(), "0x7b");
        ASSERT_EQ(label->get_int_value(), 123);
    }

    DefineTest(ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsNegativeNumber) {
        RawToken raw;
        raw.source_column_number = 0;
        raw.value = "-123";

        ConstOperandMatcher matcher;
        Token** outToken = new Token*();
        bool result = matcher.try_match(raw, outToken);

        ASSERT_TRUE(result);
        ConstOperand* label = dynamic_cast<ConstOperand*>(*outToken);
        ASSERT_NE(label, nullptr);
        ASSERT_EQ(label->get_value(), "-123");
        ASSERT_EQ(label->get_int_value(), -123);
    }

EndTestSuite

RunTest(ConstOperandMatcher, ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsConstOperand)
RunTest(ConstOperandMatcher, ConstOperandMatcher__Should__ReturnFalse__When__RawTokenIsNotConstOperand)
RunTest(ConstOperandMatcher, ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsHexConstOperand)
RunTest(ConstOperandMatcher, ConstOperandMatcher__Should__ReturnTrue__When__RawTokenIsNegativeNumber)
