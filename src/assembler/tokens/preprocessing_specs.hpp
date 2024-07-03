#pragma once

#include "common_specs.hpp"

using namespace basilar::assembler::tokens::parser;

namespace basilar::tokens {
    DefLine(EquDirectiveLine, 
        LabelDef 
        >> "equ"
        >> Args(Integer, "Expected number after equ directive")
    )
    Else Forbid(OptSpace >> "equ", "Expected label before equ directive") Then Fail
    EndDef

    DefLine(IfDirectiveLine, 
        Optional(LabelDef) 
        >> "if"
        >> Args(Label | Integer, "Expected label or number after if directive"))
    EndDef

    Def PreprocessingParser As EquDirectiveLine | IfDirectiveLine;
} // namespace basilar::tokens