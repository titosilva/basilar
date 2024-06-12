#include "../../src/tokenizer/tokenizer.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace basilar::tokens;

TEST(TokenizerTest, SplitLine__Should__SplitStringBySpaces__WhenOneSpace) {
    auto tokens = split_line_in_spaces_and_tabs("Hello World");
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens[0], "Hello");
    ASSERT_EQ(tokens[1], "World");
}

TEST(TokenizerTest, SplitLine__Should__SplitStringBySpacesAndTabs__WhenSpacesAndTabs) {
    auto tokens = split_line_in_spaces_and_tabs("1\t2\t3 4\t5 6");
    ASSERT_EQ(tokens.size(), 6);
    ASSERT_EQ(tokens[0], "1");
    ASSERT_EQ(tokens[1], "2");
    ASSERT_EQ(tokens[2], "3");
    ASSERT_EQ(tokens[3], "4");
    ASSERT_EQ(tokens[4], "5");
    ASSERT_EQ(tokens[5], "6");
}