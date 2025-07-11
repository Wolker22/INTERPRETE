#ifndef _BUILTINPARAMETER1_HPP_
#define _BUILTINPARAMETER1_HPP_

#include <string>
#include <functional>
#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter1 : public Builtin {
public:
    // Tipos de funciones para 1 parámetro
    using NumericFunction = std::function<double(double)>;
    using LogicalFunction = std::function<bool(double)>;
    using StringFunction = std::function<std::string(double)>;
    using GenericFunction = std::function<ExpNode*(ExpNode*)>;
    
    enum FunctionType { NUMERIC, LOGICAL, STRING, GENERIC };

private:
    FunctionType _funcType;
    union {
        NumericFunction numericFunc;
        LogicalFunction logicalFunc;
        StringFunction stringFunc;
        GenericFunction genericFunc;
    } _function;

public:
    // Constructor para función numérica
    BuiltinParameter1(const std::string& name, 
                      int token,
                      NumericFunction func)
        : Builtin(name, token, 1), _funcType(NUMERIC) {
        _function.numericFunc = func;
    }
    
    // Constructor para función lógica
    BuiltinParameter1(const std::string& name, 
                      int token,
                      LogicalFunction func)
        : Builtin(name, token, 1), _funcType(LOGICAL) {
        _function.logicalFunc = func;
    }
    
    // Constructor para función de cadena
    BuiltinParameter1(const std::string& name, 
                      int token,
                      StringFunction func)
        : Builtin(name, token, 1), _funcType(STRING) {
        _function.stringFunc = func;
    }
    
    // Constructor para función genérica
    BuiltinParameter1(const std::string& name, 
                      int token,
                      GenericFunction func)
        : Builtin(name, token, 1), _funcType(GENERIC) {
        _function.genericFunc = func;
    }
    
    // Evaluar la función
    ExpNode* evaluate(ExpNode* arg) const {
        switch (_funcType) {
            case NUMERIC: {
                double argValue = arg->evaluateNumber();
                return new NumberNode(_function.numericFunc(argValue));
            }
            case LOGICAL: {
                double argValue = arg->evaluateNumber();
                return new BoolNode(_function.logicalFunc(argValue));
            }
            case STRING: {
                double argValue = arg->evaluateNumber();
                return new StringNode(_function.stringFunc(argValue));
            }
            case GENERIC:
                return _function.genericFunc(arg);
            default:
                return nullptr;
        }
    }
    
    // Obtener función numérica (para compatibilidad)
    NumericFunction getNumericFunction() const {
        return (_funcType == NUMERIC) ? _function.numericFunc : nullptr;
    }
    
    // Sobrecarga de operador de asignación
    BuiltinParameter1& operator=(const BuiltinParameter1& b);
};

} // namespace lp

#endif