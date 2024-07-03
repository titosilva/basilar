#pragma once

#include "../assembler_steps.hpp"
#include "../assembler_flow.hpp"
#include "../preprocessor/preprocessor.hpp"
#include "../parser_step/parser_step.hpp"
#include "../../tokens/preprocessing_specs.hpp"

using namespace basilar::tokens;

namespace basilar::assembler::flow {

AssemblerFlow create_preprocessor_flow(LineSource* source) {
    AssemblerFlow flow(source);

    flow.add_step(new ParserStep(PreprocessingParser));
    flow.add_step(new Preprocessor());

    return flow;
}

} // namespace basilar::assembler::flow