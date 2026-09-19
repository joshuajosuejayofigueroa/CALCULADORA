#ifndef MEMORIA_H
#define MEMORIA_H

#include <string>

const int MAXIMO_HISTORIAL = 50; 

struct OperacionGuardada {
    std::string expresionTexto;
    double resultado;
};

struct MemoriaCalculadora {
    double Ans = 0.0;
    double M1 = 0.0;
    double M2 = 0.0;
    OperacionGuardada historial[MAXIMO_HISTORIAL];
    int cantidadGuardada = 0; 
};

void guardarResultado(MemoriaCalculadora &memoria, const std::string &expresionTexto, double resultado);

void guardarEnM1oM2(MemoriaCalculadora &memoria, int numeroDeMemoria); 

void mostrarHistorial(const MemoriaCalculadora &memoria);

// Imprime en pantalla el valor actual de Ans, M1 y M2.
void mostrarVariables(const MemoriaCalculadora &memoria);

#endif
