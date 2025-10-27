#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "credito.h"

class Cancion {
private:
    int id; // 9 digitos: 5 artista + 2 album + 2 cancion
    std::string nombre;
    int duracion; // en segundos
    std::string rutaBase; // ruta sin el bitrate
    int reproducciones;

    // Creditos (arrays dinamicos)
    Credito* productores;
    int numProductores;
    int capacidadProductores;

    Credito* musicos;
    int numMusicos;
    int capacidadMusicos;

    Credito* compositores;
    int numCompositores;
    int capacidadCompositores;

public:
    // Constructores
    Cancion();
    Cancion(int id, const std::string& nom, int dur, const std::string& ruta);
    Cancion(const Cancion& otra); // Constructor de copia

    // Destructor
    ~Cancion();

    // Getters
    int getId() const;
    std::string getNombre() const;
    int getDuracion() const;
    std::string getRutaBase() const;
    std::string getRutaAudio(int bitrate) const; // 128 o 320
    int getReproducciones() const;
    int getIdArtista() const;
    int getIdAlbum() const;
    int getIdCancion() const;

    // Setters
    void setNombre(const std::string& nom);
    void setDuracion(int dur);
    void setRutaBase(const std::string& ruta);

    // Manejo de creditos
    void agregarProductor(const Credito& prod);
    void agregarMusico(const Credito& mus);
    void agregarCompositor(const Credito& comp);

    // Operaciones
    void incrementarReproducciones();
    void mostrarInfo() const;
    void mostrarCreditos() const;

    // Sobrecarga de operadores
    Cancion& operator=(const Cancion& otra);
    bool operator==(const Cancion& otra) const;

    // Calcular memoria
    size_t calcularMemoria() const;

private:
    void copiarCreditos(const Cancion& otra);
    void liberarCreditos();
    void expandirProductores();
    void expandirMusicos();
    void expandirCompositores();
};

#endif
