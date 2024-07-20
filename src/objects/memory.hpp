#pragma once

#include "memory_entry.hpp"

namespace basilar::objects {

class Memory {
public:
    MemoryEntry read(int address);
    void write(int address, int value);
    void add_absolute(int value);
    void add_relative(int value);

    void set_absolute(int address);
    void set_relative(int address);

    void set_debug_info(int address, string info);

    int get_current_address();
    int get_current_line();
    void next_line();
private:
    vector<MemoryEntry> __memory;
    int __current_line = 0;
};

} // namespace basilar::objects