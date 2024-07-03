#include "../test_suite.hpp"
#include "../../src/assembler/flow/tokenizer/line_reader.hpp"

#include <filesystem>

using namespace std;
using namespace basilar::tokenizer;

DefineTestSuiteFor(LineReader)

    DefineTest(Preprocess__Should__LowerLine__WhenToLowerFormatter) {
        auto tokenizer = LineReader("Hello\nWorld");
        tokenizer.add_line_formatter(ToLower);

        auto r = tokenizer.__format("Hello");
        ASSERT_EQ(r, "hello");
    }

    DefineTest(Preprocess__Should__TrimLine__WhenTrimFormatter) {
        auto tokenizer = LineReader("  \tHello \t\t\n    World!   ");
        tokenizer.add_line_formatter(Trim);

        auto r = tokenizer.__format("  \tHello \t\t\n    World!   ");
        ASSERT_EQ(r, "Hello \t\t\n    World!");
    }

    DefineTest(Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespaceFormatter) {
        auto tokenizer = LineReader("Hello       World!");
        tokenizer.add_line_formatter(UnifyWhitespace);

        auto r = tokenizer.__format("Hello       World!");
        ASSERT_EQ(r, "Hello World!");
    }

    DefineTest(Preprocess__Should__ApplyAllFormatters__WhenMultipleFormatters) {
        auto tokenizer = LineReader("  \tHello \t\t    World    \t!   ");
        tokenizer.add_line_formatter(Trim);
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(UnifyWhitespace);

        auto r = tokenizer.__format("  \tHello \t\t    World    \t!   ");
        ASSERT_EQ(r, "hello world !");
    }

    DefineTest(ReadNextLine__Should__ReturnLine) {
        auto tokenizer = LineReader("Hello\nWorld");

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
        auto tokenizer = LineReader("  \tHello \t\t");
        tokenizer.add_line_formatter(Trim);

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "Hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(ReadNextLine__Should__PreprocessedReturnLine) {
        auto tokenizer = LineReader("  \tHello \t\t\n    World    \t!   ");
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

    DefineTest(FromFile__Should__ReturnTokenizerWithFileContent) {
        auto test_file = filesystem::path(__FILE__).replace_filename("test.txt");
        auto tokenizer = *LineReader::from_file(test_file);
        tokenizer.add_line_formatter(ToLower);
        tokenizer.add_line_formatter(Trim);

        ASSERT_TRUE(tokenizer.next_line()) << "Content: " << tokenizer.__file_content;
        auto r = tokenizer.read_current_line();
        ASSERT_EQ(r.get_remaining_input(), "hello!");
    }
EndTestSuite

RunTest(LineReader, Preprocess__Should__LowerLine__WhenToLowerFormatter)
RunTest(LineReader, Preprocess__Should__TrimLine__WhenTrimFormatter)
RunTest(LineReader, Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespaceFormatter)
RunTest(LineReader, Preprocess__Should__ApplyAllFormatters__WhenMultipleFormatters)
RunTest(LineReader, ReadNextLine__Should__ReturnLine)
RunTest(LineReader, ReadNextLine__Should__ReturnTrimmedLine)
RunTest(LineReader, ReadNextLine__Should__PreprocessedReturnLine)
RunTest(LineReader, FromFile__Should__ReturnTokenizerWithFileContent)