#pragma once

#include "./assembler_steps.hpp"
#include "./assembler_flow.hpp"
#include "./preprocessor/preprocessor.hpp"
#include "./parser_step/parser_step.hpp"
#include "../tokens/preprocessing_specs.hpp"
#include "./tokenizer/line_reader.hpp"
#include "./token_writer/token_writer.hpp"

using namespace basilar::tokens;
using namespace basilar::tokenizer;

namespace basilar::assembler::flow {

class AssemblerFactory {
public:

    static AssemblerFlow create_preprocessor_flow(string file_source, string file_dest);

};

} // namespace basilar::assembler::flow