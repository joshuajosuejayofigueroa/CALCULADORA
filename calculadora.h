#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <iostream>

using namespace std;

double potencia(double base, int exponente);
double factorial(int numero);
double seno(double x);
double coseno(double x);
double exponencial(double x);
double logaritmo(double x);

double** crearMatriz(int filas, int columnas);
void liberarMatriz(double** matriz, int filas);
void leerMatriz(double** matriz, int filas, int columnas);
void imprimirMatriz(double** matriz, int filas, int columnas);

double** sumarMatrices(double** matrizA, double** matrizB, int filas, int columnas);
double** restarMatrices(double** matrizA, double** matrizB, int filas, int columnas);
double** multiplicarMatrices(double** matrizA, double** matrizB, int filasA, int columnasA, int columnasB);
double** obtenerTranspuesta(double** matriz, int filas, int columnas);
double obtenerTraza(double** matriz, int filas);
double obtenerDeterminante(double** matriz, int dimension);

#endif
