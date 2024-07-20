#include "symbol_table.hpp"

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

    __symbols[name].is_public = true;
}

int SymbolTable::refer(string name, int address) {
    if (__symbols.find(name) == __symbols.end()) {
        __symbols[name] = __default_symbol(name);
    }

    if (__symbols[name].address == -1) {
        __symbols[name].references.push_back(address);
    }

    return __symbols[name].address;
}

list<int> SymbolTable::get_pending_references(string name) {
    if (__symbols.find(name) == __symbols.end()) {
        return list<int>();
    }

    return __symbols[name].references;
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

} // namespace basilar::objects