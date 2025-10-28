#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include "cancion.h"

class Album {
private:
    int id;
    std::string nombre;
    std::string fechaLanzamiento;
    int duracionTotal; // en segundos
    std::string selloDisquero;
    std::string rutaPortada; // .png
    float puntuacion; // 1-10

    // Generos (max 4)
    std::string* generos;
    int numGeneros;

    // Canciones
    Cancion** canciones;
    int numCanciones;
    int capacidadCanciones;

public:
    // Constructores
    Album();
    Album(int id, const std::string& nom, const std::string& fecha,
          const std::string& sello, const std::string& portada);
    Album(const Album& otro); // Constructor de copia

    // Destructor
    ~Album();

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getFechaLanzamiento() const;
    int getDuracionTotal() const;
    std::string getSelloDisquero() const;
    std::string getRutaPortada() const;
    float getPuntuacion() const;
    int getNumCanciones() const;
    Cancion* getCancion(int index) const;

    // Setters
    void setNombre(const std::string& nom);
    void setPuntuacion(float punt);

    // Manejo de generos
    void agregarGenero(const std::string& genero);
    std::string getGenerosStr() const;

    // Manejo de canciones
    void agregarCancion(Cancion* cancion);
    Cancion* buscarCancionPorId(int idCancion) const;
    void calcularDuracionTotal();

    // Operaciones
    void mostrarInfo() const;
    void mostrarCanciones() const;

    // Sobrecarga de operadores
    Album& operator=(const Album& otro);
    bool operator==(const Album& otro) const;

    // Calcular memoria
    size_t calcularMemoria() const;

private:
    void liberarMemoria();
    void copiarDatos(const Album& otro);
    void expandirCanciones();
};

#endif
