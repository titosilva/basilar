#pragma once

#include <string>
#include <functional>
#include <regex>

using namespace std;

namespace basilar::tokenizer {
    typedef std::function<std::string(std::string)> Preprocessor;

    const Preprocessor Trim = [](string line) -> string {
        return regex_replace(line, regex("^\\s+|\\s+$"), "");
    };

    const Preprocessor ToLower = [](string line) -> string { 
        string s;

        for (auto c : line) {
            s += tolower(c);
        }

        return s;
    };

    const Preprocessor UnifyWhitespace = [](string line) -> string {
        return regex_replace(line, regex("\\s+"), " ");
    };
} // namespace basilar::tokens
