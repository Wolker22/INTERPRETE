#ifndef _MATHFUNCTION_HPP_
#define _MATHFUNCTION_HPP_

#include <string>
#include <stdexcept>

namespace lp {

// Excepción especializada para errores matemáticos
class MathException : public std::runtime_error {
public:
    MathException(const std::string& function, const std::string& error)
        : std::runtime_error("Math error in " + function + ": " + error) {}
};

// Funciones matemáticas seguras
double SafeLog(double x);
double SafeLog10(double x);
double SafeExp(double x);
double SafeSqrt(double x);
double SafeAtan2(double x, double y);

// Funciones matemáticas estándar
double Integer(double x);
double Random();

} // namespace lp

#endif