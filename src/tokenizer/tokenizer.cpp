#include <string>

#include "tokenizer.hpp"

using namespace std;
namespace basilar::tokenizer {

void Tokenizer::add_line_formatter(Formatter formatter) {
    this->__line_formatters.push_back(formatter);
}

string Tokenizer::__format(string line) {
    auto cp = string(line);
    for (auto formatter : this->__line_formatters) {
        cp = formatter(cp);
    }

    return cp;
}

bool Tokenizer::next_line() {
    auto line = this->__read_next_line();

    if (line.empty()) {
        return false;
    }

    this->__tokenize(line);
    return true;
}

std::string Tokenizer::__read_next_line() {
    auto r = this->__file_content;
    if (this->__current_index >= r.size()) {
        return "\0";
    }

    string line;
    do {
        auto match = r.find_first_of("\n", this->__current_index);
        if (match == string::npos) {
            match = r.size();
        }

        line = r.substr(this->__current_index, match - this->__current_index);
        this->__current_index = match + 1;
        this->__current_line_number++;

        line = this->__format(line);
    } while (line.empty() && this->__current_index < r.size());

    return line;
}

void Tokenizer::__tokenize(std::string line) {
    this->__tokens = queue<Token*>();
    this->__raw_tokens = queue<RawToken>();

    auto pieces = split_line_in_spaces_and_tabs(line);
    for (int i = 0; i < pieces.size(); i++) {
        this->__raw_tokens.push(RawToken {
            .source_line_number = this->__current_line_number,
            .source_line = line,
            .source_column_number = i,
            .value = pieces[i],
        });
    }
}

Token* Tokenizer::next_token() {
    auto token = this->__tokens.front();
    this->__tokens.pop();
    return token;
}

RawToken Tokenizer::next_raw_token() {
    auto raw_token = this->__raw_tokens.front();
    this->__raw_tokens.pop();
    return raw_token;
}

vector<string> split_line_in_spaces_and_tabs(const string& line) {
    auto cp = string(line);
    // Splits token
    vector<string> tokens = {};

    int i = 0;
    while (i < cp.size()) {
        auto match = cp.find_first_of(" \t", i);

        if (match == string::npos) {
            match = cp.size();
        }

        tokens.push_back(cp.substr(i, match - i));
        i = match + 1;
    }

    return tokens;
}

} // namespace basilar::tokenizer