#pragma once

#include "../assembler_steps.hpp"
#include <map> 

namespace basilar::assembler::flow {

class Preprocessor : public AssemblerStep {
public:
    optional<ParseContext> run(ParseContext ctx, LineSource* source) override;
private:
    map<string, string> __definitions;
};

} // namespace basilar::assembler::flow