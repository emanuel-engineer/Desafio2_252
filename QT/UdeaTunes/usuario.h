#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "playlist.h"
using namespace std;

// Tipo de membresia
enum TipoMembresia {
    ESTANDAR,
    PREMIUM
};

class Usuario {
private:
    string nickname; // Unico
    string password;
    TipoMembresia membresia;
    string ciudad;
    string pais;
    string fechaInscripcion;

    // Playlist de favoritos (solo premium)
    Playlist* listaFavoritos;

    // Historial de reproduccion (para funcionalidad "previa")
    int* historialIds;
    int numHistorial;
    int capacidadHistorial;
    int posicionActual;

public:
    // Constructores
    Usuario();
    Usuario(const string& nick, const string& pass,
            TipoMembresia memb, const string& city,
            const string& country, const string& fecha);
    Usuario(const Usuario& otro); // Constructor de copia

    // Destructor
    ~Usuario();

    // Getters
    string getNickname() const;
    string getPassword() const;
    TipoMembresia getMembresia() const;
    string getMembresiaStr() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;
    Playlist* getListaFavoritos();
    int getBitrate() const; // 128 o 320

    // Setters
    void setMembresia(TipoMembresia memb);
    void setCiudad(const string& city);

    // Operaciones con favoritos (solo premium)
    bool agregarFavorito(int idCancion);
    bool eliminarFavorito(int idCancion);
    void seguirListaFavoritos(const Playlist& otra);

    // Historial
    void agregarAlHistorial(int idCancion);
    int obtenerCancionPrevia(int pasos); // -1 si no existe
    void limpiarHistorial();

    // Verificacion
    bool verificarPassword(const string& pass) const;
    bool esPremium() const;

    // Mostrar informacion
    void mostrarInfo() const;

    // Sobrecarga de operadores
    Usuario& operator=(const Usuario& otro);
    bool operator==(const Usuario& otro) const;

    // Calcular memoria
    size_t calcularMemoria() const;

private:
    void liberarMemoria();
    void copiarDatos(const Usuario& otro);
    void expandirHistorial();
};

#endif
