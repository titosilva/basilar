#include "objects_builder.hpp"
#include "../exceptions/semantic_exception.hpp"
#include "../utils/logger.hpp"

using namespace basilar::exceptions;

namespace basilar::objects {

void ObjectsBuilder::refer(string name, int displacement) {
    auto r = __symbol_table.refer(name, __memory.get_current_address());
    __memory.add_relative(r, displacement);
}

void ObjectsBuilder::define(string name) {
    auto defined = __symbol_table.define(name, __memory.get_current_address());

    if (!defined) {
        throw semantic_exception("Symbol \"" + name + "\" already defined", __memory.get_current_line());
    }

    auto references = __symbol_table.get_pending_references(name);
    for (auto reference : references) {
        __memory.write(reference, __memory.get_current_address());
    }
}

void ObjectsBuilder::define_external(string name) {
    auto defined = __symbol_table.define_external(name);

    if (!defined) {
        throw semantic_exception("Symbol \"" + name + "\" already defined", __memory.get_current_line());
    }

    auto references = __symbol_table.get_pending_references(name);
    for (auto reference : references) {
        __memory.write(reference, 0);
    }
}

void ObjectsBuilder::set_public(string name) {
    __symbol_table.define_public(name);
}

void ObjectsBuilder::add_reference(string name, int address) {
    __symbol_table.add_pending_reference(name, address);
}

void ObjectsBuilder::add_definition(string name, int address) {
    __symbol_table.define(name, address);
}

void ObjectsBuilder::absolute(int value) {
    __memory.add_absolute(value);
}

void ObjectsBuilder::relative(int value) {
    __memory.add_relative(value, 0);
}

void ObjectsBuilder::rellocate(int base_address) {
    __memory.rellocate(base_address);
    __symbol_table.rellocate(base_address);
}

void ObjectsBuilder::link(ObjectsBuilder& other) {
    auto base_address = __memory.get_current_address();

    debug_log_symbol_table(other.__symbol_table);
    other.rellocate(base_address);
    debug_log_symbol_table(other.__symbol_table);

    __memory.merge(other.__memory);
    __symbol_table.merge(other.__symbol_table);

    resolve();
}

void ObjectsBuilder::resolve() {
    for (auto [name, entry] : __symbol_table.get_table()) {
        if (entry.address == -1) {
            continue;
        }

        for (auto reference : entry.pending_references) {
            __memory.write(reference, entry.address);
        }
    }
}

int ObjectsBuilder::get_current_address() {
    return __memory.get_current_address();
}

void ObjectsBuilder::write_debug_info(int address, string info) {
    auto src_debug_info = __memory.read(address).debug_info;

    if (src_debug_info != "") {
        src_debug_info += "|";
    }

    __memory.set_debug_info(address, src_debug_info + info);
}

void ObjectsBuilder::append_debug_info(string info) {
    auto current_address = __memory.get_current_address();
    write_debug_info(current_address - 1, info);
}

void ObjectsBuilder::next_line() {
    __memory.next_line();
}

string ObjectsBuilder::build_debug_code() {
    string debug_file = "";

    // Add the memory lines
    int current_line = -1;
    for (int i = 0; i < __memory.get_current_address(); i++) {
        auto entry = __memory.read(i);

        if (entry.line != current_line) {
            debug_file += "\nend " + to_string(i) + ". ";
            current_line = entry.line;
        } else {
            debug_file += "\t";
        }

        debug_file += to_string(entry.value);
        if (entry.displacement > 0) {
            debug_file += "+" + to_string(entry.displacement);
        }
        
        if (entry.is_absolute) {
            debug_file += "a";
        } else {
            debug_file += "r";
        }

        if (entry.debug_info != "") {
            debug_file += "{" + entry.debug_info + "}";
        }
    }

    // Add the symbol table
    debug_file += "\n\n";
    for (auto [name, entry] : __symbol_table.get_table()) {
        debug_file += name + " def: " + to_string(entry.address);

        if (entry.is_public) {
            debug_file += "(pub)";
        }

        if (entry.is_external) {
            debug_file += "(ext)";
        }

        debug_file += " pendings: ";

        for (auto reference : entry.pending_references) {
            debug_file += to_string(reference) + " ";
        }

        debug_file += "\n";
    }

    return debug_file;
}

string ObjectsBuilder::build_object_code() {
    string object_file = "";

    bool has_linking = false;
    for (auto [name, entry] : __symbol_table.get_table()) {
        if (entry.is_external || entry.is_public) {
            has_linking = true;
            break;
        }
    }

    if (has_linking) {
        // Add the external references
        object_file += "USO\n";
        for (auto [name, entry] : __symbol_table.get_table()) {
            if (!entry.is_external) {
                continue;
            }

            for (auto reference : entry.pending_references) {
                object_file += name + "\t" + to_string(reference) + "\n";
            }
        }

        // Add the public definitions
        object_file += "\nDEF\n";
        for (auto [name, entry] : __symbol_table.get_table()) {
            if (entry.is_public) {
                object_file += name + "\t" + to_string(entry.address) + "\n";
            }
        }

        // Add the relative and absolute information
        object_file += "\nREAL\n";
        for (int i = 0; i < __memory.get_current_address(); i++) {
            auto entry = __memory.read(i);
            if (entry.is_absolute) {
                object_file += "0";
            } else {
                object_file += "1";
            }
        }

        object_file += "\n\n";
    }

    // Add the memory values
    for (int i = 0; i < __memory.get_current_address(); i++) {        
        auto entry = __memory.read(i);
        object_file += to_string(entry.value + entry.displacement);
        object_file += " ";
    }

    return object_file;
}

void ObjectsBuilder::check_consistency() {
    __symbol_table.check_consistency();
}

void debug_log_symbol_table(SymbolTable& symbol_table) {
    #ifndef DEBUG
    return;
    #endif

    LOG_DEBUG("Symbol table:");
    for (auto [name, entry] : symbol_table.get_table()) {
        string debug_info = name + " def: " + to_string(entry.address);

        if (entry.is_public) {
            debug_info += "(pub)";
        }

        if (entry.is_external) {
            debug_info += "(ext)";
        }

        debug_info += " pendings: ";

        for (auto reference : entry.pending_references) {
            debug_info += to_string(reference) + " ";
        }

        LOG_DEBUG(debug_info);
    }
}

} // namespace basilar::objects