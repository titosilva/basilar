#include <string>

#include "tokenizer.hpp"
#include "token.hpp"

using namespace std;
namespace basilar::tokens {

vector<Token> Tokenizer::get_tokens() const {
    return vector<Token>(this->tokens);
}

void Tokenizer::add_line_preprocessor(Preprocessor preprocessor) {
    this->line_preprocessors.push_back(preprocessor);
}

string Tokenizer::__preprocess(const string& line) {
    auto cp = string(line);
    for (auto preprocessor : this->line_preprocessors) {
        cp = preprocessor(cp);
    }

    return cp;
}

std::string Tokenizer::next_line() {
    auto r = this->file_content;
    if (this->current_index >= r.size()) {
        return "";
    }

    auto match = r.find_first_of("\n", this->current_index);
    if (match == string::npos) {
        auto line = r.substr(this->current_index, r.size() - this->current_index);
        this->current_index = r.size();
        this->current_line++;
        return this->__preprocess(line);
    }

    auto line = r.substr(this->current_index, match - this->current_index);
    this->current_index = match + 1;
    this->current_line++;
    return this->__preprocess(line);
}

void Tokenizer::__tokenize(const std::string& line) {
    auto cp = string(line);
    for (auto preprocessor : this->line_preprocessors) {
        cp = preprocessor(cp);
    }

    this->tokens = {};
}

vector<string> split_line_in_spaces_and_tabs(const string& line) {
    auto cp = string(line);
    // Splits token
    vector<string> tokens = {};

    int i = 0;
    for (;i < cp.size();) {
        auto match = cp.find_first_of(" \t", i);

        if (match == string::npos) {
            tokens.push_back(cp.substr(i, cp.size() - i));
            break;
        }

        tokens.push_back(cp.substr(i, match - i));
        i = match + 1;
    }

    return tokens;
}

} // namespace basilar::tokens