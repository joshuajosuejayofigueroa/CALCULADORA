#include "calculadora.h"

double potencia(double base, int exponente) {
    if (exponente == 0) return 1.0;
    if (exponente < 0) return 1.0 / potencia(base, -exponente);
    return base * potencia(base, exponente - 1);
}

double factorial(int numero) {
    if (numero <= 1) return 1.0;
    return numero * factorial(numero - 1);
}

double seno(double x) {
    double suma = 0.0;
    for (int i = 0; i < 10; i++) {
        double termino = potencia(-1, i) * potencia(x, 2 * i + 1) / factorial(2 * i + 1);
        suma = suma + termino;
    }
    return suma;
}

double coseno(double x) {
    double suma = 0.0;
    for (int i = 0; i < 10; i++) {
        double termino = potencia(-1, i) * potencia(x, 2 * i) / factorial(2 * i);
        suma = suma + termino;
    }
    return suma;
}

double exponencial(double x) {
    double suma = 0.0;
    for (int i = 0; i < 15; i++) {
        double termino = potencia(x, i) / factorial(i);
        suma = suma + termino;
    }
    return suma;
}

double logaritmo(double x) {
    if (x <= 0) return 0.0;
    double u = (x - 1.0) / (x + 1.0);
    double suma = 0.0;
    for (int i = 0; i < 15; i++) {
        double termino = (1.0 / (2 * i + 1)) * potencia(u, 2 * i + 1);
        suma = suma + termino;
    }
    return 2.0 * suma;
}

double** crearMatriz(int filas, int columnas) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new double[columnas];
    }
    return matriz;
}

void liberarMatriz(double** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    matriz = nullptr;
}

void leerMatriz(double** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "Ingrese elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
}

void imprimirMatriz(double** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << "\n";
    }
}

double** sumarMatrices(double** matrizA, double** matrizB, int filas, int columnas) {
    double** resultado = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    return resultado;
}

double** restarMatrices(double** matrizA, double** matrizB, int filas, int columnas) {
    double** resultado = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = matrizA[i][j] - matrizB[i][j];
        }
    }
    return resultado;
}

double** multiplicarMatrices(double** matrizA, double** matrizB, int filasA, int columnasA, int columnasB) {
    double** resultado = crearMatriz(filasA, columnasB);
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < columnasA; k++) {
                resultado[i][j] = resultado[i][j] + (matrizA[i][k] * matrizB[k][j]);
            }
        }
    }
    return resultado;
}

double** obtenerTranspuesta(double** matriz, int filas, int columnas) {
    double** resultado = crearMatriz(columnas, filas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[j][i] = matriz[i][j];
        }
    }
    return resultado;
}

double obtenerTraza(double** matriz, int filas) {
    double suma = 0.0;
    for (int i = 0; i < filas; i++) {
        suma = suma + matriz[i][i];
    }
    return suma;
}

double obtenerDeterminante(double** matriz, int dimension) {
    if (dimension == 1) {
        return matriz[0][0];
    }
    if (dimension == 2) {
        return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    }

    double determinante = 0.0;
    for (int columnaActual = 0; columnaActual < dimension; columnaActual++) {
        double** submatriz = crearMatriz(dimension - 1, dimension - 1);
        int subFila = 0;
        
        for (int i = 1; i < dimension; i++) {
            int subColumna = 0;
            for (int j = 0; j < dimension; j++) {
                if (j != columnaActual) {
                    submatriz[subFila][subColumna] = matriz[i][j];
                    subColumna++;
                }
            }
            subFila++;
        }

        double signo = potencia(-1, columnaActual);
        determinante = determinante + (signo * matriz[0][columnaActual] * obtenerDeterminante(submatriz, dimension - 1));
        liberarMatriz(submatriz, dimension - 1);
    }
    return determinante;
}
