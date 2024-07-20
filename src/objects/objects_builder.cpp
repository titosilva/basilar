#include "objects_builder.hpp"
#include "../exceptions/semantic_exception.hpp"

using namespace basilar::exceptions;

namespace basilar::objects {

void ObjectsBuilder::refer(string name) {
    auto r = __symbol_table.refer(name, __memory.get_current_address());

    __memory.add_relative(r);
    __memory.set_debug_info(__memory.get_current_address() - 1, name);
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
}

void ObjectsBuilder::set_public(string name) {
    __symbol_table.define_public(name);
}

void ObjectsBuilder::absolute(int value) {
    __memory.add_absolute(value);
}

string ObjectsBuilder::build_debug_file() {
    string debug_file = "";

    // Add the memory lines
    int current_line = 0;
    for (int i = 0; i < __memory.get_current_address(); i++) {
        auto entry = __memory.read(i);

        if (entry.line != current_line) {
            debug_file += "end\t" + to_string(i) + "|\t";
        } else {
            debug_file += "\t";
        }

        debug_file += to_string(entry.value);
        
        if (entry.is_absolute) {
            debug_file += "a";
        } else {
            debug_file += "r";
        }

        if (entry.debug_info != "") {
            debug_file += "{" + entry.debug_info + "}";
        }

        if (entry.line != current_line) {
            debug_file += "\n";
            current_line = entry.line;
        }
    }

    // Add the symbol table
    debug_file += "\n\n";
    for (auto [name, entry] : __symbol_table.get_table()) {
        debug_file += name + "\t" + to_string(entry.address);

        if (entry.is_public) {
            debug_file += "pub";
        }

        if (entry.is_external) {
            debug_file += "ext";
        }

        debug_file += "\t";

        for (auto reference : entry.references) {
            debug_file += to_string(reference) + " ";
        }

        debug_file += "\n";
    }

    return debug_file;
}

string ObjectsBuilder::build_object_file() {
    string object_file = "";

    bool has_linking = false;
    for (auto [name, entry] : __symbol_table.get_table()) {
        if (entry.is_external || entry.is_public) {
            has_linking = true;
            break;
        }
    }

    if (!has_linking) {
        // Add the external references
        object_file += "USO\n";
        for (auto [name, entry] : __symbol_table.get_table()) {
            if (entry.is_external) {
                object_file += name + "\t" + to_string(entry.address) + "\n";
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

        object_file += "\n";
    }

    // Add the memory values
    for (int i = 0; i < __memory.get_current_address(); i++) {
        auto entry = __memory.read(i);
        object_file += to_string(entry.value);
        object_file += " ";
    }

    return object_file;
}

} // namespace basilar::objects