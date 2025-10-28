#ifndef SISTEMA_H
#define SISTEMA_H
#include "usuario.h"
#include "artista.h"
#include "anuncio.h"
#include <string>

using namespace std;
class Sistema {
private:
    // Arrays dinamicos
    Usuario** usuarios;
    int numUsuarios;
    int capacidadUsuarios;

    Artista** artistas;
    int numArtistas;
    int capacidadArtistas;

    Anuncio** anuncios;
    int numAnuncios;
    int capacidadAnuncios;

    // Usuario actual
    Usuario* usuarioActual;

    // Configuracion reproduccion
    bool reproduciendo;
    int cancionesReproducidas;
    int ultimoAnuncioMostrado;


    std::string reemplazarGuionesBajos(const std::string& str);
    void saltarLineasComentario(std::ifstream& archivo);
    void cargarArtistasHardcoded();

public:
    // Constructor y destructor
    Sistema();
    ~Sistema();

    // Carga de datos
    void cargarDatos();
    void cargarUsuarios();
    void cargarArtistas();
    void cargarAnuncios();
    void guardarDatos();

    // Gestion usuarios
    Usuario* buscarUsuario(const string& nickname);
    bool iniciarSesion(const string& nickname, const string& password);
    void cerrarSesion();
    Usuario* getUsuarioActual();

    // Gestion artistas y canciones
    Artista* buscarArtista(int id);
    Cancion* buscarCancion(int idCancion);
    void listarArtistas() const;

    // Reproduccion
    void reproduccionAleatoria();
    void reproducirListaFavoritos(bool aleatorio);
    void mostrarAnuncio();
    Anuncio* seleccionarAnuncioPorPrioridad();

    // Menu principal
    void mostrarMenuPrincipal();
    void ejecutarMenuPrincipal();

    // Menu favoritos (premium)
    void menuFavoritos();
    void editarFavoritos();
    void seguirOtraLista();
    void ejecutarFavoritos();

    // Calcular memoria total
    size_t calcularMemoriaTotal() const;

private:
    void liberarMemoria();
    void expandirUsuarios();
    void expandirArtistas();
    void expandirAnuncios();

    // Funciones auxiliares
    int generarAleatorio(int min, int max);
    void pausa(int segundos);
    void limpiarPantalla();
};

#endif
