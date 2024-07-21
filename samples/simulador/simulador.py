from sys import argv

# OPCODES
ADD = 1
SUB = 2
MUL = 3
DIV = 4
JMP = 5
JMPN = 6
JMPP = 7
JMPZ = 8
COPY = 9
LOAD = 10
STORE = 11
INPUT = 12
OUTPUT = 13
STOP = 14

if __name__ == "__main__":
    program = []

    # Read the program data and load into an array
    with open(argv[1], "r") as f:
        data = f.read()
        program = [int(x) for x in data.split()]
    
    # Execute the program
    pc = 0
    acc = 0
    while pc < len(program):
        opcode = program[pc]
        print("\n>> PC:", pc, "Opcode:", opcode, "ACC:", acc)

        if opcode == ADD:
            operand1 = program[pc + 1]
            value = program[operand1]
            print(f"Adding value {value} from address {operand1} to accumulator")
            acc += value
            pc += 2
        elif opcode == SUB:
            operand1 = program[pc + 1]
            print(f"Subtracting value {program[operand1]} from address {operand1} from accumulator")
            acc -= program[operand1]
            pc += 2
        elif opcode == MUL:
            operand1 = program[pc + 1]
            print(f"Multiplying value {program[operand1]} from address {operand1} to accumulator")
            acc *= program[operand1]
            pc += 2
        elif opcode == DIV:
            operand1 = program[pc + 1]
            print(f"Dividing value {program[operand1]} from address {operand1} to accumulator")
            acc //= program[operand1]
            pc += 2
        elif opcode == JMP:
            operand1 = program[pc + 1]
            print(f"Jumping to address {operand1}")
            pc = operand1
        elif opcode == JMPN:
            operand1 = program[pc + 1]
            if acc < 0:
                print(f"Jumping to address {operand1} because accumulator is negative")
                pc = operand1
            else:
                print(f"Skipping jump to address {operand1} because accumulator is not negative")
                pc += 2
        elif opcode == JMPP:
            operand1 = program[pc + 1]
            if acc > 0:
                print(f"Jumping to address {operand1} because accumulator is positive")
                pc = operand1
            else:
                print(f"Skipping jump to address {operand1} because accumulator is not positive")
                pc += 2
        elif opcode == JMPZ:
            operand1 = program[pc + 1]
            if acc == 0:
                print(f"Jumping to address {operand1} because accumulator is zero")
                pc = operand1
            else:
                print(f"Skipping jump to address {operand1} because accumulator is not zero")
                pc += 2
        elif opcode == COPY:
            operand1 = program[pc + 1]
            operand2 = program[pc + 2]
            print(f"Copying value {program[operand1]} from address {operand1} to address {operand2}")
            program[operand2] = program[operand1]
            pc += 3
        elif opcode == LOAD:
            operand1 = program[pc + 1]
            print(f"Loading value {program[operand1]} from address {operand1} to accumulator")
            acc = program[operand1]
            pc += 2
        elif opcode == STORE:
            operand1 = program[pc + 1]
            print(f"Storing value {acc} from accumulator to address {operand1}")
            program[operand1] = acc
            pc += 2
        elif opcode == INPUT:
            operand1 = program[pc + 1]
            program[operand1] = int(input("Input: "))
            print(f"Writing input value {program[operand1]} to address {operand1}")
            pc += 2
        elif opcode == OUTPUT:
            operand1 = program[pc + 1]
            print("Output:", program[operand1])
            pc += 2
        elif opcode == STOP:
            print("Stopping program")
            break
        else:
            print("Invalid opcode:", opcode)
            break

    print("Program finished")
    print("Program data:", program)


        
