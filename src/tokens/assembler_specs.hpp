#pragma once

#include "parser/parser.hpp"

using namespace basilar::tokens::parser;

namespace basilar::tokens {

const TokenParser Label = RegexParser(R"([a-zA-Z_][a-zA-Z0-9_]*)", "item");
const TokenParser Blank = Ignore(Whitespace);

const TokenParser LabelDef = Blank >> Label >> Blank >> ":" >> JoinAs("label");

const TokenParser EquDirectiveCall = 
    Blank >> "equ" >> Blank
    >> Required(Number, "Expected number after equ directive") 
    >> Blank 
    >> Required(End, "Too many arguments after equ directive");

const TokenParser IfDirectiveCall = 
    Blank >> "if" >> Blank
    >> Required(Label, "Expected label after if directive") 
    >> Blank
    >> Required(End, "Too many arguments after if directive");

const TokenParser PreprocessingLine = 
    Optional(LabelDef) >> (EquDirectiveCall | IfDirectiveCall);

} // namespace basilar::tokens