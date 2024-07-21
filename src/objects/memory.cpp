#include "memory.hpp"

namespace basilar::objects {

MemoryEntry Memory::read(int address) {
    return __memory[address];
}

void Memory::write(int address, int value) {
    __memory[address].value = value;
}

void Memory::add_absolute(int value) {
    MemoryEntry entry;
    entry.value = value;
    entry.is_absolute = true;
    entry.line = __current_line;

    __memory.push_back(entry);
}

void Memory::add_relative(int value, int displacement) {
    MemoryEntry entry;
    entry.value = value;
    entry.is_absolute = false;
    entry.line = __current_line;
    entry.displacement = displacement;

    __memory.push_back(entry);
}

void Memory::set_debug_info(int address, string info) {
    __memory[address].debug_info = info;
}

void Memory::set_absolute(int address) {
    __memory[address].is_absolute = true;
}

void Memory::set_relative(int address) {
    __memory[address].is_absolute = false;
}

void Memory::rellocate(int base_address) {
    for (uint i = 0; i < __memory.size(); i++) {
        auto entry = __memory[i];
        if (!entry.is_absolute) {
            __memory[i].value += base_address;
        }
    }
}

void Memory::merge(Memory other) {
    for (auto entry : other.__memory) {
        __memory.push_back(entry);
    }
}

int Memory::get_current_address() {
    return __memory.size();
}

int Memory::get_current_line() {
    return __current_line;
}

void Memory::next_line() {
    __current_line++;
}

} // namespace basilar::objects