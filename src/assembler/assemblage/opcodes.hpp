#pragma once

namespace basilar::assembler::assemblage {

#define WhenIs(mnemonic, instruction) if (mnemonic == instruction)
#define Then(opcode) { return opcode; }
#define Otherwise(opcode) return opcode;

class Opcodes {
public:
    static int get(string mnemonic) {
        WhenIs(mnemonic, "add") Then(1);
        WhenIs(mnemonic, "sub") Then(2);
        WhenIs(mnemonic, "mul") Then(3);
        WhenIs(mnemonic, "div") Then(4);
        WhenIs(mnemonic, "jmp") Then(5);
        WhenIs(mnemonic, "jmpn") Then(6);
        WhenIs(mnemonic, "jmpp") Then(7);
        WhenIs(mnemonic, "jmpz") Then(8);
        WhenIs(mnemonic, "copy") Then(9);
        WhenIs(mnemonic, "load") Then(10);
        WhenIs(mnemonic, "store") Then(11);
        WhenIs(mnemonic, "input") Then(12);
        WhenIs(mnemonic, "output") Then(13);
        WhenIs(mnemonic, "stop") Then(14);
        Otherwise(-1);
    }
};

} // namespace basilar::assembler::assemblage