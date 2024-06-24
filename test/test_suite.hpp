#pragma once
#include "../src/friend_test.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace std;

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

#define DefineGlobalTestSuiteFor(class_name) \
    class class_name##Tests { \
    public:

#define EndGlobalTestSuite \
    };

#define DefineGlobalTest(test_name) \
    void test_name()

#define RunGlobalTest(class_name, test_name) \
    TEST(class_name##Tests, test_name) { \
        class_name##Tests test_accessor; \
        test_accessor.test_name(); \
    }
    
class TestLogger {
public:
    static void log(const std::string& message) {
        std::cout << message << std::endl;
    }
};
