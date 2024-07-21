#pragma once

#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <string>
#include <vector>

#include "../../../friend_test.hpp"
#include "../../tokens/parser/parser.hpp"
#include "../assembler_steps.hpp"
#include "formatter.hpp"

using namespace basilar::assembler::tokens::parser;
using namespace basilar::assembler::flow;

namespace basilar::tokenizer {

class LineReader : public LineSource {
public:
    static LineReader* from_file(std::string file_path);
    LineReader(std::string file_content) : __file_content(file_content), __current_line_number(0), __current_index(0) {}

    void add_line_formatter(Formatter formatter);

    void with_common_formatters() {
        this->add_line_formatter(RemoveComments);
        this->add_line_formatter(Trim);
        this->add_line_formatter(ToLower);
        this->add_line_formatter(UnifyWhitespace);
        this->add_line_formatter(EmptyBlankLines);
        this->add_line_formatter(RemoveEspacesBeforeColon);
    }

    bool next_line() override;
    ParseContext read_current_line() override;
    void set_prefix(std::string prefix) override;

    AllowInternalTestFor(LineReader);

private:
    std::string __read_next_line();
    std::string __format(std::string line);
    std::string __file_content;
    unsigned long __current_line_number;
    unsigned long __current_index;
    std::vector<Formatter> __line_formatters;
    std::string __line;
    std::string __prefix;
};

}  // namespace basilar::tokenizer