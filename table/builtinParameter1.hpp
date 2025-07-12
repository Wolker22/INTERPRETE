#ifndef _BUILTINPARAMETER1_HPP_
#define _BUILTINPARAMETER1_HPP_

#include <string>
#include <functional>
#include <memory>
#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter1 : public Builtin {
public:
    using NumericFunction = std::function<double(double)>;
    using LogicalFunction = std::function<bool(double)>;
    using StringFunction = std::function<std::string(double)>;
    using GenericFunction = std::function<ExpNode*(ExpNode*)>;
    
    enum FunctionType { NUMERIC, LOGICAL, STRING, GENERIC };

private:
    FunctionType _funcType;
    std::unique_ptr<void, void(*)(void*)> _function;

    template<typename T>
    static void function_deleter(void* ptr) {
        delete static_cast<T*>(ptr);
    }

public:
    BuiltinParameter1(const std::string& name, int token, NumericFunction func)
        : Builtin(name, token, 1), _funcType(NUMERIC),
          _function(new NumericFunction(std::move(func)), function_deleter<NumericFunction>) {}

    BuiltinParameter1(const std::string& name, int token, LogicalFunction func)
        : Builtin(name, token, 1), _funcType(LOGICAL),
          _function(new LogicalFunction(std::move(func)), function_deleter<LogicalFunction>) {}

    BuiltinParameter1(const std::string& name, int token, StringFunction func)
        : Builtin(name, token, 1), _funcType(STRING),
          _function(new StringFunction(std::move(func)), function_deleter<StringFunction>) {}

    BuiltinParameter1(const std::string& name, int token, GenericFunction func)
        : Builtin(name, token, 1), _funcType(GENERIC),
          _function(new GenericFunction(std::move(func)), function_deleter<GenericFunction>) {}

    ExpNode* evaluate(ExpNode* arg) const {
        switch (_funcType) {
            case NUMERIC: {
                auto func = static_cast<NumericFunction*>(_function.get());
                double argValue = arg->evaluateNumber();
                return new lp::NumberNode((*func)(argValue));
            }
            case LOGICAL: {
                auto func = static_cast<LogicalFunction*>(_function.get());
                double argValue = arg->evaluateNumber();
                return new lp::BoolNode((*func)(argValue));
            }
            case STRING: {
                auto func = static_cast<StringFunction*>(_function.get());
                double argValue = arg->evaluateNumber();
                return new lp::StringNode((*func)(argValue));
            }
            case GENERIC: {
                auto func = static_cast<GenericFunction*>(_function.get());
                return (*func)(arg);
            }
            default: return nullptr;
        }
    }
    
    // ... (resto de la implementación)
};

} // namespace lp

#endif