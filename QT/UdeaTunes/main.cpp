#include <iostream>
#include <string>
#include "sistema.h"
#include "recursos.h"

using namespace std;

void mostrarBanner() {
    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║                                                       ║\n";
    cout << "║              ♪  U d e A T u n e s  ♪                 ║\n";
    cout << "║                                                       ║\n";
    cout << "║          Sistema de Streaming Musical                ║\n";
    cout << "║                                                       ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void mostrarMenuInicio() {
    cout << "\n╔═══════════════════════════════════════════╗\n";
    cout << "║            MENU DE INICIO                ║\n";
    cout << "╠═══════════════════════════════════════════╣\n";
    cout << "║ 1. Iniciar sesion                        ║\n";
    cout << "║ 2. Ver informacion del sistema           ║\n";
    cout << "║ 3. Salir                                 ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    cout << "Seleccione opcion: ";
}

void mostrarInfoSistema() {
    cout << "\n╔════════════════════════════════════════════════════╗\n";
    cout << "║          INFORMACION DE UdeATunes                  ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "║                                                    ║\n";
    cout << "║                                                    ║\n";
    cout << "║                                                    ║\n";
    cout << "║ MEMBRESIAS DISPONIBLES:                            ║\n";
    cout << "║                                                    ║\n";
    cout << "║ • ESTANDAR (Gratis)                                ║\n";
    cout << "║   - Calidad de audio: 128 kbps                     ║\n";
    cout << "║   - Publicidad cada 2 canciones                    ║\n";
    cout << "║   - Reproduccion aleatoria                         ║\n";
    cout << "║                                                    ║\n";
    cout << "║ • PREMIUM ($19,900/mes)                            ║\n";
    cout << "║   - Calidad de audio: 320 kbps                     ║\n";
    cout << "║   - Sin publicidad                                 ║\n";
    cout << "║   - Lista de favoritos (hasta 10,000 canciones)    ║\n";
    cout << "║   - Seguir listas de otros usuarios                ║\n";
    cout << "║   - Control avanzado de reproduccion               ║\n";
    cout << "║                                                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
}

void mostrarUsuariosDisponibles() {
    cout << "\n╔═══════════════════════════════════════════════════╗\n";
    cout << "║          USUARIOS DE PRUEBA DISPONIBLES          ║\n";
    cout << "╠═══════════════════════════════════════════════════╣\n";
    cout << "║                                                   ║\n";
    cout << "║ Usuario: juan123     | Password: 1234            ║\n";
    cout << "║ Tipo: PREMIUM        | Ciudad: Medellin          ║\n";
    cout << "║                                                   ║\n";
    cout << "║ Usuario: maria_s     | Password: pass            ║\n";
    cout << "║ Tipo: ESTANDAR       | Ciudad: Bogota            ║\n";
    cout << "║                                                   ║\n";
    cout << "║ Usuario: carlos.m    | Password: abc123          ║\n";
    cout << "║ Tipo: PREMIUM        | Ciudad: Cali              ║\n";
    cout << "║                                                   ║\n";
    cout << "╚═══════════════════════════════════════════════════╝\n\n";
}

int main() {
    // Inicializar sistema
    Sistema sistema;

    mostrarBanner();

    cout << "Inicializando UdeATunes...\n";
    sistema.cargarDatos();

    int opcion = 0;

    do {
        mostrarMenuInicio();
        cin >> opcion;

        switch(opcion) {
        case 1: {
            mostrarUsuariosDisponibles();

            string nickname, password;
            cout << "Nickname: ";
            cin >> nickname;
            cout << "Password: ";
            cin >> password;

            if(sistema.iniciarSesion(nickname, password)) {
                sistema.ejecutarMenuPrincipal();
            }
            break;
        }

        case 2:
            mostrarInfoSistema();
            break;

        case 3:
            cout << "\n╔════════════════════════════════════════════╗\n";
            cout << "║  Gracias por usar UdeATunes!              ║\n";
            cout << "║  Vuelve pronto para mas musica ♪          ║\n";
            cout << "╚════════════════════════════════════════════╝\n\n";
            break;

        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n";
        }

    } while(opcion != 3);

    // Mostrar metricas finales del sistema
    cout << "\n=== METRICAS FINALES DEL SISTEMA ===\n";
    size_t memoriaTotal = sistema.calcularMemoriaTotal();
    Recursos::mostrarMetricas(memoriaTotal);

    return 0;
}
