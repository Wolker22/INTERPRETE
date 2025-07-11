/*!
  \file    mathFunction.hpp
  \brief   Prototipos de funciones matemáticas con control de errores
*/

#ifndef _MATHFUNCTION_HPP_
#define _MATHFUNCTION_HPP_

#include <string>

/*!
  \brief   Calcula el logaritmo neperiano de un número real
  \note    Se verifica que el argumento sea válido
  \param   x Número real
  \return  log(x)
*/
double Log(double x);

/*!
  \brief   Calcula el logaritmo decimal de un número real
  \note    Se verifica que el argumento sea válido
  \param   x Número real
  \return  log10(x)
*/
double Log10(double x);

/*!
  \brief   Calcula la exponencial de un número real
  \note    Se verifica que el argumento sea válido
  \param   x Número real
  \return  exp(x)
*/
double Exp(double x);

/*!
  \brief   Calcula la raíz cuadrada de un número real
  \note    Se verifica que el argumento sea válido
  \param   x Número real
  \return  sqrt(x)
*/
double Sqrt(double x);

/*!
  \brief   Obtiene la parte entera de un número real (truncamiento)
  \param   x Número real
  \return  Parte entera como número real
*/
double integer(double x);

/*!
  \brief   Genera un número aleatorio entre 0 y 1
  \return  Número aleatorio en [0, 1]
*/
double Random();

/*!
  \brief   Calcula la arcotangente del cociente x/y
  \note    No es equivalente a atan2(y, x)
  \param   x Valor del numerador
  \param   y Valor del denominador
  \return  atan(x/y)
*/
double Atan2(double x, double y);

#endif // _MATHFUNCTION_HPP_
