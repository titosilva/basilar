#pragma once

#include <string>

using namespace std;

namespace basilar::assembler::assemblage {

class AssemblageException : public exception {
public:
    AssemblageException(string message) : message(message) {}
    string message;

    char const* what() const noexcept override {
        return message.c_str();
    }
};

} // namespace basilar::assembler::assemblage