#ifndef ARTISTA_H
#define ARTISTA_H
#include <string>
#include "album.h"
using namespace std;

class Artista {
private:
    int id; // 5 digitos
    string nombre;
    int edad;
    string paisOrigen;
    int seguidores;
    int posicionTendencias;

    // Catalogo de albumes
    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

public:
    // Constructores
    Artista();
    Artista(int id, const string& nom, int edad, const string& pais);
    Artista(const Artista& otro); // Constructor de copia

    // Destructor
    ~Artista();

    // Getters
    int getId() const;
    string getNombre() const;
    int getEdad() const;
    string getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionTendencias() const;
    int getNumAlbumes() const;
    Album* getAlbum(int index) const;

    // Setters
    void setNombre(const string& nom);
    void setEdad(int e);
    void setSeguidores(int seg);
    void setPosicionTendencias(int pos);

    // Manejo de albumes
    void agregarAlbum(Album* album);
    Album* buscarAlbumPorId(int idAlbum) const;
    Cancion* buscarCancionPorId(int idCancion) const;

    // Operaciones
    void mostrarInfo() const;
    void mostrarCatalogo() const;
    int getTotalCanciones() const;

    // Sobrecarga de operadores
    Artista& operator=(const Artista& otro);
    bool operator==(const Artista& otro) const;

    // Calcular memoria
    size_t calcularMemoria() const;

private:
    void liberarMemoria();
    void copiarDatos(const Artista& otro);
    void expandirAlbumes();
};

#endif
