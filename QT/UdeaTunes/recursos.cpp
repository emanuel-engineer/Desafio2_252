#include "recursos.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Inicializar variable estatica
long long Recursos::contadorIteraciones = 0;

void Recursos::inicializar() {
    contadorIteraciones = 0;
}

void Recursos::incrementarIteraciones(long long cantidad) {
    contadorIteraciones += cantidad;
}

long long Recursos::getIteraciones() {
    return contadorIteraciones;
}

void Recursos::resetear() {
    contadorIteraciones = 0;
}

void Recursos::mostrarMetricas(size_t memoriaTotal) {
    cout << "\n╔════════════════════════════════════════════════════╗\n";
    cout << "║           METRICAS DE CONSUMO DE RECURSOS         ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ Total de iteraciones: " << setw(28) << contadorIteraciones << " ║\n";
    cout << "║ Memoria consumida: ";
    mostrarMemoriaFormateada(memoriaTotal);
    cout << "╚════════════════════════════════════════════════════╝\n\n";
}

void Recursos::mostrarMemoriaFormateada(size_t bytes) {
    if(bytes < 1024) {
        cout << setw(26) << bytes << " B   ║\n";
    } else if(bytes < 1024 * 1024) {
        double kb = bytes / 1024.0;
        cout << fixed << setprecision(2) << setw(23) << kb << " KB  ║\n";
    } else {
        double mb = bytes / (1024.0 * 1024.0);
        cout << fixed << setprecision(2) << setw(23) << mb << " MB  ║\n";
    }
}
