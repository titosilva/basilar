#pragma once

#include <string>
#include <utility>
#include <regex>

using namespace std;

namespace basilar::utils {

class StringUtils {
public:
    static string lower(string str) {
        string cp = string(str);
        for (auto& c : cp) {
            c = tolower(c);
        }

        return cp;
    }

    static string replace(string str, string from, string to) {
        size_t start_pos = 0;
        auto cp = string(str);

        while((start_pos = cp.find(from, start_pos)) != string::npos) {
            cp.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }

        return cp;
    }

    static bool try_parse_int(string str, int* out, int base = 10) {
        try {
            size_t idx;

            *out = stoi(str, &idx, base);
            if (idx != str.size()) {
                return false;
            }

            return true;
        } catch (...) {
            return false;
        }
    }

    // Source: https://stackoverflow.com/questions/16749069/c-split-string-by-regex
    static std::vector<std::string> resplit(const std::string &s, const std::regex &sep_regex = std::regex{"\\s+"}) {
        std::sregex_token_iterator iter(s.begin(), s.end(), sep_regex, -1);
        std::sregex_token_iterator end;
        return {iter, end};
    }

    static std::string rereplace(const std::string &s, const std::regex &re = std::regex{"\\s+"}, const std::string &replacement = " ") {
        return std::regex_replace(s, re, replacement);
    }
};

} // namespace basilar