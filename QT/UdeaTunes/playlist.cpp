#include "playlist.h"
#include <iostream>

// Constructor por defecto
Playlist::Playlist() : capacidadMax(10000), numCanciones(0) {
    idsCanciones = new int[capacidadMax];
}

// Constructor parametrizado
Playlist::Playlist(const string& nom, const string& prop)
    : nombre(nom), propietario(prop), capacidadMax(10000), numCanciones(0) {
    idsCanciones = new int[capacidadMax];
}

// Constructor de copia
Playlist::Playlist(const Playlist& otra)
    : nombre(otra.nombre), propietario(otra.propietario),
    capacidadMax(otra.capacidadMax), numCanciones(otra.numCanciones) {
    idsCanciones = new int[capacidadMax];
    for(int i = 0; i < numCanciones; i++) {
        idsCanciones[i] = otra.idsCanciones[i];
    }
}

// Destructor
Playlist::~Playlist() {
    delete[] idsCanciones;
}

// Getters
string Playlist::getNombre() const {
    return nombre;
}

string Playlist::getPropietario() const {
    return propietario;
}

int Playlist::getNumCanciones() const {
    return numCanciones;
}

int Playlist::getIdCancion(int index) const {
    if(index >= 0 && index < numCanciones) {
        return idsCanciones[index];
    }
    return -1;
}

// Setters
void Playlist::setNombre(const string& nom) {
    nombre = nom;
}

// Agregar cancion (sin duplicados)
bool Playlist::agregarCancion(int idCancion) {
    // Verificar si ya existe
    if(contieneCancion(idCancion)) {
        return false;
    }

    // Verificar capacidad
    if(numCanciones >= capacidadMax) {
        cout << "Playlist llena (max 10000 canciones)\n";
        return false;
    }

    idsCanciones[numCanciones++] = idCancion;
    return true;
}

// Eliminar cancion
bool Playlist::eliminarCancion(int idCancion) {
    for(int i = 0; i < numCanciones; i++) {
        if(idsCanciones[i] == idCancion) {
            // Mover elementos hacia la izquierda
            for(int j = i; j < numCanciones - 1; j++) {
                idsCanciones[j] = idsCanciones[j + 1];
            }
            numCanciones--;
            return true;
        }
    }
    return false;
}

// Verificar si contiene cancion
bool Playlist::contieneCancion(int idCancion) const {
    for(int i = 0; i < numCanciones; i++) {
        if(idsCanciones[i] == idCancion) {
            return true;
        }
    }
    return false;
}

// Limpiar playlist
void Playlist::limpiar() {
    numCanciones = 0;
}

// Mostrar informacion
void Playlist::mostrarInfo() const {
    cout << "\n┌─────────────────────────────────────────────┐\n";
    cout << "│ PLAYLIST: " << nombre << "\n";
    cout << "│ Propietario: " << propietario << "\n";
    cout << "│ Canciones: " << numCanciones << "/" << capacidadMax << "\n";
    cout << "└─────────────────────────────────────────────┘\n";
}

// Fusionar con otra playlist
void Playlist::fusionarCon(const Playlist& otra) {
    for(int i = 0; i < otra.numCanciones; i++) {
        agregarCancion(otra.idsCanciones[i]);
    }
}

// Sobrecarga operador =
Playlist& Playlist::operator=(const Playlist& otra) {
    if(this != &otra) {
        delete[] idsCanciones;

        nombre = otra.nombre;
        propietario = otra.propietario;
        capacidadMax = otra.capacidadMax;
        numCanciones = otra.numCanciones;

        idsCanciones = new int[capacidadMax];
        for(int i = 0; i < numCanciones; i++) {
            idsCanciones[i] = otra.idsCanciones[i];
        }
    }
    return *this;
}

// Sobrecarga operador ==
bool Playlist::operator==(const Playlist& otra) const {
    return (nombre == otra.nombre && propietario == otra.propietario);
}

// Sobrecarga operador + (fusionar)
Playlist Playlist::operator+(const Playlist& otra) const {
    Playlist resultado(*this);
    resultado.fusionarCon(otra);
    return resultado;
}

// Calcular memoria
size_t Playlist::calcularMemoria() const {
    size_t total = sizeof(Playlist);
    total += nombre.capacity();
    total += propietario.capacity();
    total += capacidadMax * sizeof(int);
    return total;
}
