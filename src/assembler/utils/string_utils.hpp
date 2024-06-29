#pragma once

#include <string>
#include <utility>

using namespace std;

namespace basilar::utils {

class StringUtils {
public:
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
};

} // namespace basilar