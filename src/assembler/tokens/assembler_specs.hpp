#pragma once

#include "parser/parser.hpp"

using namespace basilar::assembler::tokens::parser;
#define Def static TokenParser
#define As =
#define Else |
#define EndDef ;
#define Then >>

#define DefParser(name, parser) Def name As OptSpace Then parser Then OptSpace
#define DefType(type, parser) Def type As OptSpace Then JoinWithType(parser, #type) Then OptSpace
#define DefLine(name, parser) Def name As OptSpace Then parser Then OptSpace >> Require(Close, "Expected end of line")

namespace basilar::tokens {
    Def Space As Hidden(Whitespace);
    Def OptSpace As Optional(Space);
    Def Close As Hidden(End);
    Def SpaceOrClose As Space | Close;
    Def EndLine As OptSpace >> Require(Close, "Expected end of line");

    const ParserMod<string> Args = [](TokenParser parser, string error) -> TokenParser {
        return Space >> Require(parser, error) >> EndLine
        Else Forbid(OptSpace >> Close, error) Then Fail;
    };

    DefType(Integer, (HexNumber | Number) >> SpaceOrClose)
    Else Forbid(Literal("0x") << NotWhitespace, "Invalid hex number format") Then Fail
    EndDef

    DefType(Label, RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)"))
    EndDef

    DefType(LabelDef, Label >> ":")
    Then Forbid(RegexParser(R"(.*:)"), "Double label definition")
    Else Forbid(RegexParser(R"(.*:)"), "Malformed label definition") Then Fail
    EndDef

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

    Def PreprocessingLine As EquDirectiveLine | IfDirectiveLine;

    Def AssemblyLine As OptSpace >> (
        PreprocessingLine
    ) >> OptSpace;
} // namespace basilar::tokens