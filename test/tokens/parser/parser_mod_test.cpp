#include "../../../src/tokens/parser/parser.hpp"
#include "../../test_suite.hpp"

using namespace basilar::tokens::parser;

DefineGlobalTestSuiteFor(ParserMods)

    DefineGlobalTest(Optional__ShouldGetTokens__IfParserMatches) {
        auto parser = Optional(Whitespace) >> Number;
        auto result = parser.parse("    123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2);
        ASSERT_EQ(result.value().get_tokens()[0].type, "whitespace");
        ASSERT_EQ(result.value().get_tokens()[0].value, "    ");
        ASSERT_EQ(result.value().get_tokens()[1].type, "number");
        ASSERT_EQ(result.value().get_tokens()[1].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Optional__ShouldIgnore__IfParserDoesNotMatch) {
        auto parser = Optional(Whitespace) >> Number;
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Ignore__ShouldIgnore__IfParserMatches) {
        auto parser = Ignored(Whitespace) >> Number;
        auto result = parser.parse("    123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Ignore__ShouldIgnore__IfParserDoesNotMatch) {
        auto parser = Ignored(Whitespace) >> Number;
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Required__ShouldThrowException__IfParserDoesNotMatch) {
        auto parser = Required(Number, "Expected a number");
        ASSERT_THROW(parser.parse("abc"), ParsingException);
    }

    DefineGlobalTest(Required__ShouldGetTokens__IfParserMatches) {
        auto parser = Required(Number, "Expected a number");
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Repeat__ShouldGetTokens__IfParserMatches) {
        auto parser = Repeat(Number >> Ignored(Whitespace), 3);
        auto result = parser.parse("123 456 789");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 3);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_tokens()[1].type, "number");
        ASSERT_EQ(result.value().get_tokens()[1].value, "456");
        ASSERT_EQ(result.value().get_tokens()[2].type, "number");
        ASSERT_EQ(result.value().get_tokens()[2].value, "789");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(FailIf__ShouldThrowException__IfParserMatches) {
        auto parser = Forbidden(Number, "Expected not a number");
        ASSERT_THROW(parser.parse("123"), ParsingException);
    }

    DefineGlobalTest(FailIf__ShouldLetRemainingInput__IfParserDoesNotMatch) {
        auto parser = Forbidden(Number, "Expected not a number");
        auto result = parser.parse("abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 0);
        ASSERT_EQ(result.value().get_remaining_input(), "abc");
    }
EndTestSuite

RunGlobalTest(ParserMods, Optional__ShouldGetTokens__IfParserMatches)
RunGlobalTest(ParserMods, Optional__ShouldIgnore__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Ignore__ShouldIgnore__IfParserMatches)
RunGlobalTest(ParserMods, Ignore__ShouldIgnore__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Required__ShouldThrowException__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Required__ShouldGetTokens__IfParserMatches)
RunGlobalTest(ParserMods, Repeat__ShouldGetTokens__IfParserMatches)
RunGlobalTest(ParserMods, FailIf__ShouldThrowException__IfParserMatches)
RunGlobalTest(ParserMods, FailIf__ShouldLetRemainingInput__IfParserDoesNotMatch)
