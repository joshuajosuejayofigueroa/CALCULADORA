#include "matrices.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

using namespace std;

double** crearMatriz(int filas, int columnas) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new double[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0.0; // inicializamos en cero
        }
    }
    return matriz;
}

void liberarMatriz(double** matriz, int filas) {
    if (matriz == nullptr) return;
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void leerMatriz(double** matriz, int filas, int columnas) {
    cout << "Ingrese los " << filas << "x" << columnas << " valores (separados por enter):\n";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "  [" << i << "][" << j << "] = ";
            while (!(cin >> matriz[i][j])) {
                cout << "  Valor invalido, intente de nuevo: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}

void imprimirMatriz(double** matriz, int filas, int columnas) {
    cout << fixed << setprecision(2);
    for (int i = 0; i < filas; i++) {
        cout << "  [ ";
        for (int j = 0; j < columnas; j++) {
            cout << setw(8) << matriz[i][j] << " ";
        }
        cout << "]\n";
    }
}

double** sumarMatrices(double** A, double** B, int filas, int columnas) {
    double** resultado = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            resultado[i][j] = A[i][j] + B[i][j];
    return resultado;
}

double** restarMatrices(double** A, double** B, int filas, int columnas) {
    double** resultado = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            resultado[i][j] = A[i][j] - B[i][j];
    return resultado;
}

double** multiplicarMatrices(double** A, int filasA, int columnasA,
                              double** B, int filasB, int columnasB) {
    if (columnasA != filasB) {
        throw runtime_error("Dimensiones incompatibles para multiplicar (columnas de A != filas de B)");
    }
    double** resultado = crearMatriz(filasA, columnasB);
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            double suma = 0.0;
            for (int k = 0; k < columnasA; k++) {
                suma += A[i][k] * B[k][j];
            }
            resultado[i][j] = suma;
        }
    }
    return resultado;
}

double** transponerMatriz(double** A, int filas, int columnas) {
    double** resultado = crearMatriz(columnas, filas); // OJO: dimensiones invertidas
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            resultado[j][i] = A[i][j];
    return resultado;
}

double calcularTraza(double** A, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) suma += A[i][i]; // solo la diagonal principal
    return suma;
}

static double** obtenerSubmatriz(double** A, int n, int filaExcluir, int colExcluir) {
    double** sub = crearMatriz(n - 1, n - 1);
    int filaDestino = 0;
    for (int i = 0; i < n; i++) {
        if (i == filaExcluir) continue;
        int colDestino = 0;
        for (int j = 0; j < n; j++) {
            if (j == colExcluir) continue;
            sub[filaDestino][colDestino] = A[i][j];
            colDestino++;
        }
        filaDestino++;
    }
    return sub;
}

double calcularDeterminante(double** A, int n) {
    if (n == 1) {
        return A[0][0];
    }
    if (n == 2) {
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    }

    double determinante = 0.0;
    for (int j = 0; j < n; j++) {
        double** sub = obtenerSubmatriz(A, n, 0, j); // eliminamos fila 0, columna j
        double signo = (j % 2 == 0) ? 1.0 : -1.0;    // (-1)^(0+j)
        determinante += signo * A[0][j] * calcularDeterminante(sub, n - 1); // <-- RECURSION
        liberarMatriz(sub, n - 1); // liberamos la submatriz temporal, sin fugas
    }
    return determinante;
}


bool resolverGaussJordan(double** aumentada, int n, double soluciones[]) {
    const double EPSILON = 1e-9;

    for (int col = 0; col < n; col++) {
        // 1) Pivoteo parcial: buscamos la fila con mayor valor absoluto
        //    en esta columna, para evitar dividir entre numeros muy chicos.
        int filaPivote = col;
        double maxValor = fabs(aumentada[col][col]);
        for (int f = col + 1; f < n; f++) {
            if (fabs(aumentada[f][col]) > maxValor) {
                maxValor = fabs(aumentada[f][col]);
                filaPivote = f;
            }
        }

        if (maxValor < EPSILON) {
            return false; // sistema sin solucion unica (columna toda en cero)
        }

        if (filaPivote != col) {
            swap(aumentada[col], aumentada[filaPivote]);
        }

        double pivote = aumentada[col][col];
        for (int j = 0; j <= n; j++) {
            aumentada[col][j] /= pivote;
        }

        for (int f = 0; f < n; f++) {
            if (f == col) continue;
            double factor = aumentada[f][col];
            for (int j = 0; j <= n; j++) {
                aumentada[f][j] -= factor * aumentada[col][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        soluciones[i] = aumentada[i][n];
    }
    return true;
}
