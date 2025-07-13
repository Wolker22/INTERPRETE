/*!
  \file error.cpp
  \brief Code of error recovery functions 
*/

#include <iostream>
#include <string>
#include <setjmp.h>
#include <cerrno>

#include "error.hpp"
#include "../includes/macros.hpp"

extern int lineNumber; //!< Referencia al contador de líneas
extern std::string progname; //!< Referencia al nombre del programa
extern jmp_buf begin; //!< Usado para recuperación de errores

namespace lp {

void warning(std::string errorMessage1, std::string errorMessage2)
{
  std::cerr << IGREEN; 
  std::cerr << " Program: " << progname << std::endl;
  std::cerr << BIRED; 
  std::cerr << " Error line " << lineNumber 
            << " --> " << errorMessage1 << std::endl;
  std::cerr << RESET; 

  if (!errorMessage2.empty())
    std::cerr << "\t" << errorMessage2 << std::endl;
}

void yyerror(std::string errorMessage)
{
  warning("Parser error", errorMessage);
}

void execerror(std::string errorMessage1, std::string errorMessage2)
{
  warning(errorMessage1, errorMessage2); 
  longjmp(begin, 0); // Volver a un estado viable
}

void fpecatch(int signum)     
{
  execerror("Run time", "floating point error");
}

double errcheck(double d, std::string s)
{
  if (errno == EDOM)
  {
    errno = 0;
    std::string msg("Runtime error --> argument out of domain");
    std::cout << msg << std::endl;
    execerror(s, msg);
  }
  else if (errno == ERANGE)
  {
    std::string msg("Runtime error --> result out of range");
    errno = 0;
    execerror(s, msg);
  }

  return d;
}

} // namespace lp
