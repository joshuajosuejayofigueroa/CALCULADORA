#ifndef CALCULO_H
#define CALCULO_H

#include <string>
#include "memoria.h"

const int CANTIDAD_TERMINOS = 25;

double potencia(double base, long long exponente);

double factorial(long long numero);

double calcularExp(double x, int terminos = CANTIDAD_TERMINOS);

double calcularLn(double x, int terminos = CANTIDAD_TERMINOS);

double calcularSeno(double xRadianes, int terminos = CANTIDAD_TERMINOS);
double calcularCoseno(double xRadianes, int terminos = CANTIDAD_TERMINOS);

double potenciaConDecimales(double base, double exponente);

double evaluarExpresion(const std::string &expresionTexto, MemoriaCalculadora &memoria);

#endif
