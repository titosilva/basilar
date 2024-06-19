#pragma once

#include <string>
#include <functional>
#include <regex>

using namespace std;

namespace basilar::tokenizer {
    typedef std::function<std::string(std::string)> Formatter;

    const Formatter Trim = [](string line) -> string {
        return regex_replace(line, regex("^\\s+|\\s+$"), "");
    };

    const Formatter ToLower = [](string line) -> string { 
        string s;

        for (auto c : line) {
            s += tolower(c);
        }

        return s;
    };

    const Formatter UnifyWhitespace = [](string line) -> string {
        return regex_replace(line, regex("\\s+"), " ");
    };

    const Formatter RemoveComments = [](string line) -> string {
        return regex_replace(line, regex(";.*"), "");
    };

    const Formatter EmptyBlankLines = [](string line) -> string {
        return regex_replace(line, regex("^\\s*$"), "");
    };

    const Formatter RemoveEspacesBeforeColon = [](string line) -> string {
        return regex_replace(line, regex("\\s+:"), ":");
    }; 
} // namespace basilar::tokens
