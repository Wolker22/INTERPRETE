#include "table.hpp"
#include "../includes/utils.hpp"
#include <cassert>
#include <iostream>
#include <cctype> // Añadido para std::tolower
#include <algorithm> // Añadido para std::transform

namespace lp {

std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return result;
}

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
    for (const auto& pair : _table) {
        std::cout << pair.first << ", " << pair.second->getToken() << std::endl;
    }
}

} // namespace lp