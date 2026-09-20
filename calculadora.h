#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <iostream>
using namespace std;

void operacionesBasicas(double& Ans);

double potencia(double base, int exponente);
double factorial(int n);
double seno(double x, int n = 10);
double coseno(double x, int n = 10);
double exponencial(double x, int n = 10);
double logaritmo(double x, int n = 10);

double** crearMatriz(int filas, int columnas);
void liberarMatriz(double** matriz, int filas);
void leerMatriz(double** matriz, int filas, int columnas);
void mostrarMatriz(double** matriz, int filas, int columnas);

double** sumarMatrices(double** A, double** B, int filas, int columnas);
double** restarMatrices(double** A, double** B, int filas, int columnas);
double** multiplicarMatrices(double** A, int fA, int cA, double** B, int fB, int cB);
double** transponerMatriz(double** A, int filas, int columnas);
double calcularTraza(double** A, int n);
double determinante(double** A, int n);
void resolverGaussJordan();

#endif
