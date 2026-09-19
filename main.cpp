#include <iostream>
#include "matrices.h"

int main() {
    int n = 2;
    double** A = crearMatriz(n, n);
    
    std::cout << "--- Ingresa datos de Matriz 2x2 ---\n";
    leerMatriz(A, n, n);

    std::cout << "\nMatriz ingresada:\n";
    mostrarMatriz(A, n, n);

    std::cout << "\nDeterminante: " << calcularDeterminante(A, n) << "\n";

    liberarMatriz(A, n);
    return 0;
}
