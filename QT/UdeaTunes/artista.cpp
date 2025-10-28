#include "artista.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Artista::Artista() : id(0), edad(0), seguidores(0), posicionTendencias(0) {
    albumes = new Album*[3];
    capacidadAlbumes = 3;
    numAlbumes = 0;
}

// Constructor parametrizado
Artista::Artista(int id, const string& nom, int edad, const string& pais)
    : id(id), nombre(nom), edad(edad), paisOrigen(pais),
    seguidores(0), posicionTendencias(0) {
    albumes = new Album*[3];
    capacidadAlbumes = 3;
    numAlbumes = 0;
}

// Constructor de copia
Artista::Artista(const Artista& otro) {
    albumes = nullptr;
    copiarDatos(otro);
}

// Destructor
Artista::~Artista() {
    liberarMemoria();
}

void Artista::liberarMemoria() {
    for(int i = 0; i < numAlbumes; i++) {
        delete albumes[i];
    }
    delete[] albumes;
}

void Artista::copiarDatos(const Artista& otro) {
    id = otro.id;
    nombre = otro.nombre;
    edad = otro.edad;
    paisOrigen = otro.paisOrigen;
    seguidores = otro.seguidores;
    posicionTendencias = otro.posicionTendencias;

    capacidadAlbumes = otro.capacidadAlbumes;
    numAlbumes = otro.numAlbumes;
    albumes = new Album*[capacidadAlbumes];
    for(int i = 0; i < numAlbumes; i++) {
        albumes[i] = new Album(*otro.albumes[i]);
    }
}

// Getters
int Artista::getId() const {
    return id;
}

string Artista::getNombre() const {
    return nombre;
}

int Artista::getEdad() const {
    return edad;
}

string Artista::getPaisOrigen() const {
    return paisOrigen;
}

int Artista::getSeguidores() const {
    return seguidores;
}

int Artista::getPosicionTendencias() const {
    return posicionTendencias;
}

int Artista::getNumAlbumes() const {
    return numAlbumes;
}

Album* Artista::getAlbum(int index) const {
    if(index >= 0 && index < numAlbumes) {
        return albumes[index];
    }
    return nullptr;
}

// Setters
void Artista::setNombre(const string& nom) {
    nombre = nom;
}

void Artista::setEdad(int e) {
    edad = e;
}

void Artista::setSeguidores(int seg) {
    seguidores = seg;
}

void Artista::setPosicionTendencias(int pos) {
    posicionTendencias = pos;
}

// Expandir albumes
void Artista::expandirAlbumes() {
    int nuevaCapacidad = capacidadAlbumes * 2;
    Album** nuevo = new Album*[nuevaCapacidad];
    for(int i = 0; i < numAlbumes; i++) {
        nuevo[i] = albumes[i];
    }
    delete[] albumes;
    albumes = nuevo;
    capacidadAlbumes = nuevaCapacidad;
}

// Agregar album
void Artista::agregarAlbum(Album* album) {
    if(numAlbumes >= capacidadAlbumes) {
        expandirAlbumes();
    }
    albumes[numAlbumes++] = album;
}

// Buscar album por ID
Album* Artista::buscarAlbumPorId(int idAlbum) const {
    for(int i = 0; i < numAlbumes; i++) {
        if(albumes[i]->getId() == idAlbum) {
            return albumes[i];
        }
    }
    return nullptr;
}

// Buscar cancion por ID
Cancion* Artista::buscarCancionPorId(int idCancion) const {
    for(int i = 0; i < numAlbumes; i++) {
        Cancion* cancion = albumes[i]->buscarCancionPorId(idCancion);
        if(cancion != nullptr) {
            return cancion;
        }
    }
    return nullptr;
}

// Mostrar informacion
void Artista::mostrarInfo() const {
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║ ARTISTA: " << nombre << "\n";
    cout << "║ ID: " << id << "\n";
    cout << "║ Edad: " << edad << " años\n";
    cout << "║ Pais: " << paisOrigen << "\n";
    cout << "║ Seguidores: " << seguidores << "\n";
    cout << "║ Posicion en tendencias: #" << posicionTendencias << "\n";
    cout << "║ Albumes: " << numAlbumes << "\n";
    cout << "╚═══════════════════════════════════════════════╝\n";
}

void Artista::mostrarCatalogo() const {
    cout << "\nCATALOGO DE " << nombre << ":\n";
    for(int i = 0; i < numAlbumes; i++) {
        cout << "\n" << (i+1) << ". " << albumes[i]->getNombre()
        << " [" << albumes[i]->getFechaLanzamiento() << "]";
        cout << " - " << albumes[i]->getNumCanciones() << " canciones";
    }
    cout << "\n";
}

int Artista::getTotalCanciones() const {
    int total = 0;
    for(int i = 0; i < numAlbumes; i++) {
        total += albumes[i]->getNumCanciones();
    }
    return total;
}

// Sobrecarga operador =
Artista& Artista::operator=(const Artista& otro) {
    if(this != &otro) {
        liberarMemoria();
        copiarDatos(otro);
    }
    return *this;
}

// Sobrecarga operador ==
bool Artista::operator==(const Artista& otro) const {
    return id == otro.id;
}

// Calcular memoria
size_t Artista::calcularMemoria() const {
    size_t total = sizeof(Artista);
    total += nombre.capacity();
    total += paisOrigen.capacity();
    total += capacidadAlbumes * sizeof(Album*);

    for(int i = 0; i < numAlbumes; i++) {
        total += albumes[i]->calcularMemoria();
    }

    return total;
}
