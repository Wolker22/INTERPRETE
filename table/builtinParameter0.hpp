#ifndef _BUILTINPARAMETER0_HPP_
#define _BUILTINPARAMETER0_HPP_

#include <string>
#include <functional>
#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter0 : public Builtin {
public:
    using NumericFunction = std::function<double()>;
    using LogicalFunction = std::function<bool()>;
    using StringFunction = std::function<std::string()>;
    
    enum FunctionType { NUMERIC, LOGICAL, STRING };

private:
    FunctionType _funcType;
    union {
        NumericFunction numericFunc;
        LogicalFunction logicalFunc;
        StringFunction stringFunc;
    } _function;

public:
    BuiltinParameter0(const std::string& name, int token, NumericFunction func)
        : Builtin(name, token, 0), _funcType(NUMERIC) {
        _function.numericFunc = func;
    }
    
    BuiltinParameter0(const std::string& name, int token, LogicalFunction func)
        : Builtin(name, token, 0), _funcType(LOGICAL) {
        _function.logicalFunc = func;
    }
    
    BuiltinParameter0(const std::string& name, int token, StringFunction func)
        : Builtin(name, token, 0), _funcType(STRING) {
        _function.stringFunc = func;
    }
    
    ExpNode* evaluate() const {
        switch (_funcType) {
            case NUMERIC:
                return new lp::NumberNode(_function.numericFunc());
            case LOGICAL:
                return new lp::BoolNode(_function.logicalFunc());
            case STRING:
                return new lp::StringNode(_function.stringFunc());
            default:
                return nullptr;
        }
    }
    
    // ... (resto de la implementación)
};

} // namespace lp

#endif