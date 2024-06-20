#pragma once

#include <string>
#include <utility>

using namespace std;

namespace basilar::tokens {

struct RawToken {
    int source_line_number;
    string source_line;
    int source_column_number;
    string value;
};

class Token {
public:
    Token(RawToken raw) {
        _source_line = pair<int, string>(raw.source_line_number, raw.source_line);
        _source_column = pair<int, string>(raw.source_column_number, raw.value);
        this->raw = raw;
    }

    virtual string get_type_name() = 0;
    virtual string get_value() = 0;

    pair<int, string> get_source_line() {
        return pair<int, string>(_source_line);
    }

    pair<int, string> get_source_column() {
        return pair<int, string>(_source_column);
    }
protected:
    pair<int, string> _source_line;
    pair<int, string> _source_column;
    RawToken raw;
};

// SHOULD NEVER BE USED
// Only used for initializing token references
class DummyToken : public Token {
public:
    DummyToken() : Token({0, "", 0, ""}) {}

    string get_type_name() { throw "Not implemented"; }
    string get_value() { throw "Not implemented"; }
};

} // namespace basilar::tokens