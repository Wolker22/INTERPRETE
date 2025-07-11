#ifndef _BUILTINPARAMETER0_HPP_
#define _BUILTINPARAMETER0_HPP_

#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter0 : public Builtin {
public:
    // Tipos de funciones para 0 parámetros
    typedef double (*NumericFunction0)();
    typedef bool (*LogicalFunction0)();
    typedef std::string (*StringFunction0)();
    
    enum FunctionType { NUMERIC, LOGICAL, STRING };

private:
    FunctionType _funcType;
    union {
        NumericFunction0 numericFunc;
        LogicalFunction0 logicalFunc;
        StringFunction0 stringFunc;
    } _function;

public:
    // Constructor para función numérica
    BuiltinParameter0(const std::string& name, 
                      int token,
                      NumericFunction0 func)
        : Builtin(name, token, 0), _funcType(NUMERIC) {
        _function.numericFunc = func;
    }
    
    // Constructor para función lógica
    BuiltinParameter0(const std::string& name, 
                      int token,
                      LogicalFunction0 func)
        : Builtin(name, token, 0), _funcType(LOGICAL) {
        _function.logicalFunc = func;
    }
    
    // Constructor para función de cadena
    BuiltinParameter0(const std::string& name, 
                      int token,
                      StringFunction0 func)
        : Builtin(name, token, 0), _funcType(STRING) {
        _function.stringFunc = func;
    }
    
    // Evaluar la función
    ExpNode* evaluate() const {
        switch (_funcType) {
            case NUMERIC:
                return new NumberNode(_function.numericFunc());
            case LOGICAL:
                return new BoolNode(_function.logicalFunc());
            case STRING:
                return new StringNode(_function.stringFunc());
            default:
                return nullptr;
        }
    }
    
    // Sobrecarga de operador de asignación
    BuiltinParameter0& operator=(const BuiltinParameter0& b);
};

} // namespace lp

#endif