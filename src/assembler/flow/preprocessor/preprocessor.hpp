#pragma once

#include "../assembler_steps.hpp"
#include <map> 

namespace basilar::assembler::flow {

class Preprocessor : public AssemblerStep {
public:
    optional<ParseContext> run(ParseContext ctx, LineSource* source) override;
private:
    map<string, string> __definitions;
    optional<ParseContext> __handle_equ(ParseContext ctx, LineSource* source);
    optional<ParseContext> __handle_if(ParseContext ctx, LineSource* source);
    optional<ParseContext> __try_replace_tokens(ParseContext ctx, LineSource* source);
};

} // namespace basilar::assembler::flow