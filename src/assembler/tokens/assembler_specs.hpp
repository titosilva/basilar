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

    DefLine(SpaceDirectiveLine, 
        "space" >> Args(Integer, "Expected integer after space directive")
        | "space" >> EndLine
    ) Then Note("directive_call", "space")
    Else Forbid(OptSpace >> "space", "Expected space directive") Then Fail
    EndDef

    DefLine(ConstDirectiveLine, 
        "const" >> Args(Integer, "Expected number after const directive")
    ) Then Note("directive_call", "const")
    Else Forbid(OptSpace >> "const", "Expected const directive") Then Fail
    EndDef

    DefLine(DirectiveLine, 
        SpaceDirectiveLine
        | ConstDirectiveLine
    )
    EndDef

    DefLine(AssemblerLine, 
        InstructionLine
        | DirectiveLine
    ) Else Forbid(EndLine, "Expected instruction or directive") Then Fail
    EndDef

} // namespace basilar::tokens