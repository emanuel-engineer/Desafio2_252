#include "cancion.h"
#include <iostream>

// Constructor por defecto
Cancion::Cancion() : id(0), duracion(0), reproducciones(0) {
    productores = new Credito[2];
    capacidadProductores = 2;
    numProductores = 0;

    musicos = new Credito[2];
    capacidadMusicos = 2;
    numMusicos = 0;

    compositores = new Credito[2];
    capacidadCompositores = 2;
    numCompositores = 0;
}

// Constructor parametrizado
Cancion::Cancion(int id, const std::string& nom, int dur, const std::string& ruta)
    : id(id), nombre(nom), duracion(dur), rutaBase(ruta), reproducciones(0) {
    productores = new Credito[2];
    capacidadProductores = 2;
    numProductores = 0;

    musicos = new Credito[2];
    capacidadMusicos = 2;
    numMusicos = 0;

    compositores = new Credito[2];
    capacidadCompositores = 2;
    numCompositores = 0;
}

// Constructor de copia
Cancion::Cancion(const Cancion& otra)
    : id(otra.id), nombre(otra.nombre), duracion(otra.duracion),
    rutaBase(otra.rutaBase), reproducciones(otra.reproducciones) {

    productores = nullptr;
    musicos = nullptr;
    compositores = nullptr;
    copiarCreditos(otra);
}

// Destructor
Cancion::~Cancion() {
    liberarCreditos();
}

void Cancion::liberarCreditos() {
    delete[] productores;
    delete[] musicos;
    delete[] compositores;
}

void Cancion::copiarCreditos(const Cancion& otra) {
    // Copiar productores
    capacidadProductores = otra.capacidadProductores;
    numProductores = otra.numProductores;
    productores = new Credito[capacidadProductores];
    for(int i = 0; i < numProductores; i++) {
        productores[i] = otra.productores[i];
    }

    // Copiar musicos
    capacidadMusicos = otra.capacidadMusicos;
    numMusicos = otra.numMusicos;
    musicos = new Credito[capacidadMusicos];
    for(int i = 0; i < numMusicos; i++) {
        musicos[i] = otra.musicos[i];
    }

    // Copiar compositores
    capacidadCompositores = otra.capacidadCompositores;
    numCompositores = otra.numCompositores;
    compositores = new Credito[capacidadCompositores];
    for(int i = 0; i < numCompositores; i++) {
        compositores[i] = otra.compositores[i];
    }
}

// Getters
int Cancion::getId() const {
    return id;
}

std::string Cancion::getNombre() const {
    return nombre;
}

int Cancion::getDuracion() const {
    return duracion;
}

std::string Cancion::getRutaBase() const {
    return rutaBase;
}

std::string Cancion::getRutaAudio(int bitrate) const {
    return rutaBase + "_" + std::to_string(bitrate) + ".ogg";
}

int Cancion::getReproducciones() const {
    return reproducciones;
}

int Cancion::getIdArtista() const {
    return id / 10000; // Primeros 5 digitos
}

int Cancion::getIdAlbum() const {
    return (id / 100) % 100; // Digitos 6-7
}

int Cancion::getIdCancion() const {
    return id % 100; // Ultimos 2 digitos
}

// Setters
void Cancion::setNombre(const std::string& nom) {
    nombre = nom;
}

void Cancion::setDuracion(int dur) {
    duracion = dur;
}

void Cancion::setRutaBase(const std::string& ruta) {
    rutaBase = ruta;
}

// Expandir arrays
void Cancion::expandirProductores() {
    int nuevaCapacidad = capacidadProductores * 2;
    Credito* nuevo = new Credito[nuevaCapacidad];
    for(int i = 0; i < numProductores; i++) {
        nuevo[i] = productores[i];
    }
    delete[] productores;
    productores = nuevo;
    capacidadProductores = nuevaCapacidad;
}

void Cancion::expandirMusicos() {
    int nuevaCapacidad = capacidadMusicos * 2;
    Credito* nuevo = new Credito[nuevaCapacidad];
    for(int i = 0; i < numMusicos; i++) {
        nuevo[i] = musicos[i];
    }
    delete[] musicos;
    musicos = nuevo;
    capacidadMusicos = nuevaCapacidad;
}

void Cancion::expandirCompositores() {
    int nuevaCapacidad = capacidadCompositores * 2;
    Credito* nuevo = new Credito[nuevaCapacidad];
    for(int i = 0; i < numCompositores; i++) {
        nuevo[i] = compositores[i];
    }
    delete[] compositores;
    compositores = nuevo;
    capacidadCompositores = nuevaCapacidad;
}

// Agregar creditos
void Cancion::agregarProductor(const Credito& prod) {
    if(numProductores >= capacidadProductores) {
        expandirProductores();
    }
    productores[numProductores++] = prod;
}

void Cancion::agregarMusico(const Credito& mus) {
    if(numMusicos >= capacidadMusicos) {
        expandirMusicos();
    }
    musicos[numMusicos++] = mus;
}

void Cancion::agregarCompositor(const Credito& comp) {
    if(numCompositores >= capacidadCompositores) {
        expandirCompositores();
    }
    compositores[numCompositores++] = comp;
}

// Operaciones
void Cancion::incrementarReproducciones() {
    reproducciones++;
}

void Cancion::mostrarInfo() const {
    std::cout << "\n┌─────────────────────────────────────────────┐\n";
    std::cout << "│ CANCION: " << nombre << "\n";
    std::cout << "│ ID: " << id << "\n";
    std::cout << "│ Duracion: " << duracion/60 << ":" << duracion%60 << "\n";
    std::cout << "│ Reproducciones: " << reproducciones << "\n";
    std::cout << "└─────────────────────────────────────────────┘\n";
}

void Cancion::mostrarCreditos() const {
    std::cout << "\nCREDITOS:\n";

    if(numProductores > 0) {
        std::cout << "  Productores:\n";
        for(int i = 0; i < numProductores; i++) {
            std::cout << "    - ";
            productores[i].mostrarInfo();
            std::cout << "\n";
        }
    }

    if(numMusicos > 0) {
        std::cout << "  Musicos:\n";
        for(int i = 0; i < numMusicos; i++) {
            std::cout << "    - ";
            musicos[i].mostrarInfo();
            std::cout << "\n";
        }
    }

    if(numCompositores > 0) {
        std::cout << "  Compositores:\n";
        for(int i = 0; i < numCompositores; i++) {
            std::cout << "    - ";
            compositores[i].mostrarInfo();
            std::cout << "\n";
        }
    }
}

// Sobrecarga operador =
Cancion& Cancion::operator=(const Cancion& otra) {
    if(this != &otra) {
        id = otra.id;
        nombre = otra.nombre;
        duracion = otra.duracion;
        rutaBase = otra.rutaBase;
        reproducciones = otra.reproducciones;

        liberarCreditos();
        copiarCreditos(otra);
    }
    return *this;
}

// Sobrecarga operador ==
bool Cancion::operator==(const Cancion& otra) const {
    return id == otra.id;
}

// Calcular memoria
size_t Cancion::calcularMemoria() const {
    size_t total = sizeof(Cancion);
    total += nombre.capacity();
    total += rutaBase.capacity();
    total += capacidadProductores * sizeof(Credito);
    total += capacidadMusicos * sizeof(Credito);
    total += capacidadCompositores * sizeof(Credito);

    for(int i = 0; i < numProductores; i++) {
        total += productores[i].calcularMemoria() - sizeof(Credito);
    }
    for(int i = 0; i < numMusicos; i++) {
        total += musicos[i].calcularMemoria() - sizeof(Credito);
    }
    for(int i = 0; i < numCompositores; i++) {
        total += compositores[i].calcularMemoria() - sizeof(Credito);
    }

    return total;
}
