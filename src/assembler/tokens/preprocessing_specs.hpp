#pragma once

#include "common_specs.hpp"

using namespace basilar::assembler::tokens::parser;

namespace basilar::tokens {
    DefLine(EquDirectiveLine, 
        LabelDef 
        >> "equ"
        >> Args(NotWhitespace, "Expected non-whitespace argument after equ directive")
    ) Then Note("is_equ", "true")
    Else Forbid(OptSpace >> "equ", "Expected label before equ directive") Then Fail
    EndDef

    DefLine(IfDirectiveLine, 
        "if" >> Args(Label | Integer, "Expected label or number after if directive")
    ) Then Note("is_if", "true")
    EndDef

    Def PreprocessingParser As EquDirectiveLine | IfDirectiveLine;
} // namespace basilar::tokens