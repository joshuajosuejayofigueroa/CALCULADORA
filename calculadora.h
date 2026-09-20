#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <iostream>
using namespace std;

// OPERACIONES BASICAS Y EVALUADOR DE EXPRESIONES
void operacionesBasicas(double& Ans);
double evaluarExpresion(char texto[], int& posicion);
double evaluarTermino(char texto[], int& posicion);
double evaluarFactor(char texto[], int& posicion);

// MODULO CIENTIFICO
double potencia(double base, int exponente);
double factorial(int n);
double senoTaylor(double x, int n);
double seno(double grados, int n);
double cosenoTaylor(double x, int n);
double coseno(double grados, int n);
double exponencialTaylor(double x, int n);
double exponencial(double x, int grado);
double logaritmoTaylor(double y, int n);
double logaritmo(double x, int grado);

// MODULO DE MATRICES
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
