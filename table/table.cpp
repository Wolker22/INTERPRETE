#include "table.hpp"
#include "../includes/utils.hpp"
#include <cassert>
#include <iostream>

namespace lp {

bool Table::lookupSymbol(const std::string& name) const {
    return _table.find(toLower(name)) != _table.end();
}

Symbol* Table::getSymbol(const std::string& name) {
    assert(lookupSymbol(name) && "Symbol not found");
    return _table.at(toLower(name)).get();
}

const Symbol* Table::getSymbol(const std::string& name) const {
    assert(lookupSymbol(name) && "Symbol not found");
    return _table.at(toLower(name)).get();
}

void Table::installSymbol(Symbol* s) {
    assert(!lookupSymbol(s->getName()) && "Symbol already exists");
    _table[toLower(s->getName())] = std::unique_ptr<Symbol>(s);
}

void Table::installSymbol(std::unique_ptr<Symbol> s) {
    assert(!lookupSymbol(s->getName()) && "Symbol already exists");
    _table[toLower(s->getName())] = std::move(s);
}

void Table::eraseSymbol(const std::string& name) {
    assert(lookupSymbol(name) && "Symbol does not exist");
    _table.erase(toLower(name));
}

void Table::printTable() const {
    for (const auto& [name, symbol] : _table) {
        std::cout << name << ", " << symbol->getToken() << std::endl;
    }
}

} // namespace lp