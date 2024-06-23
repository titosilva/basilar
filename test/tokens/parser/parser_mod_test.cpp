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
        ASSERT_EQ(result.value().remaining_input, "");
    }

    DefineGlobalTest(Optional__ShouldIgnore__IfParserDoesNotMatch) {
        auto parser = Optional(Whitespace) >> Number;
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().remaining_input, "");
    }

    DefineGlobalTest(Ignore__ShouldIgnore__IfParserMatches) {
        auto parser = Ignore(Whitespace) >> Number;
        auto result = parser.parse("    123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().remaining_input, "");
    }

    DefineGlobalTest(Ignore__ShouldIgnore__IfParserDoesNotMatch) {
        auto parser = Ignore(Whitespace) >> Number;
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().remaining_input, "");
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
        ASSERT_EQ(result.value().remaining_input, "");
    }
EndTestSuite

RunGlobalTest(ParserMods, Optional__ShouldGetTokens__IfParserMatches)
RunGlobalTest(ParserMods, Optional__ShouldIgnore__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Ignore__ShouldIgnore__IfParserMatches)
RunGlobalTest(ParserMods, Ignore__ShouldIgnore__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Required__ShouldThrowException__IfParserDoesNotMatch)
RunGlobalTest(ParserMods, Required__ShouldGetTokens__IfParserMatches)