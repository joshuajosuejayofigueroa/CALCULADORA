#include "calculadora.h"

int main() {
    int opcionPrincipal = 0;

    double Ans = 0.0;
    double M1 = 0.0;
    double M2 = 0.0;

    do {
        cout << "\n--- CALCULADORA CIENTIFICA Y MATRICIAL ---\n";
        cout << "1. Operaciones Basicas\n";
        cout << "2. Modulo Cientifico\n";
        cout << "3. Modulo de Matrices\n";
        cout << "4. Gestion de Memoria\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcionPrincipal;

        if (opcionPrincipal == 1) {
            operacionesBasicas(Ans);

        } else if (opcionPrincipal == 2) {
            int opCientifica = 0;
            cout << "\n--- MODULO CIENTIFICO ---\n";
            cout << "1. Potencia\n";
            cout << "2. Factorial\n";
            cout << "3. Seno\n";
            cout << "4. Coseno\n";
            cout << "5. Exponencial (e^x)\n";
            cout << "6. Logaritmo Natural (ln)\n";
            cout << "Ingrese opcion: ";
            cin >> opCientifica;

            if (opCientifica == 1) {
                double base;
                int exponente;
                cout << "Ingrese la base: "; cin >> base;
                cout << "Ingrese el exponente: "; cin >> exponente;
                Ans = potencia(base, exponente);
                cout << "Resultado: " << Ans << endl;

            } else if (opCientifica == 2) {
                int numero;
                cout << "Ingrese un numero entero: "; cin >> numero;
                Ans = factorial(numero);
                cout << "Resultado: " << Ans << endl;

            } else if (opCientifica == 3) {
                double angulo;
                int n;
                cout << "Ingrese el angulo en grados: "; cin >> angulo;
                cout << "Ingrese el grado del polinomio de Taylor (N): "; cin >> n;
                Ans = seno(angulo, n);
                cout << "Resultado sin(" << angulo << "deg): " << Ans << endl;

            } else if (opCientifica == 4) {
                double angulo;
                int n;
                cout << "Ingrese el angulo en grados: "; cin >> angulo;
                cout << "Ingrese el grado del polinomio de Taylor (N): "; cin >> n;
                Ans = coseno(angulo, n);
                cout << "Resultado cos(" << angulo << "deg): " << Ans << endl;

            } else if (opCientifica == 5) {
                double x;
                int n;
                cout << "Ingrese el exponente (x): "; cin >> x;
                cout << "Ingrese el grado del polinomio de Taylor (N): "; cin >> n;
                Ans = exponencial(x, n);
                cout << "Resultado e^" << x << ": " << Ans << endl;

            } else if (opCientifica == 6) {
                double x;
                int n;
                cout << "Ingrese el valor x (ej. 1.5): "; cin >> x;
                cout << "Ingrese el grado del polinomio de Taylor (N): "; cin >> n;
                Ans = logaritmo(x, n);
                cout << "Resultado ln(" << x << "): " << Ans << endl;
            }

        } else if (opcionPrincipal == 3) {
            int opMatrices = 0;
            cout << "\n--- MODULO DE MATRICES ---\n";
            cout << "1. Sumar Matrices\n";
            cout << "2. Restar Matrices\n";
            cout << "3. Multiplicar Matrices\n";
            cout << "4. Transpuesta\n";
            cout << "5. Traza\n";
            cout << "6. Determinante (Laplace)\n";
            cout << "7. Resolver Sistema NxN (Gauss-Jordan)\n";
            cout << "Ingrese opcion: ";
            cin >> opMatrices;

            if (opMatrices == 1) {
                int filas, columnas;
                cout << "Ingrese filas y columnas: "; cin >> filas >> columnas;
                double** A = crearMatriz(filas, columnas);
                double** B = crearMatriz(filas, columnas);
                cout << "Matriz A:\n"; leerMatriz(A, filas, columnas);
                cout << "Matriz B:\n"; leerMatriz(B, filas, columnas);
                double** R = sumarMatrices(A, B, filas, columnas);
                cout << "Resultado:\n"; mostrarMatriz(R, filas, columnas);
                liberarMatriz(A, filas); liberarMatriz(B, filas); liberarMatriz(R, filas);
            } else if (opMatrices == 2) {
                int filas, columnas;
                cout << "Ingrese filas y columnas: "; cin >> filas >> columnas;
                double** A = crearMatriz(filas, columnas);
                double** B = crearMatriz(filas, columnas);
                cout << "Matriz A:\n"; leerMatriz(A, filas, columnas);
                cout << "Matriz B:\n"; leerMatriz(B, filas, columnas);
                double** R = restarMatrices(A, B, filas, columnas);
                cout << "Resultado:\n"; mostrarMatriz(R, filas, columnas);
                liberarMatriz(A, filas); liberarMatriz(B, filas); liberarMatriz(R, filas);
            } else if (opMatrices == 3) {
                int filasA, columnasA, filasB, columnasB;
                cout << "Filas y columnas de A: "; cin >> filasA >> columnasA;
                cout << "Filas y columnas de B: "; cin >> filasB >> columnasB;
                if (columnasA != filasB) {
                    cout << "No se pueden multiplicar las matrices.\n";
                } else {
                    double** A = crearMatriz(filasA, columnasA);
                    double** B = crearMatriz(filasB, columnasB);
                    cout << "Matriz A:\n"; leerMatriz(A, filasA, columnasA);
                    cout << "Matriz B:\n"; leerMatriz(B, filasB, columnasB);
                    double** R = multiplicarMatrices(A, filasA, columnasA, B, filasB, columnasB);
                    cout << "Resultado:\n"; mostrarMatriz(R, filasA, columnasB);
                    liberarMatriz(A, filasA); liberarMatriz(B, filasB); liberarMatriz(R, filasA);
                }
            } else if (opMatrices == 4) {
                int filas, columnas;
                cout << "Ingrese filas y columnas: "; cin >> filas >> columnas;
                double** A = crearMatriz(filas, columnas);
                cout << "Matriz A:\n"; leerMatriz(A, filas, columnas);
                double** T = transponerMatriz(A, filas, columnas);
                cout << "Transpuesta:\n"; mostrarMatriz(T, columnas, filas);
                liberarMatriz(A, filas); liberarMatriz(T, columnas);
            } else if (opMatrices == 5) {
                int tamanio;
                cout << "Ingrese tamanio de matriz cuadrada: "; cin >> tamanio;
                double** A = crearMatriz(tamanio, tamanio);
                cout << "Matriz A:\n"; leerMatriz(A, tamanio, tamanio);
                Ans = calcularTraza(A, tamanio);
                cout << "Traza: " << Ans << endl;
                liberarMatriz(A, tamanio);
            } else if (opMatrices == 6) {
                int tamanio;
                cout << "Ingrese tamanio de matriz cuadrada: "; cin >> tamanio;
                double** A = crearMatriz(tamanio, tamanio);
                cout << "Matriz A:\n"; leerMatriz(A, tamanio, tamanio);
                Ans = determinante(A, tamanio);
                cout << "Determinante: " << Ans << endl;
                liberarMatriz(A, tamanio);
            } else if (opMatrices == 7) {
                resolverGaussJordan();
            }

        } else if (opcionPrincipal == 4) {
            int opMemoria = 0;
            cout << "\n--- GESTION DE MEMORIA ---\n";
            cout << "1. Ver valores\n";
            cout << "2. Guardar Ans en M1\n";
            cout << "3. Guardar Ans en M2\n";
            cout << "4. Limpiar memorias\n";
            cout << "Ingrese opcion: ";
            cin >> opMemoria;

            if (opMemoria == 1) {
                cout << "Ans = " << Ans << endl;
                cout << "M1  = " << M1 << endl;
                cout << "M2  = " << M2 << endl;
            } else if (opMemoria == 2) {
                M1 = Ans;
                cout << "Ans guardado en M1.\n";
            } else if (opMemoria == 3) {
                M2 = Ans;
                cout << "Ans guardado en M2.\n";
            } else if (opMemoria == 4) {
                M1 = 0.0;
                M2 = 0.0;
                cout << "Memorias reiniciadas.\n";
            }
        }

    } while (opcionPrincipal != 5);

    cout << "Gracias por usar la calculadora.\n";
    return 0;
}
