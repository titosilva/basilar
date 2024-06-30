#pragma once

#include "parser/parser.hpp"

using namespace basilar::tokens::parser;
#define Def static TokenParser
#define As =
#define Else |
#define EndDef ;
#define Then >>

#define DefParser(name, parser) Def name As OptSpace Then parser Then OptSpace
#define DefType(type, parser) Def type As OptSpace Then JoinWithType(parser, #type) Then OptSpace

namespace basilar::tokens {
    Def Space As Hidden(Whitespace);
    Def OptSpace As Optional(Space);
    Def Close As Hidden(End);
    Def SpaceOrClose As Space | Close;
    Def EndArgs As OptSpace >> Require(Close, "Expected end of arguments");

    DefType(Integer, (HexNumber | Number) >> SpaceOrClose)
    Else Forbid(Literal("0x") << NotWhitespace, "Invalid hex number format") Then Fail
    EndDef

    DefParser(Label, RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)", "label"))
    EndDef

    DefType(LabelDef, Label >> ":")
    Then Forbid(RegexParser(R"(.*:)"), "Double label definition")
    Else Forbid(RegexParser(R"(.*:)"), "Malformed label definition") Then Fail
    EndDef

    Def EquDirectiveLine As OptSpace
        >> LabelDef >> OptSpace
        >> "equ"
        >> Require(Space >> Integer, "Expected number after equ directive")
    Then EndArgs
    Else Forbid(OptSpace >> "equ", "Expected label before equ directive") Then Fail
    EndDef

    Def IfDirectiveLine As OptSpace
        >> Optional(LabelDef) >> OptSpace
        >> "if"
        >> Require(Space >> (Label | Integer), "Expected label or number after if directive")
    Then EndArgs
    EndDef

    Def PreprocessingLine As EquDirectiveLine | IfDirectiveLine;

    Def AssemblyLine As OptSpace >> (
        PreprocessingLine
    ) >> OptSpace;
} // namespace basilar::tokens