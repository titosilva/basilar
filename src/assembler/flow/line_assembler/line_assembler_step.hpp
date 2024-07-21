#pragma once

#include "../../assemblage/line_handler.hpp"
#include "../assembler_steps.hpp"

using namespace basilar::assembler::assemblage;

namespace basilar::assembler::flow {

class LineAssemblerStep : public AssemblerStep {
public:
    LineAssemblerStep(string file_dest) : __file_dest(file_dest) {}
    optional<ParseContext> run(ParseContext ctx, LineSource* source) override;

    void write_object_file();
    void write_debug_file();
    void check_consistency();
private:
    LineHandler __line_handler;
    string __file_dest;
};

} // namespace basilar::assembler::flow