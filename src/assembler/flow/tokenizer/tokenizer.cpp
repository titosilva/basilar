#include <string>
#include <fstream>

#include "tokenizer.hpp"

using namespace std;
namespace basilar::tokenizer {

Tokenizer* Tokenizer::from_file(string file_path) {
    auto file = ifstream(file_path);

    if (!file.good()) {
        throw runtime_error("Failed to open file");
    }
    
    string content;
    while (file.good()) {
        string line;
        getline(file, line);
        content += line + "\n";
    }

    return new Tokenizer(content);
}

void Tokenizer::add_line_formatter(Formatter formatter) {
    this->__line_formatters.push_back(formatter);
}

void Tokenizer::with_parser(TokenParser parser) {
    this->__parser = parser;
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

    this->__line = line;
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

ParseContext Tokenizer::parse_current_line() {
    return this->__parse(this->__line);
}

ParseContext Tokenizer::__parse(std::string line) {
    auto ctx = this->__parser.parse(line);

    if (!ctx.has_value()) {
        throw new runtime_error("Failed to parse line");
    }

    return ctx.value();
}

} // namespace basilar::tokenizer