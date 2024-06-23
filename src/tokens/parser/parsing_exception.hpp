#pragma once

#include <string>

using namespace std;

namespace basilar::tokens::parser {

class ParsingException : public exception {
public:
    ParsingException(string message) : message(message) {}
    string message;

    char const* what() const noexcept override {
        return message.c_str();
    }
};

} // namespace basilar::tokens::parser