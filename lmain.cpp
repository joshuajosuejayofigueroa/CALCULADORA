#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include "calculo.h"
#include "memoria.h"
#include "matrices.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menuCientifico(MemoriaCalculadora &mem) {
    int opcion;
    do {
        cout << "\n--- MODULO CIENTIFICO ---\n";
        cout << "1. Evaluar expresion (+, -, *, /, ^, !, %, parentesis)\n";
        cout << "2. Potencia recursiva (entera o fraccionaria)\n";
        cout << "3. Factorial recursivo\n";
        cout << "4. sin(x), cos(x), e^x, ln(x) (Taylor recursivo)\n";
        cout << "5. Guardar Ans en M1 o M2\n";
        cout << "6. Ver variables (Ans, M1, M2)\n";
        cout << "7. Ver historial de operaciones\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        if (!(cin >> opcion)) { limpiarBuffer(); continue; }
        limpiarBuffer();

        try {
            if (opcion == 1) {
                cout << "Puedes usar Ans, M1 y M2 dentro de la expresion.\n";
                cout << "Expresion: ";
                string expr;
                getline(cin, expr);
                double resultado = evaluarExpresion(expr, mem);
                cout << "Resultado = " << resultado << "\n";
                guardarResultado(mem, expr, resultado);

            } else if (opcion == 2) {
                double base, exponente;
                cout << "Base: "; cin >> base;
                cout << "Exponente: "; cin >> exponente;
                limpiarBuffer();
                double resultado;
                if (floor(exponente) == exponente) {
                    resultado = potencia(base, static_cast<long long>(exponente));
                } else {
                    resultado = potenciaConDecimales(base, exponente);
                }
                cout << "Resultado = " << resultado << "\n";
                guardarResultado(mem, to_string(base) + "^" + to_string(exponente), resultado);

            } else if (opcion == 3) {
                long long n;
                cout << "n: "; cin >> n; limpiarBuffer();
                double resultado = factorial(n);
                cout << "Resultado = " << resultado << "\n";
                guardarResultado(mem, to_string(n) + "!", resultado);

            } else if (opcion == 4) {
                cout << "1) sin  2) cos  3) e^x  4) ln(x)\n";
                int sub; cout << "Opcion: "; cin >> sub;
                double x; cout << "x: "; cin >> x; limpiarBuffer();
                double resultado = 0;
                string etiqueta;
                if (sub == 1) { resultado = calcularSeno(x); etiqueta = "sin(" + to_string(x) + ")"; }
                else if (sub == 2) { resultado = calcularCoseno(x); etiqueta = "cos(" + to_string(x) + ")"; }
                else if (sub == 3) { resultado = calcularExp(x); etiqueta = "e^" + to_string(x); }
                else if (sub == 4) { resultado = calcularLn(x); etiqueta = "ln(" + to_string(x) + ")"; }
                else { cout << "Opcion invalida.\n"; continue; }
                cout << "Resultado = " << resultado << "\n";
                guardarResultado(mem, etiqueta, resultado);

            } else if (opcion == 5) {
                int m;
                cout << "Guardar Ans en (1) M1 o (2) M2: "; cin >> m; limpiarBuffer();
                guardarEnM1oM2(mem, m);

            } else if (opcion == 6) {
                mostrarVariables(mem);

            } else if (opcion == 7) {
                mostrarHistorial(mem);

            } else if (opcion != 0) {
                cout << "Opcion invalida.\n";
            }
        } catch (const exception &e) {
            cout << "ERROR: " << e.what() << "\n";
        }
    } while (opcion != 0);
}

void menuMatrices() {
    int opcion;
    do {
        cout << "\n--- MODULO DE ALGEBRA LINEAL ---\n";
        cout << "1. Sumar dos matrices\n";
        cout << "2. Restar dos matrices\n";
        cout << "3. Multiplicar dos matrices\n";
        cout << "4. Transponer una matriz\n";
        cout << "5. Traza de una matriz cuadrada\n";
        cout << "6. Determinante (recursivo, Laplace)\n";
        cout << "7. Resolver sistema de ecuaciones (Gauss-Jordan)\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        if (!(cin >> opcion)) { limpiarBuffer(); continue; }

        try {
            if (opcion == 1 || opcion == 2) {
                int filas, columnas;
                cout << "Filas: "; cin >> filas;
                cout << "Columnas: "; cin >> columnas;
                double** A = crearMatriz(filas, columnas);
                double** B = crearMatriz(filas, columnas);
                cout << "Matriz A:\n"; leerMatriz(A, filas, columnas);
                cout << "Matriz B:\n"; leerMatriz(B, filas, columnas);
                double** R = (opcion == 1) ? sumarMatrices(A, B, filas, columnas)
                                           : restarMatrices(A, B, filas, columnas);
                cout << "Resultado:\n"; imprimirMatriz(R, filas, columnas);
                liberarMatriz(A, filas);
                liberarMatriz(B, filas);
                liberarMatriz(R, filas);

            } else if (opcion == 3) {
                int filasA, columnasA, filasB, columnasB;
                cout << "Filas de A: "; cin >> filasA;
                cout << "Columnas de A: "; cin >> columnasA;
                cout << "Filas de B: "; cin >> filasB;
                cout << "Columnas de B: "; cin >> columnasB;
                double** A = crearMatriz(filasA, columnasA);
                double** B = crearMatriz(filasB, columnasB);
                cout << "Matriz A:\n"; leerMatriz(A, filasA, columnasA);
                cout << "Matriz B:\n"; leerMatriz(B, filasB, columnasB);
                double** R = multiplicarMatrices(A, filasA, columnasA, B, filasB, columnasB);
                cout << "Resultado:\n"; imprimirMatriz(R, filasA, columnasB);
                liberarMatriz(A, filasA);
                liberarMatriz(B, filasB);
                liberarMatriz(R, filasA);

            } else if (opcion == 4) {
                int filas, columnas;
                cout << "Filas: "; cin >> filas;
                cout << "Columnas: "; cin >> columnas;
                double** A = crearMatriz(filas, columnas);
                leerMatriz(A, filas, columnas);
                double** T = transponerMatriz(A, filas, columnas);
                cout << "Transpuesta:\n"; imprimirMatriz(T, columnas, filas);
                liberarMatriz(A, filas);
                liberarMatriz(T, columnas);

            } else if (opcion == 5) {
                int n;
                cout << "Tamano n (matriz cuadrada n x n): "; cin >> n;
                double** A = crearMatriz(n, n);
                leerMatriz(A, n, n);
                cout << "Traza = " << calcularTraza(A, n) << "\n";
                liberarMatriz(A, n);

            } else if (opcion == 6) {
                int n;
                cout << "Tamano n (matriz cuadrada n x n): "; cin >> n;
                double** A = crearMatriz(n, n);
                leerMatriz(A, n, n);
                cout << "Determinante = " << calcularDeterminante(A, n) << "\n";
                liberarMatriz(A, n);

            } else if (opcion == 7) {
                int n;
                cout << "Numero de incognitas (n): "; cin >> n;
                double** aumentada = crearMatriz(n, n + 1);
                cout << "Ingrese la matriz aumentada [A | b] (n filas, n+1 columnas):\n";
                leerMatriz(aumentada, n, n + 1);
                double* soluciones = new double[n];
                bool tieneSolucion = resolverGaussJordan(aumentada, n, soluciones);
                if (tieneSolucion) {
                    cout << "Solucion del sistema:\n";
                    for (int i = 0; i < n; i++) {
                        cout << "  x" << i + 1 << " = " << soluciones[i] << "\n";
                    }
                } else {
                    cout << "El sistema no tiene solucion unica (o es indeterminado).\n";
                }
                delete[] soluciones;
                liberarMatriz(aumentada, n);

            } else if (opcion != 0) {
                cout << "Opcion invalida.\n";
            }
        } catch (const exception &e) {
            cout << "ERROR: " << e.what() << "\n";
        }
    } while (opcion != 0);
}

int main() {
    MemoriaCalculadora mem; // toda la memoria de la calculadora vive aqui

    int opcion;
    do {
        cout << "\n=================================================\n";
        cout << "   CALCULADORA CIENTIFICA Y MATRICIAL - CS6003\n";
        cout << "=================================================\n";
        cout << "1. Modulo de Calculo Cientifico & Expresiones Escalares\n";
        cout << "2. Modulo de Algebra Lineal & Matrices Dinamicas\n";
        cout << "3. Gestion de Memoria y Registro de Operaciones\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        if (!(cin >> opcion)) { limpiarBuffer(); continue; }
        limpiarBuffer();

        if (opcion == 1) {
            menuCientifico(mem);
        } else if (opcion == 2) {
            menuMatrices();
        } else if (opcion == 3) {
            mostrarVariables(mem);
            mostrarHistorial(mem);
        } else if (opcion != 4) {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    cout << "Gracias por usar la calculadora. Hasta pronto!\n";
    return 0;
}
