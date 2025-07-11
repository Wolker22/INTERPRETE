#ifndef _BUILTIN_HPP_
#define _BUILTIN_HPP_

#include <string>
#include <iostream>
#include "symbol.hpp"

namespace lp {

class Builtin : public Symbol {
protected:
    int _nParameters;

public:
    Builtin(const std::string& name = "", int token = 0, int nParameters = 0)
        : Symbol(name, token), _nParameters(nParameters) {}

    Builtin(const Builtin& b) 
        : Symbol(b), _nParameters(b._nParameters) {}

    int getNParameters() const { return _nParameters; }
    void setNParameters(int nParameters) { _nParameters = nParameters; }

    virtual Builtin& operator=(const Builtin& b) {
        if (this != &b) {
            Symbol::operator=(b);
            _nParameters = b._nParameters;
        }
        return *this;
    }

    virtual void read() {}
    virtual void write() const {}
};

} // namespace lp

#endif