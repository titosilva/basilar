#include "../test_suite.hpp"
#include "../../src/tokenizer/tokenizer.hpp"

using namespace std;
using namespace basilar::tokens;

DefineTestSuiteFor(Tokenizer)

    DefineTest(Preprocess__Should__PreprocessLine__WhenLinePreprocessors) {
        auto tokenizer = Tokenizer("Hello\nWorld");
        tokenizer.add_line_preprocessor([](string line) {
            string s;
            for (auto& c : line) {
                s += tolower(c);
            }

            return s;
        });

        auto r = tokenizer.__preprocess("Hello");
        ASSERT_EQ(r, "hello");
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

EndTestSuite

RunTest(Tokenizer, Preprocess__Should__PreprocessLine__WhenLinePreprocessors)
RunTest(Tokenizer, SplitLine__Should__SplitStringBySpaces__WhenOneSpace)
RunTest(Tokenizer, SplitLine__Should__SplitStringBySpacesAndTabs__WhenSpacesAndTabs)