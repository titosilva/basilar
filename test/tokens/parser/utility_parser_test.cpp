#include "../../../src/assembler/tokens/parser/utility_parsers.hpp"
#include "../../test_suite.hpp"

using namespace std;
using namespace basilar::assembler::tokens::parser;

DefineGlobalTestSuiteFor(UtilityParsers)    
    DefineGlobalTest(Literal__ShouldParseToken__IfExactMatch) {
        auto parser = Literal("123");
        auto result = parser.parse("123abc");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "abc");
    }

    DefineGlobalTest(Literal__ShouldNotParseToken__IfExactMatchFails) {
        auto parser = Literal("123");
        auto result = parser.parse("abc123");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(End__ShouldParseToken__IfEndOfInput) {
        auto parser = End;
        auto result = parser.parse("");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "end");
        ASSERT_EQ(result.value().get_tokens()[0].value, "");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(End__ShouldNotParseToken__IfInputNotEmpty) {
        auto parser = End;
        auto result = parser.parse("abc");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(NotWhitespace__ShouldParseToken__IfNotEmpty) {
        auto parser = NotWhitespace;
        auto result = parser.parse("abc 123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "notwhitespace");
        ASSERT_EQ(result.value().get_tokens()[0].value, "abc");
        ASSERT_EQ(result.value().get_remaining_input(), " 123");
    }

    DefineGlobalTest(Note__Should__AddAnnotation__WhenParseSucceeds) {
        auto parser =  Literal("123") >> Note("key", "value");
        auto result = parser.parse("123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_annotations().size(), 1);
        ASSERT_EQ(result.value().get_annotations()["key"], "value");
        ASSERT_TRUE(result.value().has_annotation("key"));
    }

    DefineGlobalTest(Note__ShouldNot__AddAnnotation__WhenParseFails) {
        auto parser =  Literal("123") >> Note("key", "value");
        auto result = parser.parse("abc");

        ASSERT_FALSE(result.has_value());
    }
EndGlobalTestSuite

RunGlobalTest(UtilityParsers, Literal__ShouldParseToken__IfExactMatch)
RunGlobalTest(UtilityParsers, Literal__ShouldNotParseToken__IfExactMatchFails)
RunGlobalTest(UtilityParsers, End__ShouldParseToken__IfEndOfInput)
RunGlobalTest(UtilityParsers, End__ShouldNotParseToken__IfInputNotEmpty)
RunGlobalTest(UtilityParsers, NotWhitespace__ShouldParseToken__IfNotEmpty)
RunGlobalTest(UtilityParsers, Note__Should__AddAnnotation__WhenParseSucceeds)
RunGlobalTest(UtilityParsers, Note__ShouldNot__AddAnnotation__WhenParseFails)
