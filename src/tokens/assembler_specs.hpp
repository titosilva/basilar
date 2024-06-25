#pragma once

#include "parser/parser.hpp"

using namespace basilar::tokens::parser;
#define Def static TokenParser
#define As =
#define Else |
#define EndDef

namespace basilar::tokens {
    Def Blank As Ignored(Whitespace);
    Def Close As Hidden(End);

    Def Label As Blank >> RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)", "label") >> Blank;
    Def MalformedLabel As RegexParser(R"(.*:)", "malformed_label");

    Def LabelDef As Label >> ":" >> Blank >> JoinAs("label")
    Else Forbidden(MalformedLabel, "Malformed label definition") >> ButFail;

    Def EquDirectiveLine As
        LabelDef >> "equ" >> Blank
        >> Required(Number, "Expected number after equ directive") >> Blank 
        >> Required(Close, "Too many arguments after equ directive")
    Else Forbidden(Blank >> "equ", "Expected label before equ directive") >> ButFail;

    Def IfDirectiveLine As 
        Optional(LabelDef) >> "if" >> Blank
        >> Required(Label | Number, "Expected label or number after if directive") >> Blank
        >> Required(Close, "Too many arguments after if directive");
    EndDef

    Def PreprocessingLine As EquDirectiveLine | IfDirectiveLine;

    Def AssemblyLine As Blank >> (
        PreprocessingLine
    ) >> Blank;
} // namespace basilar::tokens