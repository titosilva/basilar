#pragma once

#include <string>
using namespace std;

namespace basilar::exceptions {

class lexycal_exception : public exception {
public:
    lexycal_exception(string message) : message(message) {}
    lexycal_exception(string message, int line) : message("Line " + to_string(line) + ": " + message) {}
    string message;

    char const* what() const noexcept override {
        return message.c_str();
    }
};


} // namespace basilar::exceptions