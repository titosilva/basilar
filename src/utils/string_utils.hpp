#pragma once

#include <string>

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
};

} // namespace basilar