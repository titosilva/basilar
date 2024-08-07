#pragma once

#include "memory_entry.hpp"

#include <vector>
using namespace std;

namespace basilar::objects {

class Memory {
public:
    MemoryEntry read(int address);
    void write(int address, int value);
    void add_absolute(int value);
    void add_relative(int value, int displacement = 0);

    void set_absolute(int address);
    void set_relative(int address);

    void set_debug_info(int address, string info);

    void rellocate(int base_address);
    void merge(Memory other);

    int get_current_address();
    int get_current_line();
    void next_line();
    void set_line_number(int line_number);
private:
    vector<MemoryEntry> __memory;
    int __current_line = 0;
};

} // namespace basilar::objects