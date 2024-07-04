#pragma once
#include "../src/friend_test.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>

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

class TestData {
public:
    static string get_data_file_path(string file_name) {
        auto test_file = filesystem::path(__FILE__);
        test_file = test_file.parent_path() / "data" / file_name;
        return test_file.string();
    }

    static string get_data_file_content(string file_name) {
        auto file_path = get_data_file_path(file_name);
        ifstream file(file_path);
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return content;
    }
}
