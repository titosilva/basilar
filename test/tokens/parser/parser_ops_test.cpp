#include "../../../src/assembler/tokens/parser/regex_parser.hpp"
#include "../../test_suite.hpp"

using namespace std;
using namespace basilar::assembler::tokens::parser;

DefineGlobalTestSuiteFor(ParserOps)

    DefineGlobalTest(ShouldParseAllTokens__WhenDirectlyCombined) {
        auto parser = RegexParser("^[0-9]+", "number") >> RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("123abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_tokens()[1].type, "letter");
        ASSERT_EQ(result.value().get_tokens()[1].value, "abc");
    }

    DefineGlobalTest(ShouldNotParseAnyTokens__WhenFirstParserFails) {
        auto parser = RegexParser("^[0-9]+", "number") >> RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("abc123");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(ShouldNotParseAnyTokens__WhenSecondParserFails) {
        auto parser = RegexParser("^[0-9]+", "number") >> RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("123");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(ShouldParseAllTokens__WithOrCombined__AndFirstParserFails) {
        auto parser = RegexParser("^[0-9]+", "number") | RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("abc123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "letter");
        ASSERT_EQ(result.value().get_tokens()[0].value, "abc");
    }

    DefineGlobalTest(ShouldNotParseAnyTokens__WhenBothParsersFail) {
        auto parser = RegexParser("^[0-9]+", "number") | RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("*");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(ShouldParseAllTokens__WhenBothParsersSucceed) {
        auto parser = RegexParser("^[0-9]+", "number") | RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
    }

    DefineGlobalTest(ShouldParseAllTokens__WhenOptionalCombined) {
        auto parser = RegexParser("^[0-9]+", "number") << RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("123abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_tokens()[1].type, "letter");
        ASSERT_EQ(result.value().get_tokens()[1].value, "abc");
    }

    DefineGlobalTest(ShouldNotParseAnyTokens__WhenOptionalCombined__AndFirstParserFails) {
        auto parser = RegexParser("^[0-9]+", "number") << RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("abc123");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(ShouldParseAllTokens__WhenOptionalCombined__AndSecondParserFails) {
        auto parser = RegexParser("^[0-9]+", "number") << RegexParser("^[a-z]+", "letter");
        auto result = parser.parse("123**");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
    }

    DefineGlobalTest(ShouldParseExactTokens__WhenAdditionIsUsedToString) {
        auto parser = RegexParser("^[0-9]+", "number") + "abc";
        auto result = parser.parse("123abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_tokens()[1].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[1].value, "abc");
    }
EndGlobalTestSuite

RunGlobalTest(ParserOps, ShouldParseAllTokens__WhenDirectlyCombined)
RunGlobalTest(ParserOps, ShouldNotParseAnyTokens__WhenFirstParserFails)
RunGlobalTest(ParserOps, ShouldNotParseAnyTokens__WhenSecondParserFails)
RunGlobalTest(ParserOps, ShouldParseAllTokens__WithOrCombined__AndFirstParserFails)
RunGlobalTest(ParserOps, ShouldNotParseAnyTokens__WhenBothParsersFail)
RunGlobalTest(ParserOps, ShouldParseAllTokens__WhenBothParsersSucceed)
RunGlobalTest(ParserOps, ShouldParseAllTokens__WhenOptionalCombined)
RunGlobalTest(ParserOps, ShouldNotParseAnyTokens__WhenOptionalCombined__AndFirstParserFails)
RunGlobalTest(ParserOps, ShouldParseAllTokens__WhenOptionalCombined__AndSecondParserFails)

