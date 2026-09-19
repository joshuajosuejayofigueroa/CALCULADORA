#include <iostream>
#include "calculadora.h"

using namespace std;

int main() {
    double respuestaAnterior = 0.0;
    double memoria1 = 0.0;
    double memoria2 = 0.0;
    
    int opcionPrincipal = 0;

    while (opcionPrincipal != 4) {
        cout << "\n=== CALCULADORA CIENTIFICA Y MATRICIAL ===\n";
        cout << "1. Modulo Cientifico\n";
        cout << "2. Modulo de Matrices\n";
        cout << "3. Ver Variables de Memoria\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcionPrincipal;

        if (opcionPrincipal == 1) {
            int opcionCientifica = 0;
            cout << "\n--- MODULO CIENTIFICO ---\n";
            cout << "1. Potencia\n";
            cout << "2. Factorial\n";
            cout << "3. Seno\n";
            cout << "4. Coseno\n";
            cout << "5. Exponencial (e^x)\n";
            cout << "6. Logaritmo Natural (ln)\n";
            cout << "Ingrese opcion: ";
            cin >> opcionCientifica;

            if (opcionCientifica == 1) {
                double base;
                int exponente;
                cout << "Ingrese la base: ";
                cin >> base;
                cout << "Ingrese el exponente entero: ";
                cin >> exponente;
                respuestaAnterior = potencia(base, exponente);
                cout << "Resultado: " << respuestaAnterior << "\n";
            } else if (opcionCientifica == 2) {
                int numero;
                cout << "Ingrese un numero entero positivo: ";
                cin >> numero;
                if (numero < 0) {
                    cout << "Error: Numero negativo.\n";
                } else {
                    respuestaAnterior = factorial(numero);
                    cout << "Resultado: " << respuestaAnterior << "\n";
                }
            } else if (opcionCientifica == 3) {
                double x;
                cout << "Ingrese x (en radianes): ";
                cin >> x;
                respuestaAnterior = seno(x);
                cout << "Resultado: " << respuestaAnterior << "\n";
            } else if (opcionCientifica == 4) {
                double x;
                cout << "Ingrese x (en radianes): ";
                cin >> x;
                respuestaAnterior = coseno(x);
                cout << "Resultado: " << respuestaAnterior << "\n";
            } else if (opcionCientifica == 5) {
                double x;
                cout << "Ingrese x: ";
                cin >> x;
                respuestaAnterior = exponencial(x);
                cout << "Resultado: " << respuestaAnterior << "\n";
            } else if (opcionCientifica == 6) {
                double x;
                cout << "Ingrese x: ";
                cin >> x;
                if (x <= 0) {
                    cout << "Error: El numero debe ser mayor a 0.\n";
                } else {
                    respuestaAnterior = logaritmo(x);
                    cout << "Resultado: " << respuestaAnterior << "\n";
                }
            }

            cout << "\nGuardar resultado en memoria? (1: Guardar en M1, 2: Guardar en M2, 0: No guardar): ";
            int opcionMemoria;
            cin >> opcionMemoria;
            if (opcionMemoria == 1) memoria1 = respuestaAnterior;
            if (opcionMemoria == 2) memoria2 = respuestaAnterior;

        } else if (opcionPrincipal == 2) {
            int opcionMatrices = 0;
            cout << "\n--- MODULO DE MATRICES ---\n";
            cout << "1. Sumar Matrices\n";
            cout << "2. Restar Matrices\n";
            cout << "3. Multiplicar Matrices\n";
            cout << "4. Transpuesta\n";
            cout << "5. Traza\n";
            cout << "6. Determinante\n";
            cout << "Ingrese opcion: ";
            cin >> opcionMatrices;

            if (opcionMatrices == 1 || opcionMatrices == 2) {
                int filas, columnas;
                cout << "Ingrese numero de filas: ";
                cin >> filas;
                cout << "Ingrese numero de columnas: ";
                cin >> columnas;

                double** matrizA = crearMatriz(filas, columnas);
                double** matrizB = crearMatriz(filas, columnas);

                cout << "\nDatos de la Matriz A:\n";
                leerMatriz(matrizA, filas, columnas);
                cout << "\nDatos de la Matriz B:\n";
                leerMatriz(matrizB, filas, columnas);

                double** resultado = nullptr;
                if (opcionMatrices == 1) {
                    resultado = sumarMatrices(matrizA, matrizB, filas, columnas);
                    cout << "\nResultado de la Suma:\n";
                } else {
                    resultado = restarMatrices(matrizA, matrizB, filas, columnas);
                    cout << "\nResultado de la Resta:\n";
                }

                imprimirMatriz(resultado, filas, columnas);

                liberarMatriz(matrizA, filas);
                liberarMatriz(matrizB, filas);
                liberarMatriz(resultado, filas);

            } else if (opcionMatrices == 3) {
                int filasA, columnasA, columnasB;
                cout << "Ingrese filas de Matriz A: ";
                cin >> filasA;
                cout << "Ingrese columnas de Matriz A (y filas de Matriz B): ";
                cin >> columnasA;
                cout << "Ingrese columnas de Matriz B: ";
                cin >> columnasB;

                double** matrizA = crearMatriz(filasA, columnasA);
                double** matrizB = crearMatriz(columnasA, columnasB);

                cout << "\nDatos de la Matriz A:\n";
                leerMatriz(matrizA, filasA, columnasA);
                cout << "\nDatos de la Matriz B:\n";
                leerMatriz(matrizB, columnasA, columnasB);

                double** resultado = multiplicarMatrices(matrizA, matrizB, filasA, columnasA, columnasB);

                cout << "\nResultado de la Multiplicacion:\n";
                imprimirMatriz(resultado, filasA, columnasB);

                liberarMatriz(matrizA, filasA);
                liberarMatriz(matrizB, columnasA);
                liberarMatriz(resultado, filasA);

            } else if (opcionMatrices == 4) {
                int filas, columnas;
                cout << "Ingrese filas: ";
                cin >> filas;
                cout << "Ingrese columnas: ";
                cin >> columnas;

                double** matriz = crearMatriz(filas, columnas);
                cout << "\nDatos de la Matriz:\n";
                leerMatriz(matriz, filas, columnas);

                double** resultado = obtenerTranspuesta(matriz, filas, columnas);
                cout << "\nMatriz Transpuesta:\n";
                imprimirMatriz(resultado, columnas, filas);

                liberarMatriz(matriz, filas);
                liberarMatriz(resultado, columnas);

            } else if (opcionMatrices == 5) {
                int dimension;
                cout << "Ingrese la dimension de la matriz cuadrada: ";
                cin >> dimension;

                double** matriz = crearMatriz(dimension, dimension);
                cout << "\nDatos de la Matriz:\n";
                leerMatriz(matriz, dimension, dimension);

                double traza = obtenerTraza(matriz, dimension);
                cout << "\nLa Traza es: " << traza << "\n";

                liberarMatriz(matriz, dimension);

            } else if (opcionMatrices == 6) {
                int dimension;
                cout << "Ingrese la dimension de la matriz cuadrada: ";
                cin >> dimension;

                double** matriz = crearMatriz(dimension, dimension);
                cout << "\nDatos de la Matriz:\n";
                leerMatriz(matriz, dimension, dimension);

                double determinante = obtenerDeterminante(matriz, dimension);
                cout << "\nEl Determinante es: " << determinante << "\n";

                liberarMatriz(matriz, dimension);
            }

        } else if (opcionPrincipal == 3) {
            cout << "\n--- MEMORIA Y VARIABLES ---\n";
            cout << "Ans (Ultima respuesta): " << respuestaAnterior << "\n";
            cout << "M1: " << memoria1 << "\n";
            cout << "M2: " << memoria2 << "\n";
        }
    }

    return 0;
}
