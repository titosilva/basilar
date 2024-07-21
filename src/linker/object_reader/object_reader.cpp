#include "object_reader.hpp"
#include "../../utils/logger.hpp"
#include "../../utils/string_utils.hpp"

#include <optional>
#include <string>
#include <utility>
#include <vector>
using namespace std;

namespace basilar::linker {

void skip_spaces(string source, int* index) {
    while (source[*index] == ' ' || source[*index] == '\t') {
        *index = *index + 1;
    }
}

void skip_blank_lines(string source, int* index) {
    while (source[*index] == '\n' || source[*index] == '\r') {
        *index = *index + 1;
        skip_spaces(source, index);
    }
}

bool skip_if(string source, int* index, string expected) {
    skip_spaces(source, index);

    if (source.substr(*index, expected.size()) != expected) {
        return false;
    }

    *index += expected.size();
    return true;
}

string read_line(string source, int* index) {
    string line = "";

    while (source[*index] != '\n' && source[*index] != '\r') {
        line += source[*index];
        *index = *index + 1;
    }

    return line;
}

string read_token(string source, int* index) {
    skip_spaces(source, index);

    string token = "";
    while (source[*index] != ' ' && source[*index] != '\t' && source[*index] != '\n' && source[*index] != '\r') {
        token += source[*index];
        *index = *index + 1;
    }

    return token;
}

optional<pair<string, int>> read_symbol(string source, int* index) {
    auto original = *index;
    skip_spaces(source, index);
    string symbol = read_token(source, index);

    if (symbol.empty()) {
        return nullopt;
    }

    skip_spaces(source, index);
    string value = read_token(source, index);

    if (value.empty()) {
        *index = original;
        return nullopt;
    }

    return make_pair(symbol, StringUtils::parse_int(value));
}

ObjectsBuilder ObjectsReader::read() {
    skip_blank_lines(__source, &__current_index);
    LOG_DEBUG("Reading object file");

    if (skip_if(__source, &__current_index, "USO")) {
        LOG_DEBUG("Reading USO...");

        int entries_count = 0;
        skip_blank_lines(__source, &__current_index);
        while (auto symbol = read_symbol(__source, &__current_index)) {
            __objects_builder.add_reference(symbol->first, symbol->second);
            entries_count++;
            skip_blank_lines(__source, &__current_index);
        }

        LOG_DEBUG("USO entries count: " + to_string(entries_count));
        skip_blank_lines(__source, &__current_index);
    }

    skip_blank_lines(__source, &__current_index);
    if (skip_if(__source, &__current_index, "DEF")) {
        LOG_DEBUG("Reading DEF...");

        int entries_count = 0;
        skip_blank_lines(__source, &__current_index);
        while (auto symbol = read_symbol(__source, &__current_index)) {
            __objects_builder.add_definition(symbol->first, symbol->second);
            entries_count++;
            skip_blank_lines(__source, &__current_index);
        }

        LOG_DEBUG("DEF entries count: " + to_string(entries_count));
        skip_blank_lines(__source, &__current_index);
    }

    skip_blank_lines(__source, &__current_index);
    vector<bool> relatives;
    if (skip_if(__source, &__current_index, "REAL")) {
        LOG_DEBUG("Reading REAL...");

        int entries_count = 0;
        skip_blank_lines(__source, &__current_index);
        while (__source[__current_index] != '\n' && __source[__current_index] != '\r') {
            auto c = __source[__current_index];
            relatives.push_back(c == '1');
            __current_index++;
            entries_count++;
        }

        LOG_DEBUG("REAL entries count: " + to_string(entries_count));
        skip_blank_lines(__source, &__current_index);
    }

    LOG_DEBUG("Reading memory entries...");
    skip_blank_lines(__source, &__current_index);
    while (__source[__current_index] != '\n' && __source[__current_index] != '\r') {
        if (__source[__current_index] == '\0' || __current_index >= __source.size()) {
            break;
        }

        skip_spaces(__source, &__current_index);
        string valueStr = read_token(__source, &__current_index);
        auto value = StringUtils::parse_int(valueStr);

        if (relatives[__objects_builder.get_current_address()]) {
            __objects_builder.relative(value);
        } else {
            __objects_builder.absolute(value);
        }

        skip_spaces(__source, &__current_index);
    }

    return __objects_builder;
}

} // namespace basilar::linker