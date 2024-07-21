#include "../test_suite.hpp"
#include "../../src/assembler/tokens/assembler_specs.hpp"

using namespace std;
using namespace basilar::tokens;
using namespace basilar::assembler::tokens::parser;

DefineGlobalTestSuiteFor(AssemblerSpecs)
    DefineGlobalTest(addCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = addCall;
        auto result = parser.parse("add label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "add");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "add");
    }

    DefineGlobalTest(addCall__ShouldParse__WhenArgsAreExpression) {
        auto parser = addCall;
        auto result = parser.parse("add label + 2");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "add");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label+2");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "add");
    }

    DefineGlobalTest(addCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = addCall;
        ASSERT_THROW(parser.parse("add"), ParsingException);
    }

    DefineGlobalTest(subCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = subCall;
        auto result = parser.parse("sub label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "sub");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "sub");
    }

    DefineGlobalTest(subCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = subCall;
        ASSERT_THROW(parser.parse("sub"), ParsingException);
    }

    DefineGlobalTest(mulCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = mulCall;
        auto result = parser.parse("mul label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "mul");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "mul");
    }

    DefineGlobalTest(mulCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = mulCall;
        ASSERT_THROW(parser.parse("mul"), ParsingException);
    }

    DefineGlobalTest(divCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = divCall;
        auto result = parser.parse("\t\t\t\t\t\t     div   \t label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "div");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "div");
    }

    DefineGlobalTest(divCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = divCall;
        ASSERT_THROW(parser.parse("div"), ParsingException);
    }

    DefineGlobalTest(jmpCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = jmpCall;
        auto result = parser.parse("\tjmp         label\t\t");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "jmp");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "jmp");
    }

    DefineGlobalTest(jmpCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = jmpCall;
        ASSERT_THROW(parser.parse("jmp"), ParsingException);
    }

    DefineGlobalTest(jmpnCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = jmpnCall;
        auto result = parser.parse("                       jmpn \t label\t");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "jmpn");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "jmpn");
    }

    DefineGlobalTest(jmpnCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = jmpnCall;
        ASSERT_THROW(parser.parse("jmpn"), ParsingException);
    }

    DefineGlobalTest(jmppCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = jmppCall;
        auto result = parser.parse("jmpp             label                           ");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "jmpp");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "jmpp");
    }

    DefineGlobalTest(jmppCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = jmppCall;
        ASSERT_THROW(parser.parse("jmpp"), ParsingException);
    }

    DefineGlobalTest(jmpzCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = jmpzCall;
        auto result = parser.parse("jmpz label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "jmpz");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "jmpz");
    }

    DefineGlobalTest(jmpzCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = jmpzCall;
        ASSERT_THROW(parser.parse("jmpz"), ParsingException);
    }

    DefineGlobalTest(copyCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = copyCall;
        auto result = parser.parse("copy label1,label2");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 3)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "copy");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label1");
        ASSERT_EQ(result.value().get_tokens()[2].type, "label");
        ASSERT_EQ(result.value().get_tokens()[2].value, "label2");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "copy");
    }

    DefineGlobalTest(copyCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = copyCall;
        ASSERT_THROW(parser.parse("copy"), ParsingException);
    }

    DefineGlobalTest(loadCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = loadCall;
        auto result = parser.parse("load label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "load");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "load");
    }

    DefineGlobalTest(loadCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = loadCall;
        ASSERT_THROW(parser.parse("load"), ParsingException);
    }

    DefineGlobalTest(storeCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = storeCall;
        auto result = parser.parse("\t\tstore\t   label\t\t   \t\t   ");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "store");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "store");
    }

    DefineGlobalTest(storeCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = storeCall;
        ASSERT_THROW(parser.parse("store"), ParsingException);
    }

    DefineGlobalTest(inputCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = inputCall;
        auto result = parser.parse("input label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "input");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "input");
    }

    DefineGlobalTest(inputCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = inputCall;
        ASSERT_THROW(parser.parse("input"), ParsingException);
    }

    DefineGlobalTest(outputCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = outputCall;
        auto result = parser.parse("output label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "output");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "output");
    }

    DefineGlobalTest(outputCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel) {
        auto parser = outputCall;
        ASSERT_THROW(parser.parse("output"), ParsingException);
    }

    DefineGlobalTest(stopCall__ShouldParse__WhenArgsAreCorrect) {
        auto parser = stopCall;
        auto result = parser.parse("stop");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "stop");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "stop");
    }

    DefineGlobalTest(stopCall__ShouldThrow__WhenInstructionIsFollowedByLabel) {
        auto parser = stopCall;
        ASSERT_THROW(parser.parse("stop label"), ParsingException);
    }

    DefineGlobalTest(InstructionLine__ShouldParse__WhenLabelIsDefined) {
        auto parser = InstructionLine;
        auto result = parser.parse("label: add label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 3)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value
            << "; Token 1 type: " << result.value().get_tokens()[0].type;

        ASSERT_EQ(result.value().get_tokens()[0].type, "labeldef");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_tokens()[1].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[1].value, "add");
        ASSERT_EQ(result.value().get_tokens()[2].type, "label");
        ASSERT_EQ(result.value().get_tokens()[2].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "add");
    }

    DefineGlobalTest(InstructionLine__ShouldParse__WhenLabelIsNotDefined) {
        auto parser = InstructionLine;
        auto result = parser.parse("add label");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[0].value, "add");
        ASSERT_EQ(result.value().get_tokens()[1].type, "label");
        ASSERT_EQ(result.value().get_tokens()[1].value, "label");
        ASSERT_EQ(result.value().get_remaining_input(), "");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "add");
    }

    DefineGlobalTest(InstructionLine__ShouldParse__WhenInstructionIsCopy) {
        auto parser = InstructionLine;
        auto result = parser.parse("\t\t\t\t   label:\t \tcopy\tlabel1,label2");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 4)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;

        ASSERT_EQ(result.value().get_tokens()[0].type, "labeldef");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_tokens()[1].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[1].value, "copy");
        ASSERT_EQ(result.value().get_tokens()[2].type, "label");
        ASSERT_EQ(result.value().get_tokens()[2].value, "label1");
        ASSERT_EQ(result.value().get_tokens()[3].type, "label");
        ASSERT_EQ(result.value().get_tokens()[3].value, "label2");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "copy");
    }

    DefineGlobalTest(InstructionLine__ShouldParse__WhenInstructionIsStop) {
        auto parser = InstructionLine;
        auto result = parser.parse("label: stop");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 2)
            << "Tokens size: " << result.value().get_tokens().size()
            << "; Remaining input: " << result.value().get_remaining_input()
            << "; Token 1: " << result.value().get_tokens()[0].value;
        
        ASSERT_EQ(result.value().get_tokens()[0].type, "labeldef");
        ASSERT_EQ(result.value().get_tokens()[0].value, "label:");
        ASSERT_EQ(result.value().get_tokens()[1].type, "literal");
        ASSERT_EQ(result.value().get_tokens()[1].value, "stop");

        ASSERT_TRUE(result.value().has_annotation("instruction_call"));
        ASSERT_EQ(result.value().get_annotations().at("instruction_call"), "stop");
    }
EndGlobalTestSuite

RunGlobalTest(AssemblerSpecs, addCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, addCall__ShouldParse__WhenArgsAreExpression)
RunGlobalTest(AssemblerSpecs, addCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, subCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, subCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, mulCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, mulCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, divCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, divCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, jmpCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, jmpCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, jmpnCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, jmpnCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, jmppCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, jmppCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, jmpzCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, jmpzCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, copyCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, copyCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, loadCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, loadCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, storeCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, storeCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, inputCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, inputCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, outputCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, outputCall__ShouldThrow__WhenInstructionIsNotFollowedByLabel)
RunGlobalTest(AssemblerSpecs, stopCall__ShouldParse__WhenArgsAreCorrect)
RunGlobalTest(AssemblerSpecs, stopCall__ShouldThrow__WhenInstructionIsFollowedByLabel)
RunGlobalTest(AssemblerSpecs, InstructionLine__ShouldParse__WhenLabelIsDefined)
RunGlobalTest(AssemblerSpecs, InstructionLine__ShouldParse__WhenLabelIsNotDefined)
RunGlobalTest(AssemblerSpecs, InstructionLine__ShouldParse__WhenInstructionIsCopy)
RunGlobalTest(AssemblerSpecs, InstructionLine__ShouldParse__WhenInstructionIsStop)

