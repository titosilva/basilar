#pragma once

#include "parser/parser.hpp"

using namespace basilar::tokens::parser;

namespace basilar::tokens {

const TokenParser Label = RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)", "item");
const TokenParser Blank = Ignore(Whitespace);

const TokenParser LabelDef = Blank >> Label >> Blank >> ":" >> JoinAs("label");

const TokenParser EquDirective = 
    Blank >> "equ" >> Blank
    >> Required(Number, "Expected number after equ directive") 
    >> Blank 
    >> Required(End, "Too many arguments after equ directive")
    >> JoinAs("equ");

const TokenParser IfDirective = 
    Blank >> "if" >> Blank
    >> Required(Label, "Expected item after if directive") 
    >> Blank
    >> Required(End, "Too many arguments after if directive")
    >> JoinAs("if");

const TokenParser PreprocessingLine = 
    Optional(LabelDef) >> (EquDirective | IfDirective)

} // namespace basilar::tokens