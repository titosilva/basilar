#include "../../../src/tokens/parser/regex_parser.hpp"
#include "../../test_suite.hpp"

using namespace std;
using namespace basilar::tokens::parser;

DefineTestSuiteFor(RegexParser)

    DefineTest(ShouldParseToken__IfRegexMatches) {
        auto parser = RegexParser("^[0-9]+", "number");
        auto result = parser.parse("123abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
    }

    DefineTest(ShouldNotParseToken__IfRegexDoesNotMatch) {
        auto parser = RegexParser("^[0-9]+", "number");
        auto result = parser.parse("abc123");

        ASSERT_FALSE(result.has_value());
    }

EndTestSuite

RunTest(RegexParser, ShouldParseToken__IfRegexMatches)