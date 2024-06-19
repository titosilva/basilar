#include "../test_suite.hpp"
#include "../../src/tokenizer/tokenizer.hpp"

using namespace std;
using namespace basilar::tokenizer;

DefineTestSuiteFor(Tokenizer)

    DefineTest(Preprocess__Should__LowerLine__WhenToLowerPreprocessor) {
        auto tokenizer = Tokenizer("Hello\nWorld");
        tokenizer.add_line_preprocessor(ToLower);

        auto r = tokenizer.__preprocess("Hello");
        ASSERT_EQ(r, "hello");
    }

    DefineTest(Preprocess__Should__TrimLine__WhenTrimPreprocessor) {
        auto tokenizer = Tokenizer("  \tHello \t\t\n    World!   ");
        tokenizer.add_line_preprocessor(Trim);

        auto r = tokenizer.__preprocess("  \tHello \t\t\n    World!   ");
        ASSERT_EQ(r, "Hello \t\t\n    World!");
    }

    DefineTest(Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespacePreprocessor) {
        auto tokenizer = Tokenizer("Hello       World!");
        tokenizer.add_line_preprocessor(UnifyWhitespace);

        auto r = tokenizer.__preprocess("Hello       World!");
        ASSERT_EQ(r, "Hello World!");
    }

    DefineTest(Preprocess__Should__ApplyAllPreprocessors__WhenMultiplePreprocessors) {
        auto tokenizer = Tokenizer("  \tHello \t\t    World    \t!   ");
        tokenizer.add_line_preprocessor(Trim);
        tokenizer.add_line_preprocessor(ToLower);
        tokenizer.add_line_preprocessor(UnifyWhitespace);

        auto r = tokenizer.__preprocess("  \tHello \t\t    World    \t!   ");
        ASSERT_EQ(r, "hello world !");
    }
    
    DefineTest(SplitLine__Should__SplitStringBySpaces__WhenOneSpace) {
        auto tokens = split_line_in_spaces_and_tabs("Hello World");
        ASSERT_EQ(tokens.size(), 2);
        ASSERT_EQ(tokens[0], "Hello");
        ASSERT_EQ(tokens[1], "World");
    }

    DefineTest(SplitLine__Should__SplitStringBySpacesAndTabs__WhenSpacesAndTabs) {
        auto tokens = split_line_in_spaces_and_tabs("1\t2\t3 4\t5 6");
        ASSERT_EQ(tokens.size(), 6);
        ASSERT_EQ(tokens[0], "1");
        ASSERT_EQ(tokens[1], "2");
        ASSERT_EQ(tokens[2], "3");
        ASSERT_EQ(tokens[3], "4");
        ASSERT_EQ(tokens[4], "5");
        ASSERT_EQ(tokens[5], "6");
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
        tokenizer.add_line_preprocessor(Trim);

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "Hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(ReadNextLine__Should__PreprocessedReturnLine) {
        auto tokenizer = Tokenizer("  \tHello \t\t\n    World    \t!   ");
        tokenizer.add_line_preprocessor(Trim);
        tokenizer.add_line_preprocessor(ToLower);
        tokenizer.add_line_preprocessor(UnifyWhitespace);

        auto r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "hello");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "world !");

        r = tokenizer.__read_next_line();
        ASSERT_EQ(r, "\0");
    }

    DefineTest(NextToken__Should__RetrieveTokenInFirstLine) {
        auto tokenizer = Tokenizer("rot1:\tjmp a1\n\tjmp a3");
        tokenizer.with_common_preprocessors();

        ASSERT_TRUE(tokenizer.next_line());
        auto token = tokenizer.next_token();
        ASSERT_EQ(token.value, "rot1:");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "jmp");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "a1");
    }

    DefineTest(NextToken__Should__RetrieveTokenInNextLine) {
        auto tokenizer = Tokenizer("rot1:\tjmp a1\n\t\tjmp\t\ta3    ");
        tokenizer.with_common_preprocessors();

        ASSERT_TRUE(tokenizer.next_line());
        ASSERT_TRUE(tokenizer.next_line());

        auto token = tokenizer.next_token();
        ASSERT_EQ(token.value, "jmp");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "a3");

        ASSERT_FALSE(tokenizer.next_line());
    }

    DefineTest(NextToken__Should__RetrieveTokenInNextLine__WithComments__AndBlankLines) {
        auto tokenizer = Tokenizer("rot1:\tjmp a1; this is a comment\n\t; Commented\t\t\n\n\n\t\t\tjmp\t\ta3    ");
        tokenizer.with_common_preprocessors();

        ASSERT_TRUE(tokenizer.next_line());
        auto token = tokenizer.next_token();
        ASSERT_EQ(token.value, "rot1:");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "jmp");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "a1");

        ASSERT_TRUE(tokenizer.next_line());
        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "jmp");

        token = tokenizer.next_token();
        ASSERT_EQ(token.value, "a3");

        ASSERT_FALSE(tokenizer.next_line());
    }
EndTestSuite

RunTest(Tokenizer, Preprocess__Should__LowerLine__WhenToLowerPreprocessor)
RunTest(Tokenizer, Preprocess__Should__TrimLine__WhenTrimPreprocessor)
RunTest(Tokenizer, Preprocess__Should__UnifyWhitespace__WhenUnifyWhitespacePreprocessor)
RunTest(Tokenizer, Preprocess__Should__ApplyAllPreprocessors__WhenMultiplePreprocessors)
RunTest(Tokenizer, SplitLine__Should__SplitStringBySpaces__WhenOneSpace)
RunTest(Tokenizer, SplitLine__Should__SplitStringBySpacesAndTabs__WhenSpacesAndTabs)
RunTest(Tokenizer, ReadNextLine__Should__ReturnLine)
RunTest(Tokenizer, ReadNextLine__Should__ReturnTrimmedLine)
RunTest(Tokenizer, ReadNextLine__Should__PreprocessedReturnLine)
RunTest(Tokenizer, NextToken__Should__RetrieveTokenInFirstLine)
RunTest(Tokenizer, NextToken__Should__RetrieveTokenInNextLine)
RunTest(Tokenizer, NextToken__Should__RetrieveTokenInNextLine__WithComments__AndBlankLines)