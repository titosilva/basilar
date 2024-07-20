#include "object_reader.hpp"

#include <optional>
#include <string>
#include <utility>
#include <vector>
using namespace std;

namespace basilar::linker {

void skip_spaces(string source, int& index) {
    while (source[index] == ' ' || source[index] == '\t') {
        index++;
    }
}

void skip_blank_lines(string source, int& index) {
    while (source[index] == '\n' || source[index] == '\r') {
        skip_spaces(source, index);
        index++;
    }
}

bool skip_if(string source, int& index, string expected) {
    skip_spaces(source, index);

    if (source.substr(index, expected.size()) != expected) {
        return false;
    }

    index += expected.size();
    return true;
}

string read_line(string source, int& index) {
    string line = "";

    while (source[index] != '\n' && source[index] != '\r') {
        line += source[index];
        index++;
    }

    return line;
}

string read_token(string source, int& index) {
    skip_spaces(source, index);

    string token = "";
    while (source[index] != ' ' && source[index] != '\t' && source[index] != '\n' && source[index] != '\r') {
        token += source[index];
        index++;
    }

    return token;
}

optional<pair<string, int>> read_symbol(string source, int& index) {
    skip_spaces(source, index);
    string symbol = read_token(source, index);

    if (symbol.empty()) {
        return nullopt;
    }

    skip_spaces(source, index);
    string value = read_token(source, index);

    if (value.empty()) {
        return nullopt;
    }

    return make_pair(symbol, stoi(value));
}

ObjectsBuilder ObjectsReader::read() {
    skip_blank_lines(__source, __current_index);
    if (skip_if(__source, __current_index, "USO")) {
        skip_blank_lines(__source, __current_index);
        while (auto symbol = read_symbol(__source, __current_index), symbol.has_value()) {
            __objects_builder.add_reference(symbol->first, symbol->second);
        }
    }

    skip_blank_lines(__source, __current_index);
    if (skip_if(__source, __current_index, "DEF")) {
        skip_blank_lines(__source, __current_index);
        while (auto symbol = read_symbol(__source, __current_index), symbol.has_value()) {
            __objects_builder.add_definition(symbol->first, symbol->second);
        }
    }

    skip_blank_lines(__source, __current_index);
    vector<bool> relatives;
    if (skip_if(__source, __current_index, "REAL")) {
        skip_blank_lines(__source, __current_index);
        while (__source[__current_index] != '\n' && __source[__current_index] != '\r') {
            auto c = __source[__current_index];
            relatives.push_back(c == '1');
            __current_index++;
        }
    }

    skip_blank_lines(__source, __current_index);
    int current_index = 0;
    while (__source[__current_index] != '\n' && __source[__current_index] != '\r') {
        string value = read_token(__source, __current_index);
        auto value = stoi(value);

        if (relatives[current_index]) {
            __objects_builder.relative(value);
        } else {
            __objects_builder.absolute(value);
        }

        skip_spaces(__source, __current_index);
    }

    return __objects_builder;
}

} // namespace basilar::linker