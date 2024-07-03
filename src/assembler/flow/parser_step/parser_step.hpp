#pragma once

#include "../assembler_steps.hpp"
#include "../../tokens/parser/parser.hpp"

namespace basilar::assembler::flow {

class ParserStep : public AssemblerStep {
public:
    ParserStep(TokenParser* parser) : __parser(parser) {}
    optional<ParseContext> run(ParseContext ctx, LineSource* source) override;
private:
    TokenParser* __parser;
};

} // namespace basilar::assembler::flow