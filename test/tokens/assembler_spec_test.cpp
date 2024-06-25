#include "../test_suite.hpp"
#include "../../src/tokens/assembler_specs.hpp"

using namespace std;
using namespace basilar::tokens;
using namespace basilar::tokens::parser;

DefineGlobalTestSuiteFor(AssemblerSpecs)
    DefineGlobalTest(Label__ShouldParseSequencesWithLettersNumbersAndUnderscores) {
        auto parser = Label;
        auto result = parser.parse("label_123");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "label");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label_123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(Label__ShouldNotParseSequencesStartingWithNumber) {
        auto parser = Label;
        auto result = parser.parse("123label");

        ASSERT_FALSE(result.has_value()) 
            << "Label parsed result starting with number: " 
            << result.value().get_tokens()[0].value 
            << "; Remaining input: " << result.value().get_remaining_input();
    }

    DefineGlobalTest(Label__ShouldNotParseSequencesWithInvalidChars) {
        auto parser = Label;
        auto result = parser.parse("@label");

        ASSERT_FALSE(result.has_value());
    }

    DefineGlobalTest(LabelDef__ShouldParseLabelDefinition) {
        auto parser = LabelDef;
        auto result = parser.parse("  label: and a b");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "label");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_remaining_input(), "and a b");
    }

    DefineGlobalTest(LabelDef__ShouldParseLabelDefinition__WhenLabelContainsUnderscore) {
        auto parser = LabelDef;
        auto result = parser.parse("\t    \tlabel_: and a b");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "label");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label_:");
        ASSERT_EQ(result.value().get_remaining_input(), "and a b");
    }

    DefineGlobalTest(LabelDef__ShouldParseLabelDefinition__WhenThereIsSpaceBeforeColon) {
        auto parser = LabelDef;
        auto result = parser.parse("  label : and a b");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "label");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_remaining_input(), "and a b");
    }

    DefineGlobalTest(LabelDef__ShouldThrow__WhenLabelStartsWithNumber) {
        auto parser = LabelDef;
        ASSERT_THROW(parser.parse("123label: and a b"), ParsingException);
    }

    DefineGlobalTest(LabelDef__ShouldThrow__WhenLabelContainsInvalidChars) {
        auto parser = LabelDef;
        ASSERT_THROW(parser.parse("label@: and a b"), ParsingException);
    }

    DefineGlobalTest(EquDirective__ShouldParse__WhenNumberIsProvided) {
        auto parser = EquDirectiveLine;
        auto result = parser.parse("label: equ 123   ");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 3);
        ASSERT_EQ(result.value().get_tokens()[0].type, "label");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_tokens()[1].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[1].value, "equ");
        ASSERT_EQ(result.value().get_tokens()[2].type, "number");
        ASSERT_EQ(result.value().get_tokens()[2].value, "123");
        ASSERT_EQ(result.value().get_remaining_input(), "");
    }

    DefineGlobalTest(EquDirective__ShouldThrow__WhenNumberIsNotProvided) {
        auto parser = EquDirectiveLine;
        ASSERT_THROW(parser.parse("label: equ"), ParsingException);
    }

    DefineGlobalTest(EquDirective__ShouldThrow__WhenLabelIsNotProvided) {
        auto parser = EquDirectiveLine;
        ASSERT_THROW(parser.parse("equ 123"), ParsingException);
    }

    DefineGlobalTest(EquDirective__ShouldThrow__WhenTooManyArguments) {
        auto parser = EquDirectiveLine;
        ASSERT_THROW(parser.parse("label: equ 123 456"), ParsingException);
    }
EndGlobalTestSuite

RunGlobalTest(AssemblerSpecs, Label__ShouldParseSequencesWithLettersNumbersAndUnderscores)
RunGlobalTest(AssemblerSpecs, Label__ShouldNotParseSequencesStartingWithNumber)
RunGlobalTest(AssemblerSpecs, Label__ShouldNotParseSequencesWithInvalidChars)
RunGlobalTest(AssemblerSpecs, LabelDef__ShouldParseLabelDefinition)
RunGlobalTest(AssemblerSpecs, LabelDef__ShouldParseLabelDefinition__WhenLabelContainsUnderscore)
RunGlobalTest(AssemblerSpecs, LabelDef__ShouldParseLabelDefinition__WhenThereIsSpaceBeforeColon)
RunGlobalTest(AssemblerSpecs, LabelDef__ShouldThrow__WhenLabelStartsWithNumber)
RunGlobalTest(AssemblerSpecs, LabelDef__ShouldThrow__WhenLabelContainsInvalidChars)
RunGlobalTest(AssemblerSpecs, EquDirective__ShouldParse__WhenNumberIsProvided)
RunGlobalTest(AssemblerSpecs, EquDirective__ShouldThrow__WhenNumberIsNotProvided)
RunGlobalTest(AssemblerSpecs, EquDirective__ShouldThrow__WhenLabelIsNotProvided)
RunGlobalTest(AssemblerSpecs, EquDirective__ShouldThrow__WhenTooManyArguments)

