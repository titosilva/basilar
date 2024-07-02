#include "../test_suite.hpp"
#include "../../src/assembler/flow/tokenizer/tokenizer.hpp"

#include <filesystem>

using namespace std;
using namespace basilar::tokenizer;

DefineTestSuiteFor(Tokenizer)

    DefineTest(Preprocess__Should__LowerLine__WhenToLowerFormatter) {
        auto tokenizer = Tokenizer("Hello\nWorld");
        tokenizer.add_line_formatter(ToLower);

        auto r = tokenizer.__format("Hello");
        ASSERT_EQ(r, "hello");
    }

    DefineTest(Preprocess__Should__TrimLine__WhenTrimFormatter) {
        auto tokenizer = Tokenizer("  \tHello \t\t\n    World!   ");
        tokenizer.add_line_formatter(Trim);

        auto r = tokenizer.__format("  \tHello \t\t\n    World!   ");
        ASSERT_EQ(r, "Hello \t\t\n    World!");
    }

    DefineTest(Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespaceFormatter) {
        auto tokenizer = Tokenizer("Hello       World!");
        tokenizer.add_line_formatter(UnifyWhitespace);

        auto r = tokenizer.__format("Hello       World!");
        ASSERT_EQ(r, "Hello World!");
    }

    DefineTest(Preprocess__Should__ApplyAllFormatters__WhenMultipleFormatters) {
        auto tokenizer = Tokenizer("  \tHello \t\t    World    \t!   ");
        tokenizer.add_line_formatter(Trim);
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(UnifyWhitespace);

        auto r = tokenizer.__format("  \tHello \t\t    World    \t!   ");
        ASSERT_EQ(r, "hello world !");
    }

    DefineTest(ReadNextLine__Should__ReturnLine) {
        auto tokenizer = Tokenizer("Hello\nWorld");

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "Hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "World");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(ReadNextLine__Should__ReturnTrimmedLine) {
        auto tokenizer = Tokenizer("  \tHello \t\t");
        tokenizer.add_line_formatter(Trim);

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "Hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(ReadNextLine__Should__PreprocessedReturnLine) {
        auto tokenizer = Tokenizer("  \tHello \t\t\n    World    \t!   ");
        tokenizer.add_line_formatter(Trim);
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(UnifyWhitespace);

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "world !");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(ParseCurrentLine__Should__ParseLineWithProvidedParser) {
        auto tokenizer = Tokenizer("\t  Hello\t\t\nWorld");
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(Trim);
        tokenizer.with_parser(Literal("hello"));

        tokenizer.next_line();

        auto r = tokenizer.parse_current_line();
        ASSERT_EQ(r.get_tokens().size(), 1);
        ASSERT_EQ(r.get_tokens()[0].value, "hello");
    }

    DefineTest(FromFile__Should__ReturnTokenizerWithFileContent) {
        auto test_file = filesystem::path(__FILE__).replace_filename("test.txt");
        auto tokenizer = *Tokenizer::from_file(test_file);
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(Trim);
        tokenizer.with_parser(Literal("hello"));

        ASSERT_TRUE(tokenizer.next_line()) << "Content: " << tokenizer.__file_content;
        auto r = tokenizer.parse_current_line();

        ASSERT_EQ(r.get_tokens().size(), 1);
        ASSERT_EQ(r.get_tokens()[0].value, "hello");
    }
EndTestSuite

RunTest(Tokenizer, Preprocess__Should__LowerLine__WhenToLowerFormatter)
RunTest(Tokenizer, Preprocess__Should__TrimLine__WhenTrimFormatter)
RunTest(Tokenizer, Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespaceFormatter)
RunTest(Tokenizer, Preprocess__Should__ApplyAllFormatters__WhenMultipleFormatters)
RunTest(Tokenizer, ReadNextLine__Should__ReturnLine)
RunTest(Tokenizer, ReadNextLine__Should__ReturnTrimmedLine)
RunTest(Tokenizer, ReadNextLine__Should__PreprocessedReturnLine)
RunTest(Tokenizer, ParseCurrentLine__Should__ParseLineWithProvidedParser)
RunTest(Tokenizer, FromFile__Should__ReturnTokenizerWithFileContent)