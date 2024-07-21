#include "symbol_table.hpp"
#include "../exceptions/semantic_exception.hpp"
#include "../exceptions/linking_exception.hpp"

using namespace basilar::exceptions;

namespace basilar::objects {

bool SymbolTable::define(string name, int address) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
        __symbols[name].address = address;
        return true;
    }

    if (__symbols[name].address != -1) {
        return false;
    }

    __symbols[name].address = address;
    return true;
}

bool SymbolTable::define_external(string name) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
        __symbols[name].address = 0;
        __symbols[name].is_external = true;
        return true;
    }

    if (__symbols[name].address != -1) {
        return false;
    }

    __symbols[name].address = 0;
    __symbols[name].is_external = true;
    return true;
}

void SymbolTable::define_public(string name) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
    }

    // This check is not requested by the specification
    // if (__symbols[name].is_external) {
    //     throw semantic_exception("Cannot set public an external symbol: " + name);
    // }

    __symbols[name].is_public = true;
}

int SymbolTable::refer(string name, int address) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
    }

    if (__symbols[name].address == -1 || __symbols[name].is_external) {
        __symbols[name].pending_references.push_back(address);
    }

    return __symbols[name].address;
}

void SymbolTable::rellocate(int base_address) {
    for (auto& [name, symbol] : __symbols) {
        for (auto& reference : symbol.pending_references) {
            reference += base_address;
        }
        
        if (symbol.address == -1) {
            continue;
        }

        if (symbol.is_external) {
            continue;
        }

        symbol.address += base_address;
    }
}

void SymbolTable::merge(SymbolTable other) {
    for (auto& [name, symbol] : other.__symbols) {
        if (__symbols.find(name) == __symbols.end()) {
            __symbols[name] = symbol;
            continue;
        }

        if (__symbols[name].address != -1 && symbol.address != -1) {
            throw linking_exception("Symbol \"" + name + "\" defined in both object files");   
        }

        if (__symbols[name].address == -1) {
            __symbols[name].address = symbol.address;
        }

        for (auto reference : symbol.pending_references) {
            __symbols[name].pending_references.push_back(reference);
        }
    }
}

void SymbolTable::add_pending_reference(string name, int address) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
    }

    __symbols[name].pending_references.push_back(address);
}

list<int> SymbolTable::get_pending_references(string name) {
    if (__symbols.find(name) == __symbols.end()) {
        return list<int>();
    }

    return __symbols[name].pending_references;
}

map<string, Symbol> SymbolTable::get_table() {
    return map<string, Symbol>(__symbols);
}

Symbol SymbolTable::__default_symbol(string name) {
    Symbol symbol;
    symbol.name = name;
    symbol.address = -1;
    symbol.is_external = false;
    symbol.is_public = false;

    return symbol;
}

void SymbolTable::check_consistency() {
    for (auto [name, symbol] : __symbols) {
        if (symbol.address == -1) {
            throw semantic_exception("Symbol \"" + name + "\" not defined");
        }
    }
}

} // namespace basilar::objects