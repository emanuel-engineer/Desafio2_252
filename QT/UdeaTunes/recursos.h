#ifndef RECURSOS_H
#define RECURSOS_H

#include <cstddef>

// Clase para medicion de recursos del sistema
class Recursos {
private:
    static long long contadorIteraciones;

public:
    // Inicializar contador
    static void inicializar();

    // Incrementar iteraciones
    static void incrementarIteraciones(long long cantidad = 1);

    // Obtener iteraciones
    static long long getIteraciones();

    // Resetear contador
    static void resetear();

    // Mostrar metricas
    static void mostrarMetricas(size_t memoriaTotal);

    // Formatear bytes a formato legible
    static void mostrarMemoriaFormateada(size_t bytes);
};

#endif
