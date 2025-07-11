#ifndef _BUILTINPARAMETER2_HPP_
#define _BUILTINPARAMETER2_HPP_

#include <string>
#include <functional>
#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter2 : public Builtin {
public:
    // Tipos de funciones para 2 parámetros
    using NumericFunction = std::function<double(double, double)>;
    using LogicalFunction = std::function<bool(double, double)>;
    using StringFunction = std::function<std::string(double, double)>;
    using GenericFunction = std::function<ExpNode*(ExpNode*, ExpNode*)>;
    
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
    BuiltinParameter2(const std::string& name, 
                      int token,
                      NumericFunction func)
        : Builtin(name, token, 2), _funcType(NUMERIC) {
        _function.numericFunc = func;
    }
    
    // Constructor para función lógica
    BuiltinParameter2(const std::string& name, 
                      int token,
                      LogicalFunction func)
        : Builtin(name, token, 2), _funcType(LOGICAL) {
        _function.logicalFunc = func;
    }
    
    // Constructor para función de cadena
    BuiltinParameter2(const std::string& name, 
                      int token,
                      StringFunction func)
        : Builtin(name, token, 2), _funcType(STRING) {
        _function.stringFunc = func;
    }
    
    // Constructor para función genérica
    BuiltinParameter2(const std::string& name, 
                      int token,
                      GenericFunction func)
        : Builtin(name, token, 2), _funcType(GENERIC) {
        _function.genericFunc = func;
    }
    
    // Evaluar la función
    ExpNode* evaluate(ExpNode* arg1, ExpNode* arg2) const {
        switch (_funcType) {
            case NUMERIC: {
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new NumberNode(_function.numericFunc(arg1Value, arg2Value));
            }
            case LOGICAL: {
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new BoolNode(_function.logicalFunc(arg1Value, arg2Value));
            }
            case STRING: {
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new StringNode(_function.stringFunc(arg1Value, arg2Value));
            }
            case GENERIC:
                return _function.genericFunc(arg1, arg2);
            default:
                return nullptr;
        }
    }
    
    // Obtener función numérica (para compatibilidad)
    NumericFunction getNumericFunction() const {
        return (_funcType == NUMERIC) ? _function.numericFunc : nullptr;
    }
    
    // Sobrecarga de operador de asignación
    BuiltinParameter2& operator=(const BuiltinParameter2& b);
};

} // namespace lp

#endif