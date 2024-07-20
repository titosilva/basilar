#pragma once

#include "common_specs.hpp"

using namespace basilar::assembler::tokens::parser;

namespace basilar::tokens {
    #define DefineInstruction(name, args) \
        DefParser(name##Call, \
            #name >> Args(args, "Invalid arguments for "#name" instruction") \
        ) Then Note("instruction_call", #name) \
        Else Forbid(OptSpace >> #name >> SpaceOrClose, "Expected arguments for "#name" instruction") Then Fail \
        EndDef

    #define DefineInstructionWithoutArgs(name) \
        DefParser(name##Call, \
            #name >> EndLine \
        ) Then Note("instruction_call", #name) \
        Else Forbid(OptSpace >> #name >> SpaceOrClose, "Unexpected arguments for "#name" instruction") Then Fail \
        EndDef

    DefineInstruction(add, Label)
    DefineInstruction(sub, Label)
    DefineInstruction(mul, Label)
    DefineInstruction(div, Label)
    DefineInstruction(jmp, Label)
    DefineInstruction(jmpn, Label)
    DefineInstruction(jmpp, Label)
    DefineInstruction(jmpz, Label)
    // TODO: check if copy is correct
    DefineInstruction(copy, Label >> Hidden(Literal(",")) >> Label)
    DefineInstruction(load, Label)
    DefineInstruction(store, Label)
    DefineInstruction(input, Label)
    DefineInstruction(output, Label)
    DefineInstructionWithoutArgs(stop)

    DefParser(InstructionCall,
        addCall
        | subCall
        | mulCall
        | divCall
        | jmpCall
        | jmpnCall
        | jmppCall
        | jmpzCall
        | copyCall
        | loadCall
        | storeCall
        | inputCall
        | outputCall
        | stopCall
    )
    EndDef

    DefLine(InstructionLine, 
        Optional(LabelDef) >> InstructionCall
    )
    EndDef

    DefParser(spaceDirectiveCall, 
        LabelDef >> (
            ("space" >> OptSpace >> Close)
            | ("space" >> Args(Integer, "Expected integer after space directive"))
        )
    ) Then Note("directive_call", "space")
    Else Forbid(OptSpace >> "space", "Expected label definition in space directive") Then Fail
    EndDef

    DefParser(constDirectiveCall, 
        LabelDef >>
        "const" >> Args(Integer, "Expected number after const directive")
    ) Then Note("directive_call", "const")
    Else Forbid(OptSpace >> "const", "Expected label definition in const directive") Then Fail
    EndDef

    DefParser(externDirectiveCall, 
        LabelDef >>
        "extern" >> EndLine
    ) Then Note("directive_call", "extern")
    Else Forbid(OptSpace >> "extern", "Expected label definition in extern directive") Then Fail
    EndDef

    DefParser(beginDirectiveCall, 
        Optional(LabelDef) >>
        "begin" >> EndLine
    ) Then Note("directive_call", "begin")
    Else Forbid(OptSpace >> "begin", "Invalid begin directive") Then Fail
    EndDef

    DefParser(endDirectiveCall, 
        "end" >> EndLine
    ) Then Note("directive_call", "end")
    Else Forbid(OptSpace >> "end", "Invalid end directive") Then Fail
    EndDef

    DefParser(publicDirectiveCall, 
        Optional(LabelDef) >>
        "public" >> Args(Label, "Expected label after begin directive")
    ) Then Note("directive_call", "public")
    Else Forbid(OptSpace >> "public", "Invalid begin directive") Then Fail
    EndDef

    DefLine(DirectiveLine, 
        spaceDirectiveCall
        | constDirectiveCall
        | externDirectiveCall
        | beginDirectiveCall
        | endDirectiveCall
        | publicDirectiveCall
    )
    EndDef

    Def AssemblerParser As InstructionLine | DirectiveLine
    Else Forbid(EndLine, "Expected instruction or directive") Then Fail
    EndDef

} // namespace basilar::tokens