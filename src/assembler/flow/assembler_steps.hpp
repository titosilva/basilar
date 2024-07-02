#pragma once

#include "../tokens/parser/parser.hpp"
#include <utility>
#include <optional>

using namespace basilar::assembler::tokens::parser;
using namespace std;

namespace basilar::assembler::flow {

class AssemblerSource {
public:
    virtual ParseContext parse_current_line() = 0;
    virtual bool next_line() = 0;
};

class AssemblerStep {
public:
    virtual optional<ParseContext> run(ParseContext ctx, AssemblerSource* source) const = 0;
};

} // namespace basilar::assembler::flow