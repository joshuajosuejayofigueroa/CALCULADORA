#include "calculadora.h"

void operacionesBasicas(double& Ans) {
    int opcion = 0;
    cout << "\n--- OPERACIONES BASICAS ---\n";
    cout << "1. Suma (+)\n";
    cout << "2. Resta (-)\n";
    cout << "3. Multiplicacion (*)\n";
    cout << "4. Division (/)\n";
    cout << "5. Modulo (%)\n";
    cout << "Ingrese opcion: ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        double a, b;
        cout << "Ingrese el primer numero: "; cin >> a;
        cout << "Ingrese el segundo numero: "; cin >> b;

        if (opcion == 1) Ans = a + b;
        else if (opcion == 2) Ans = a - b;
        else if (opcion == 3) Ans = a * b;
        else if (opcion == 4) {
            if (b != 0) Ans = a / b;
            else {
                cout << "Error: Division por cero.\n";
                return;
            }
        }
        cout << "Resultado: " << Ans << endl;

    } else if (opcion == 5) {
        int a, b;
        cout << "Ingrese el primer numero entero: "; cin >> a;
        cout << "Ingrese el segundo numero entero: "; cin >> b;
        if (b != 0) {
            Ans = a % b;
            cout << "Resultado: " << Ans << endl;
        } else {
            cout << "Error: Division por cero.\n";
        }
    } else {
        cout << "Opcion no valida.\n";
    }
}

double potencia(double base, int exponente) {
    if (exponente == 0) return 1.0;
    if (exponente < 0) return 1.0 / potencia(base, -exponente);
    return base * potencia(base, exponente - 1);
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

double seno(double x, int n) {
    if (n == 0) return x;
    double signo = (n % 2 == 0) ? 1.0 : -1.0;
    double termino = signo * potencia(x, 2 * n + 1) / factorial(2 * n + 1);
    return termino + seno(x, n - 1);
}

double coseno(double x, int n) {
    if (n == 0) return 1.0;
    double signo = (n % 2 == 0) ? 1.0 : -1.0;
    double termino = signo * potencia(x, 2 * n) / factorial(2 * n);
    return termino + coseno(x, n - 1);
}

double exponencial(double x, int n) {
    if (n == 0) return 1.0;
    return (potencia(x, n) / factorial(n)) + exponencial(x, n - 1);
}

double logaritmo(double x, int n) {
    if (n == 1) return x;
    double signo = (n % 2 == 0) ? -1.0 : 1.0;
    double termino = signo * potencia(x, n) / n;
    return termino + logaritmo(x, n - 1);
}

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
