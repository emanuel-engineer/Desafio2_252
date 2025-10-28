#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
#include "cancion.h"

using namespace std;

class Playlist {
private:
    string nombre;
    string propietario; // nickname del usuario

    // Array de IDs de canciones (max 10000)
    int* idsCanciones;
    int numCanciones;
    int capacidadMax;

public:
    // Constructores
    Playlist();
    Playlist(const string& nom, const string& prop);
    Playlist(const Playlist& otra); // Constructor de copia

    // Destructor
    ~Playlist();

    // Getters
    string getNombre() const;
    string getPropietario() const;
    int getNumCanciones() const;
    int getIdCancion(int index) const;

    // Setters
    void setNombre(const string& nom);

    // Operaciones
    bool agregarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    bool contieneCancion(int idCancion) const;
    void limpiar();
    void mostrarInfo() const;

    // Fusionar con otra playlist
    void fusionarCon(const Playlist& otra);

    // Sobrecarga de operadores
    Playlist& operator=(const Playlist& otra);
    bool operator==(const Playlist& otra) const;
    Playlist operator+(const Playlist& otra) const; // Fusionar playlists

    // Calcular memoria
    size_t calcularMemoria() const;

private:
    void expandirCapacidad();
};

#endif
