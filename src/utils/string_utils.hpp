#pragma once

#include <string>
#include <utility>
#include <regex>

using namespace std;

class StringUtils {
public:
    static bool has(string str, string to_find) {
        auto r = str.find(to_find);
        return r != string::npos;
    }

    static vector<string> split(string str, string to_split) {
        auto r = vector<string>();

        auto bstr = string(str);
        size_t pos = 0;
        do {
            bstr = bstr.substr(pos);
            pos = bstr.find(to_split);
            r.push_back(bstr.substr(0, pos));
        } while (pos != string::npos);

        return r;
    }

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

    static bool try_parse_int(string str, int* out, int base) {
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

    static bool try_parse_int(string str, int* out) {
        if (try_parse_int(str, out, 10)) {
            return true;
        }

        if (try_parse_int(str, out, 16)) {
            return true;
        }

        if (lower(str.substr(0, 2)) == "0x" && try_parse_int(str.substr(2), out, 16)) {
            return true;
        }

        return false;
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
