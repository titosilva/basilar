#pragma once

#include "../tokens/parser/parser.hpp"
#include <utility>
#include <optional>

using namespace basilar::assembler::tokens::parser;
using namespace std;

namespace basilar::assembler::flow {

class LineSource {
public:
    virtual ParseContext read_current_line() = 0;
    virtual bool next_line() = 0;
};

class AssemblerStep {
public:
    virtual optional<ParseContext> run(ParseContext ctx, LineSource* source) = 0;
};

class AssemblerPostStep {
public:
    virtual void run() = 0;
};

} // namespace basilar::assembler::flow