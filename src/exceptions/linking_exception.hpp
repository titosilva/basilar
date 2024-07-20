#pragma once

#include <string>
using namespace std;

namespace basilar::exceptions {

class linking_exception : public exception {
public:
    semantic_exception(string message) : message(message) {}
    string message;

    char const* what() const noexcept override {
        return message.c_str();
    }
};


} // namespace basilar::exceptions