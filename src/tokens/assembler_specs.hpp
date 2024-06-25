#pragma once

#include "parser/parser.hpp"

using namespace basilar::tokens::parser;
#define Def static TokenParser
#define As =
#define Else |
#define EndDef ;
#define Then >>

namespace basilar::tokens {
    Def OptSpace As Hidden(Optional(Whitespace));
    Def Space As Hidden(Require(Whitespace, "Expected empty space"));
    Def Close As OptSpace >> Hidden(End);
    Def EndArgs As Require(Close, "Expected end of arguments");

    Def Label As OptSpace >> RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)", "label") >> OptSpace;
    Def MalformedLabel As RegexParser(R"(.*:)", "malformed_label");

    Def LabelDef As OptSpace 
        >> Label >> OptSpace >> ":" >> OptSpace
    Then JoinAs("label")
    Else Forbid(MalformedLabel, "Malformed label definition") Then Fail
    EndDef

    Def EquDirectiveLine As OptSpace
        >> LabelDef >> OptSpace
        >> "equ" >> Space
        >> Require(Number, "Expected number after equ directive")
    Then EndArgs
    Else Forbid(OptSpace >> "equ", "Expected label before equ directive") Then Fail
    EndDef

    Def IfDirectiveLine As OptSpace
        >> Optional(LabelDef) >> OptSpace
        >> "if" >> Space
        >> Require(Label | Number, "Expected label or number after if directive")
    Then EndArgs
    EndDef

    Def PreprocessingLine As EquDirectiveLine | IfDirectiveLine;

    Def AssemblyLine As OptSpace >> (
        PreprocessingLine
    ) >> OptSpace;
} // namespace basilar::tokens