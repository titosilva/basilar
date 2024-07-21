#pragma once

#include "parser/parser.hpp"
#include "spec_base.hpp"

using namespace basilar::assembler::tokens::parser;

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

    DefType(LabelWithDisplacement, 
        Label >> OptSpace >> "+" >> OptSpace >> Integer
    )
    EndDef

    Def Expression As LabelWithDisplacement | Label;

    DefType(LabelDef, Label >> ":") Then Note("has_label", "true")
    Then Forbid(RegexParser(R"(.*:)"), "Double label definition")
    Else Forbid(RegexParser(R"(.*:)"), "Malformed label definition") Then Fail
    EndDef
} // namespace basilar::tokens