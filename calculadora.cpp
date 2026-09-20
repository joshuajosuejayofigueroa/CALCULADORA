#include "calculadora.h"
#include <iostream>

using namespace std;
#define PI 3.14159265358979323846

// =======================================================
// EVALUADOR DE EXPRESIONES ARITMETICAS (OPERACIONES BASICAS)
// =======================================================

// Declaraciones previas de las funciones para que la recursion funcione sin problemas
double evaluarExpresion(char texto[], int& posicion);
double evaluarTermino(char texto[], int& posicion);
double evaluarFactor(char texto[], int& posicion);

// Ignora los espacios en blanco ingresados por el usuario
void omitirEspacios(char texto[], int& posicion) {
    while (texto[posicion] == ' ') {
        posicion++;
    }
}

// Nivel 3: Numeros, Parentesis (), Potencias (^) y Factoriales (!)
double evaluarFactor(char texto[], int& posicion) {
    omitirEspacios(texto, posicion);
    double resultado = 0.0;

    // Si encontramos un parentesis de apertura
    if (texto[posicion] == '(') {
        posicion++; // Avanzar despues del '('
        resultado = evaluarExpresion(texto, posicion); // Evaluar lo que esta adentro
        omitirEspacios(texto, posicion);
        if (texto[posicion] == ')') {
            posicion++; // Avanzar despues del ')'
        }
    } 
    // Si encontramos un numero
    else {
        double valorEntero = 0.0;
        while (texto[posicion] >= '0' && texto[posicion] <= '9') {
            valorEntero = valorEntero * 10.0 + (texto[posicion] - '0');
            posicion++;
        }
        resultado = valorEntero;

        // Si el numero tiene punto decimal
        if (texto[posicion] == '.') {
            posicion++;
            double factorDecimal = 0.1;
            while (texto[posicion] >= '0' && texto[posicion] <= '9') {
                resultado = resultado + (texto[posicion] - '0') * factorDecimal;
                factorDecimal = factorDecimal / 10.0;
                posicion++;
            }
        }
    }

    omitirEspacios(texto, posicion);

    // Operador Potencia ^
    if (texto[posicion] == '^') {
        posicion++;
        double exponente = evaluarFactor(texto, posicion);
        resultado = potencia(resultado, (int)exponente);
    }

    // Operador Factorial !
    if (texto[posicion] == '!') {
        posicion++;
        if (resultado < 0) {
            cout << "Error: Factorial de un numero negativo no existe.\n";
            return 0.0;
        }
        resultado = factorial((int)resultado);
    }

    return resultado;
}

// Nivel 2: Multiplicacion (*), Division (/) y Modulo (%)
double evaluarTermino(char texto[], int& posicion) {
    double valorIzquierda = evaluarFactor(texto, posicion);
    omitirEspacios(texto, posicion);

    while (texto[posicion] == '*' || texto[posicion] == '/' || texto[posicion] == '%') {
        char operador = texto[posicion];
        posicion++;

        double valorDerecha = evaluarFactor(texto, posicion);

        if (operador == '*') {
            valorIzquierda = valorIzquierda * valorDerecha;
        } else if (operador == '/') {
            if (valorDerecha == 0) {
                cout << "Error: Division por cero no permitida.\n";
                return 0.0;
            }
            valorIzquierda = valorIzquierda / valorDerecha;
        } else if (operador == '%') {
            if ((int)valorDerecha == 0) {
                cout << "Error: Modulo por cero no permitido.\n";
                return 0.0;
            }
            valorIzquierda = (int)valorIzquierda % (int)valorDerecha;
        }
        omitirEspacios(texto, posicion);
    }
    return valorIzquierda;
}

// Nivel 1: Suma (+) y Resta (-)
double evaluarExpresion(char texto[], int& posicion) {
    double valorIzquierda = evaluarTermino(texto, posicion);
    omitirEspacios(texto, posicion);

    while (texto[posicion] == '+' || texto[posicion] == '-') {
        char operador = texto[posicion];
        posicion++;

        double valorDerecha = evaluarTermino(texto, posicion);

        if (operador == '+') {
            valorIzquierda = valorIzquierda + valorDerecha;
        } else if (operador == '-') {
            valorIzquierda = valorIzquierda - valorDerecha;
        }
        omitirEspacios(texto, posicion);
    }
    return valorIzquierda;
}

// Funcion principal de Operaciones Basicas / Evaluador de Expresiones
void operacionesBasicas(double& Ans) {
    char expresion[100];
    cout << "\n--- EVALUADOR DE EXPRESIONES ARITMETICAS ---\n";
    cout << "Ingrese la expresion (ejemplo: (3+5)*2^3!): ";
    
    cin.ignore();
    cin.getline(expresion, 100);

    int posicionInicio = 0;
    Ans = evaluarExpresion(expresion, posicionInicio);
    cout << "Resultado: " << Ans << endl;
}


// ==========================================
// MODULO CIENTIFICO (SERIES DE TAYLOR)
// ==========================================

double potencia(double base, int exponente) {
    if (exponente == 0) return 1.0;
    if (exponente < 0) return 1.0 / potencia(base, -exponente);
    return base * potencia(base, exponente - 1);
}

double factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1.0;
    return (double)n * factorial(n - 1);
}

double senoTaylor(double x, int n) {
    if (n == 0) return x;
    double signo = (n % 2 == 0) ? 1.0 : -1.0;
    double termino = signo * potencia(x, 2 * n + 1) / factorial(2 * n + 1);
    return termino + senoTaylor(x, n - 1);
}

double seno(double grados, int n) {
    double rad = grados * (PI / 180.0);
    return senoTaylor(rad, n);
}

double cosenoTaylor(double x, int n) {
    if (n == 0) return 1.0;
    double signo = (n % 2 == 0) ? 1.0 : -1.0;
    double termino = signo * potencia(x, 2 * n) / factorial(2 * n);
    return termino + cosenoTaylor(x, n - 1);
}

double coseno(double grados, int n) {
    double rad = grados * (PI / 180.0);
    return cosenoTaylor(rad, n);
}

double exponencialTaylor(double x, int n) {
    if (n == 0) return 1.0;
    return (potencia(x, n) / factorial(n)) + exponencialTaylor(x, n - 1);
}

double exponencial(double x, int grado) {
    if (grado < 0) {
        cout << "Error: El grado del polinomio no puede ser negativo.\n";
        return 0.0;
    }
    return exponencialTaylor(x, grado);
}

double logaritmoTaylor(double y, int n) {
    if (n == 1) return y;
    double signo = (n % 2 == 0) ? -1.0 : 1.0;
    double termino = signo * potencia(y, n) / n;
    return termino + logaritmoTaylor(y, n - 1);
}

double logaritmo(double x, int grado) {
    if (x <= 0) {
        cout << "Error: El logaritmo solo esta definido para x > 0.\n";
        return 0.0;
    }

    if (grado <= 0) {
        cout << "Error: El grado del polinomio debe ser mayor a 0.\n";
        return 0.0;
    }

    double y = x - 1.0;
    return logaritmoTaylor(y, grado);
}


// ==========================================
// MODULO DE MATRICES Y ALGEBRA LINEAL
// ==========================================

double** crearMatriz(int filas, int columnas) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new double[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0.0;
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
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
}

void mostrarMatriz(double** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

double** sumarMatrices(double** A, double** B, int filas, int columnas) {
    double** R = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            R[i][j] = A[i][j] + B[i][j];
        }
    }
    return R;
}

double** restarMatrices(double** A, double** B, int filas, int columnas) {
    double** R = crearMatriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            R[i][j] = A[i][j] - B[i][j];
        }
    }
    return R;
}

double** multiplicarMatrices(double** A, int fA, int cA, double** B, int fB, int cB) {
    if (cA != fB) return nullptr;
    double** R = crearMatriz(fA, cB);
    for (int i = 0; i < fA; i++) {
        for (int j = 0; j < cB; j++) {
            R[i][j] = 0;
            for (int k = 0; k < cA; k++) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return R;
}

double** transponerMatriz(double** A, int filas, int columnas) {
    double** T = crearMatriz(columnas, filas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            T[j][i] = A[i][j];
        }
    }
    return T;
}

double calcularTraza(double** A, int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += A[i][i];
    }
    return suma;
}

double determinante(double** A, int n) {
    if (n == 1) return A[0][0];
    if (n == 2) return (A[0][0] * A[1][1] - A[0][1] * A[1][0]);

    double det = 0;
    for (int p = 0; p < n; p++) {
        double** subMatriz = crearMatriz(n - 1, n - 1);
        for (int i = 1; i < n; i++) {
            int colSub = 0;
            for (int j = 0; j < n; j++) {
                if (j == p) continue;
                subMatriz[i - 1][colSub] = A[i][j];
                colSub++;
            }
        }
        double signo = (p % 2 == 0) ? 1.0 : -1.0;
        det += signo * A[0][p] * determinante(subMatriz, n - 1);
        liberarMatriz(subMatriz, n - 1);
    }
    return det;
}

void resolverGaussJordan() {
    int n;
    cout << "Ingrese el numero de variables (N para matriz N x N): ";
    cin >> n;

    double** A = crearMatriz(n, n + 1);

    cout << "\nIngrese la matriz aumentada [A|b]:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
        cout << "Termino independiente b[" << i << "]: ";
        cin >> A[i][n];
    }

    for (int i = 0; i < n; i++) {
        if (A[i][i] == 0) {
            for (int k = i + 1; k < n; k++) {
                if (A[k][i] != 0) {
                    for (int j = 0; j <= n; j++) {
                        double temp = A[i][j];
                        A[i][j] = A[k][j];
                        A[k][j] = temp;
                    }
                    break;
                }
            }
        }

        double pivote = A[i][i];
        if (pivote == 0) {
            cout << "\nEl sistema no tiene solucion unica.\n";
            liberarMatriz(A, n);
            return;
        }

        for (int j = 0; j <= n; j++) {
            A[i][j] /= pivote;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j <= n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
    }

    cout << "\nSolucion del sistema:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << A[i][n] << endl;
    }
    liberarMatriz(A, n);
}
