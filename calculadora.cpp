#include <iostream>
#include "calculadora.h"

double** crearMatriz(int filas, int cols) {
    double** m = new double*[filas];
    for (int i = 0; i < filas; i++) {
        m[i] = new double[cols];
    }
    return m;
}

void liberarMatriz(double** m, int filas) {
    if (m == nullptr) return;
    for (int i = 0; i < filas; i++) {
        delete[] m[i];
    }
    delete[] m;
}

void leerMatriz(double** m, int filas, int cols) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "Ingresa [" << i << "][" << j << "]: ";
            std::cin >> m[i][j];
        }
    }
}

void mostrarMatriz(double** m, int filas, int cols) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << "\n";
    }
}


double** sumarMatrices(double** a, double** b, int filas, int cols) {
    double** res = crearMatriz(filas, cols);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return res;
}

double** restarMatrices(double** a, double** b, int filas, int cols) {
    double** res = crearMatriz(filas, cols);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return res;
}

double** multiplicarMatrices(double** a, double** b, int f1, int c1, int c2) {
    double** res = crearMatriz(f1, c2);
    for (int i = 0; i < f1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

double** obtenerTranspuesta(double** m, int filas, int cols) {
    double** res = crearMatriz(cols, filas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            res[j][i] = m[i][j];
        }
    }
    return res;
}

double calcularTraza(double** m, int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += m[i][i];
    }
    return suma;
}


double** obtenerSubmatriz(double** m, int n, int filaEliminar, int colEliminar) {
    double** sub = crearMatriz(n - 1, n - 1);
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (i == filaEliminar) continue;
        int c = 0;
        for (int j = 0; j < n; j++) {
            if (j == colEliminar) continue;
            sub[r][c] = m[i][j];
            c++;
        }
        r++;
    }
    return sub;
}

double calcularDeterminante(double** m, int n) {
    if (n == 1) return m[0][0];
    if (n == 2) return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);

    double det = 0;
    int signo = 1;

    for (int j = 0; j < n; j++) {
        double** sub = obtenerSubmatriz(m, n, 0, j);
        det += signo * m[0][j] * calcularDeterminante(sub, n - 1);
        liberarMatriz(sub, n - 1); 
        signo = -signo;
    }
    return det;
}

bool resolverCramer(double** A, double* B, double* X, int n) {
    double detA = calcularDeterminante(A, n);
    if (detA == 0) return false;

    double** temp = crearMatriz(n, n);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                temp[i][k] = A[i][k];
            }
        }

        for (int i = 0; i < n; i++) {
            temp[i][j] = B[i];
        }

        X[j] = calcularDeterminante(temp, n) / detA;
    }

    liberarMatriz(temp, n);
    return true;
}
