#pragma once

#include <string>

using namespace std;

namespace basilar::tokens::parser {

class Token {
public:
    Token(string type, string value) : value(value) {
        string s;

        for (auto c : type) {
            s += tolower(c);
        }

        this->type = s;
    }

    string type;
    string value;
};

} // namespace basilar::tokens::parser