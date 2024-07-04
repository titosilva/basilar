#include <string>
#include <fstream>

// TODO: Remove this
#include <iostream>

#include "line_reader.hpp"

using namespace std;
namespace basilar::tokenizer {

LineReader* LineReader::from_file(string file_path) {
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

    file.close();
    return new LineReader(content);
}

void LineReader::add_line_formatter(Formatter formatter) {
    this->__line_formatters.push_back(formatter);
}

string LineReader::__format(string line) {
    auto cp = string(line);
    for (auto formatter : this->__line_formatters) {
        cp = formatter(cp);
    }

    return cp;
}

bool LineReader::next_line() {
    auto line = this->__read_next_line();

    if (line.empty()) {
        return false;
    }

    this->__line = line;
    return true;
}

std::string LineReader::__read_next_line() {
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

        cout << "Line: " << line << endl;
        line = this->__format(line);
    } while (line.empty() && this->__current_index < r.size());

    return line;
}

ParseContext LineReader::read_current_line() {
    // TODO: Remove this
    cout << "Current line: " << this->__line << endl;
    return ParseContext(this->__line);
}

} // namespace basilar::tokenizer