#ifndef CALCULADORA_H
#define CALCULADORA_H

double** crearMatriz(int filas, int cols);
void liberarMatriz(double** m, int filas);
void leerMatriz(double** m, int filas, int cols);
void mostrarMatriz(double** m, int filas, int cols);

double** sumarMatrices(double** a, double** b, int filas, int cols);
double** restarMatrices(double** a, double** b, int filas, int cols);
double** multiplicarMatrices(double** a, double** b, int f1, int c1, int c2);
double** obtenerTranspuesta(double** m, int filas, int cols);
double calcularTraza(double** m, int n);

double** obtenerSubmatriz(double** m, int n, int filaEliminar, int colEliminar);
double calcularDeterminante(double** m, int n);
bool resolverCramer(double** A, double* B, double* X, int n);

#endif
