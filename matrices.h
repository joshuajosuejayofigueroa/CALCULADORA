#ifndef MATRICES_H
#define MATRICES_H
#ifndef MATRICES_H
#define MATRICES_H

double** crearMatriz(int filas, int columnas);         
void liberarMatriz(double** matriz, int filas);         
void leerMatriz(double** matriz, int filas, int columnas);      
void imprimirMatriz(double** matriz, int filas, int columnas);   

double** sumarMatrices(double** A, double** B, int filas, int columnas);
double** restarMatrices(double** A, double** B, int filas, int columnas);
double** multiplicarMatrices(double** A, int filasA, int columnasA,
                              double** B, int filasB, int columnasB);
double** transponerMatriz(double** A, int filas, int columnas);
double calcularTraza(double** A, int n); // solo matrices cuadradas

double calcularDeterminante(double** A, int n);

bool resolverGaussJordan(double** aumentada, int n, double soluciones[]);

#endif

double** crearMatriz(int filas, int columnas);           // reserva memoria (new)
void liberarMatriz(double** matriz, int filas);          // libera memoria (delete)
void leerMatriz(double** matriz, int filas, int columnas);       // pide datos por teclado
void imprimirMatriz(double** matriz, int filas, int columnas);   // muestra en consola

double** sumarMatrices(double** A, double** B, int filas, int columnas);
double** restarMatrices(double** A, double** B, int filas, int columnas);
double** multiplicarMatrices(double** A, int filasA, int columnasA,
                              double** B, int filasB, int columnasB);
double** transponerMatriz(double** A, int filas, int columnas);
double calcularTraza(double** A, int n); // solo matrices cuadradas

double calcularDeterminante(double** A, int n);

bool resolverGaussJordan(double** aumentada, int n, double soluciones[]);

#endif
