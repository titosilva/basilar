#pragma once

#include <gtest/gtest.h>
#include "../src/friend_test.hpp"

#define DefineTestSuiteFor(class_name) \
    template<> \
    class FriendTest<class_name> { \
    public:

#define EndTestSuite \
    };

#define DefineTest(test_name) \
    void test_name()

#define RunTest(class_name, test_name) \
    TEST(class_name##Tests, test_name) { \
        FriendTest<class_name> test_accessor; \
        test_accessor.test_name(); \
    }
    