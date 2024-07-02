#pragma once

#include "assembler_steps.hpp"

namespace basilar::assembler::flow {

class AssemblerFlow {
public:
    AssemblerFlow(AssemblerSource* source) : __source(source) {}

    AssemblerFlow add_step(AssemblerStep* step);
    void run();

private:
    AssemblerSource* __source;
    vector<AssemblerStep*> __steps;
};

} // namespace basilar::assembler::flow