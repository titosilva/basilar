#pragma once

#include "../assembler_steps.hpp"

namespace basilar::assembler::flow {

class TokenWriter : public AssemblerStep {
public:
    TokenWriter(string file_dest) : __file_dest(file_dest) {}

    std::optional<ParseContext> run(ParseContext ctx, LineSource* source) override;
private:
    string __file_dest;
    bool __file_is_clean = false;
};

}  // namespace basilar::assembler::flow