#pragma once

#include "../../assemblage/byte_counter.hpp"
#include "../assembler_steps.hpp"

using namespace basilar::assembler::assemblage;

namespace basilar::assembler::flow {

class ByteCountingStep : public AssemblerStep {
public:
    ByteCountingStep(string file_dest) : __file_dest(file_dest) {}
    optional<ParseContext> run(ParseContext ctx, LineSource* source) override;
private:
    ByteCounter __byte_counter;
    string __file_dest;
};

} // namespace basilar::assembler::flow