#ifndef _BUILTINPARAMETER2_HPP_
#define _BUILTINPARAMETER2_HPP_

#include <string>
#include <functional>
#include <memory>
#include "builtin.hpp"
#include "../ast/ast.hpp"

namespace lp {

class BuiltinParameter2 : public Builtin {
public:
    using NumericFunction = std::function<double(double, double)>;
    using LogicalFunction = std::function<bool(double, double)>;
    using StringFunction = std::function<std::string(double, double)>;
    using GenericFunction = std::function<ExpNode*(ExpNode*, ExpNode*)>;
    
    enum FunctionType { NUMERIC, LOGICAL, STRING, GENERIC };

private:
    FunctionType _funcType;
    std::unique_ptr<void, void(*)(void*)> _function;

    template<typename T>
    static void function_deleter(void* ptr) {
        delete static_cast<T*>(ptr);
    }

public:
    BuiltinParameter2(const std::string& name, int token, NumericFunction func)
        : Builtin(name, token, 2), _funcType(NUMERIC),
          _function(new NumericFunction(std::move(func)), function_deleter<NumericFunction>) {}

    BuiltinParameter2(const std::string& name, int token, LogicalFunction func)
        : Builtin(name, token, 2), _funcType(LOGICAL),
          _function(new LogicalFunction(std::move(func)), function_deleter<LogicalFunction>) {}

    BuiltinParameter2(const std::string& name, int token, StringFunction func)
        : Builtin(name, token, 2), _funcType(STRING),
          _function(new StringFunction(std::move(func)), function_deleter<StringFunction>) {}

    BuiltinParameter2(const std::string& name, int token, GenericFunction func)
        : Builtin(name, token, 2), _funcType(GENERIC),
          _function(new GenericFunction(std::move(func)), function_deleter<GenericFunction>) {}

    ExpNode* evaluate(ExpNode* arg1, ExpNode* arg2) const {
        switch (_funcType) {
            case NUMERIC: {
                auto func = static_cast<NumericFunction*>(_function.get());
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new lp::NumberNode((*func)(arg1Value, arg2Value));
            }
            case LOGICAL: {
                auto func = static_cast<LogicalFunction*>(_function.get());
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new lp::BoolNode((*func)(arg1Value, arg2Value));
            }
            case STRING: {
                auto func = static_cast<StringFunction*>(_function.get());
                double arg1Value = arg1->evaluateNumber();
                double arg2Value = arg2->evaluateNumber();
                return new lp::StringNode((*func)(arg1Value, arg2Value));
            }
            case GENERIC: {
                auto func = static_cast<GenericFunction*>(_function.get());
                return (*func)(arg1, arg2);
            }
            default: return nullptr;
        }
    }
    
    // ... (resto de la implementación)
};

} // namespace lp

#endif