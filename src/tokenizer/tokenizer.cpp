#include <string>

#include "tokenizer.hpp"
#include "token.hpp"

using namespace std;
namespace basilar::tokens {

void Tokenizer::add_line_preprocessor(Preprocessor preprocessor) {
    this->__line_preprocessors.push_back(preprocessor);
}

string Tokenizer::__preprocess(string line) {
    auto cp = string(line);
    for (auto preprocessor : this->__line_preprocessors) {
        cp = preprocessor(cp);
    }

    return cp;
}

bool Tokenizer::next_line() {
    auto line = this->__read_next_line();

    if (line == "\0") {
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

    auto match = r.find_first_of("\n", this->__current_index);
    if (match == string::npos) {
        match = r.size();
    }

    auto line = r.substr(this->__current_index, match - this->__current_index);
    this->__current_index = match + 1;
    this->__current_line_number++;
    return this->__preprocess(line);
}

void Tokenizer::__tokenize(std::string line) {
    this->__tokens = queue<Token>();

    auto tokens = split_line_in_spaces_and_tabs(line);
    for (auto token : tokens) {
        auto t = Token(
            TokenType::LABEL,
            token,
            line,
            this->__current_line_number
        );

        this->__tokens.push(t);
    }
}

Token Tokenizer::next_token() {
    auto token = this->__tokens.front();
    this->__tokens.pop();
    return token;
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

} // namespace basilar::tokens