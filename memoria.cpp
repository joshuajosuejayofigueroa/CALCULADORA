#include "memoria.h"
#include <iostream>
#include <iomanip>

using namespace std;

void guardarResultado(MemoriaCalculadora &memoria, const string &expresionTexto, double resultado) {
    memoria.Ans = resultado;

    if (memoria.cantidadGuardada >= MAXIMO_HISTORIAL) {
        for (int i = 1; i < MAXIMO_HISTORIAL; i++) {
            memoria.historial[i - 1] = memoria.historial[i];
        }
        memoria.historial[MAXIMO_HISTORIAL - 1] = {expresionTexto, resultado};
    } else {
        // Todavia hay espacio libre, lo guardo en el siguiente casillero
        memoria.historial[memoria.cantidadGuardada] = {expresionTexto, resultado};
        memoria.cantidadGuardada++;
    }
}

void guardarEnM1oM2(MemoriaCalculadora &memoria, int numeroDeMemoria) {
    if (numeroDeMemoria == 1) {
        memoria.M1 = memoria.Ans;
        cout << "Listo, guarde Ans (" << memoria.Ans << ") en M1.\n";
    } else if (numeroDeMemoria == 2) {
        memoria.M2 = memoria.Ans;
        cout << "Listo, guarde Ans (" << memoria.Ans << ") en M2.\n";
    } else {
        cout << "Esa memoria no existe, solo tengo M1 y M2.\n";
    }
}

void mostrarHistorial(const MemoriaCalculadora &memoria) {
    if (memoria.cantidadGuardada == 0) {
        cout << "Todavia no he calculado nada.\n";
        return;
    }
    cout << "\n--- Historial (ultimas " << memoria.cantidadGuardada << " operaciones) ---\n";
    for (int i = 0; i < memoria.cantidadGuardada; i++) {
        cout << "  [" << (i + 1) << "] " << memoria.historial[i].expresionTexto
             << " = " << fixed << setprecision(6) << memoria.historial[i].resultado << "\n";
    }
    cout << "-------------------------------------------------\n";
}

void mostrarVariables(const MemoriaCalculadora &memoria) {
    cout << fixed << setprecision(6);
    cout << "Ans = " << memoria.Ans << "\n";
    cout << "M1  = " << memoria.M1 << "\n";
    cout << "M2  = " << memoria.M2 << "\n";
}
