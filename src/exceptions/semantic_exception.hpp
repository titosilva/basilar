#pragma once

#include <string>
using namespace std;

namespace basilar::exceptions {

class semantic_exception : public exception {
public:
    semantic_exception(string message) : message(message) {}
    semantic_exception(string message, int line) : message("Semantic error at line " + to_string(line) + ": " + message) {}
    string message;

    char const* what() const noexcept override {
        return message.c_str();
    }

    string get_message() const {
        return message;
    }
};


} // namespace basilar::exceptions