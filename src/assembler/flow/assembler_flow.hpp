#pragma once

#include "assembler_steps.hpp"

namespace basilar::assembler::flow {

class AssemblerFlow {
public:
    AssemblerFlow(LineSource* source) : __source(source) {}

    AssemblerFlow add_step(AssemblerStep* step);
    AssemblerFlow add_post_step(AssemblerPostStep* step);

    void run();
private:
    LineSource* __source;
    vector<AssemblerStep*> __steps;
    vector<AssemblerPostStep*> __post_steps;
};

} // namespace basilar::assembler::flow