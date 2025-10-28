#include "album.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Album::Album() : id(0), duracionTotal(0), puntuacion(0.0f), numGeneros(0) {
    generos = new string[4]; // Max 4 generos
    canciones = new Cancion*[5];
    capacidadCanciones = 5;
    numCanciones = 0;
}

// Constructor parametrizado
Album::Album(int id, const string& nom, const string& fecha,
             const string& sello, const string& portada)
    : id(id), nombre(nom), fechaLanzamiento(fecha), duracionTotal(0),
    selloDisquero(sello), rutaPortada(portada), puntuacion(0.0f), numGeneros(0) {
    generos = new string[4];
    canciones = new Cancion*[5];
    capacidadCanciones = 5;
    numCanciones = 0;
}

// Constructor de copia
Album::Album(const Album& otro) {
    generos = nullptr;
    canciones = nullptr;
    copiarDatos(otro);
}

// Destructor
Album::~Album() {
    liberarMemoria();
}

void Album::liberarMemoria() {
    delete[] generos;

    for(int i = 0; i < numCanciones; i++) {
        delete canciones[i];
    }
    delete[] canciones;
}

void Album::copiarDatos(const Album& otro) {
    id = otro.id;
    nombre = otro.nombre;
    fechaLanzamiento = otro.fechaLanzamiento;
    duracionTotal = otro.duracionTotal;
    selloDisquero = otro.selloDisquero;
    rutaPortada = otro.rutaPortada;
    puntuacion = otro.puntuacion;

    // Copiar generos
    numGeneros = otro.numGeneros;
    generos = new string[4];
    for(int i = 0; i < numGeneros; i++) {
        generos[i] = otro.generos[i];
    }

    // Copiar canciones
    capacidadCanciones = otro.capacidadCanciones;
    numCanciones = otro.numCanciones;
    canciones = new Cancion*[capacidadCanciones];
    for(int i = 0; i < numCanciones; i++) {
        canciones[i] = new Cancion(*otro.canciones[i]);
    }
}

// Getters
int Album::getId() const {
    return id;
}

string Album::getNombre() const {
    return nombre;
}

string Album::getFechaLanzamiento() const {
    return fechaLanzamiento;
}

int Album::getDuracionTotal() const {
    return duracionTotal;
}

string Album::getSelloDisquero() const {
    return selloDisquero;
}

string Album::getRutaPortada() const {
    return rutaPortada;
}

float Album::getPuntuacion() const {
    return puntuacion;
}

int Album::getNumCanciones() const {
    return numCanciones;
}

Cancion* Album::getCancion(int index) const {
    if(index >= 0 && index < numCanciones) {
        return canciones[index];
    }
    return nullptr;
}

// Setters
void Album::setNombre(const string& nom) {
    nombre = nom;
}

void Album::setPuntuacion(float punt) {
    if(punt >= 1.0f && punt <= 10.0f) {
        puntuacion = punt;
    }
}

// Generos
void Album::agregarGenero(const string& genero) {
    if(numGeneros < 4) {
        generos[numGeneros++] = genero;
    }
}

string Album::getGenerosStr() const {
    string resultado = "";
    for(int i = 0; i < numGeneros; i++) {
        resultado += generos[i];
        if(i < numGeneros - 1) {
            resultado += ", ";
        }
    }
    return resultado;
}

// Expandir array de canciones
void Album::expandirCanciones() {
    int nuevaCapacidad = capacidadCanciones * 2;
    Cancion** nuevo = new Cancion*[nuevaCapacidad];
    for(int i = 0; i < numCanciones; i++) {
        nuevo[i] = canciones[i];
    }
    delete[] canciones;
    canciones = nuevo;
    capacidadCanciones = nuevaCapacidad;
}

// Agregar cancion
void Album::agregarCancion(Cancion* cancion) {
    if(numCanciones >= capacidadCanciones) {
        expandirCanciones();
    }
    canciones[numCanciones++] = cancion;
}

// Buscar cancion por ID
Cancion* Album::buscarCancionPorId(int idCancion) const {
    for(int i = 0; i < numCanciones; i++) {
        if(canciones[i]->getId() == idCancion) {
            return canciones[i];
        }
    }
    return nullptr;
}

// Calcular duracion total
void Album::calcularDuracionTotal() {
    duracionTotal = 0;
    for(int i = 0; i < numCanciones; i++) {
        duracionTotal += canciones[i]->getDuracion();
    }
}

// Mostrar informacion
void Album::mostrarInfo() const {
    cout << "\n╔═════════════════════════════════════════════╗\n";
    cout << "║ ALBUM: " << nombre << "\n";
    cout << "║ ID: " << id << "\n";
    cout << "║ Fecha: " << fechaLanzamiento << "\n";
    cout << "║ Sello: " << selloDisquero << "\n";
    cout << "║ Generos: " << getGenerosStr() << "\n";
    cout << "║ Duracion: " << duracionTotal/60 << " min\n";
    cout << "║ Puntuacion: " << puntuacion << "/10\n";
    cout << "║ Canciones: " << numCanciones << "\n";
    cout << "╚═════════════════════════════════════════════╝\n";
}

void Album::mostrarCanciones() const {
    cout << "\nCANCIONES DEL ALBUM:\n";
    for(int i = 0; i < numCanciones; i++) {
        cout << (i+1) << ". " << canciones[i]->getNombre()
        << " (" << canciones[i]->getDuracion()/60 << ":"
        << canciones[i]->getDuracion()%60 << ")\n";
    }
}

// Sobrecarga operador =
Album& Album::operator=(const Album& otro) {
    if(this != &otro) {
        liberarMemoria();
        copiarDatos(otro);
    }
    return *this;
}

// Sobrecarga operador ==
bool Album::operator==(const Album& otro) const {
    return id == otro.id;
}

// Calcular memoria
size_t Album::calcularMemoria() const {
    size_t total = sizeof(Album);
    total += nombre.capacity();
    total += fechaLanzamiento.capacity();
    total += selloDisquero.capacity();
    total += rutaPortada.capacity();
    total += 4 * sizeof(string); // generos

    for(int i = 0; i < numGeneros; i++) {
        total += generos[i].capacity();
    }

    total += capacidadCanciones * sizeof(Cancion*);
    for(int i = 0; i < numCanciones; i++) {
        total += canciones[i]->calcularMemoria();
    }

    return total;
}
