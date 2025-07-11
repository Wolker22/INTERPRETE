#include <cmath>
#include <random>
#include <chrono>
#include "mathFunction.hpp"

namespace lp {

// Función auxiliar para validar entradas
namespace {
    void CheckDomain(double x, const std::string& function) {
        if (std::isnan(x)) {
            throw MathException(function, "NaN input");
        }
        if (std::isinf(x)) {
            throw MathException(function, "Infinite input");
        }
    }
}

double SafeLog(double x) {
    CheckDomain(x, "logarithm");
    if (x <= 0.0) {
        throw MathException("logarithm", "Non-positive argument");
    }
    return std::log(x);
}

double SafeLog10(double x) {
    CheckDomain(x, "log10");
    if (x <= 0.0) {
        throw MathException("log10", "Non-positive argument");
    }
    return std::log10(x);
}

double SafeExp(double x) {
    CheckDomain(x, "exponential");
    const double result = std::exp(x);
    if (std::isinf(result)) {
        throw MathException("exponential", "Overflow");
    }
    return result;
}

double SafeSqrt(double x) {
    CheckDomain(x, "square root");
    if (x < 0.0) {
        throw MathException("square root", "Negative argument");
    }
    return std::sqrt(x);
}

double SafeAtan2(double x, double y) {
    CheckDomain(x, "atan2");
    CheckDomain(y, "atan2");
    if (x == 0.0 && y == 0.0) {
        throw MathException("atan2", "Both arguments zero");
    }
    return std::atan2(x, y);
}

double Integer(double x) {
    return std::trunc(x);
}

double Random() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

} // namespace lp