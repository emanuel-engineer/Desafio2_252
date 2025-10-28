#include "usuario.h"
#include <iostream>

// Constructor por defecto
Usuario::Usuario() : membresia(ESTANDAR), posicionActual(-1) {
    listaFavoritos = nullptr;
    historialIds = new int[100];
    capacidadHistorial = 100;
    numHistorial = 0;
}

// Constructor parametrizado
Usuario::Usuario(const string& nick, const string& pass,
                 TipoMembresia memb, const string& city,
                 const string& country, const string& fecha)
    : nickname(nick), password(pass), membresia(memb), ciudad(city),
    pais(country), fechaInscripcion(fecha), posicionActual(-1) {

    if(membresia == PREMIUM) {
        listaFavoritos = new Playlist("Favoritos", nickname);
    } else {
        listaFavoritos = nullptr;
    }

    historialIds = new int[100];
    capacidadHistorial = 100;
    numHistorial = 0;
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro) {
    listaFavoritos = nullptr;
    historialIds = nullptr;
    copiarDatos(otro);
}

// Destructor
Usuario::~Usuario() {
    liberarMemoria();
}

void Usuario::liberarMemoria() {
    delete listaFavoritos;
    delete[] historialIds;
}

void Usuario::copiarDatos(const Usuario& otro) {
    nickname = otro.nickname;
    password = otro.password;
    membresia = otro.membresia;
    ciudad = otro.ciudad;
    pais = otro.pais;
    fechaInscripcion = otro.fechaInscripcion;
    posicionActual = otro.posicionActual;

    if(otro.listaFavoritos != nullptr) {
        listaFavoritos = new Playlist(*otro.listaFavoritos);
    } else {
        listaFavoritos = nullptr;
    }

    capacidadHistorial = otro.capacidadHistorial;
    numHistorial = otro.numHistorial;
    historialIds = new int[capacidadHistorial];
    for(int i = 0; i < numHistorial; i++) {
        historialIds[i] = otro.historialIds[i];
    }
}

// Getters
string Usuario::getNickname() const {
    return nickname;
}

string Usuario::getPassword() const {
    return password;
}

TipoMembresia Usuario::getMembresia() const {
    return membresia;
}

string Usuario::getMembresiaStr() const {
    return (membresia == PREMIUM) ? "Premium" : "Estandar";
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

Playlist* Usuario::getListaFavoritos() {
    return listaFavoritos;
}

int Usuario::getBitrate() const {
    return (membresia == PREMIUM) ? 320 : 128;
}

// Setters
void Usuario::setMembresia(TipoMembresia memb) {
    if(membresia != memb) {
        membresia = memb;

        if(memb == PREMIUM && listaFavoritos == nullptr) {
            listaFavoritos = new Playlist("Favoritos", nickname);
        } else if(memb == ESTANDAR && listaFavoritos != nullptr) {
            delete listaFavoritos;
            listaFavoritos = nullptr;
        }
    }
}

void Usuario::setCiudad(const string& city) {
    ciudad = city;
}

// Operaciones con favoritos
bool Usuario::agregarFavorito(int idCancion) {
    if(!esPremium() || listaFavoritos == nullptr) {
        return false;
    }
    return listaFavoritos->agregarCancion(idCancion);
}

bool Usuario::eliminarFavorito(int idCancion) {
    if(!esPremium() || listaFavoritos == nullptr) {
        return false;
    }
    return listaFavoritos->eliminarCancion(idCancion);
}

void Usuario::seguirListaFavoritos(const Playlist& otra) {
    if(esPremium() && listaFavoritos != nullptr) {
        listaFavoritos->fusionarCon(otra);
    }
}

// Expandir historial
void Usuario::expandirHistorial() {
    int nuevaCapacidad = capacidadHistorial * 2;
    int* nuevo = new int[nuevaCapacidad];
    for(int i = 0; i < numHistorial; i++) {
        nuevo[i] = historialIds[i];
    }
    delete[] historialIds;
    historialIds = nuevo;
    capacidadHistorial = nuevaCapacidad;
}

// Agregar al historial
void Usuario::agregarAlHistorial(int idCancion) {
    if(numHistorial >= capacidadHistorial) {
        expandirHistorial();
    }
    historialIds[numHistorial++] = idCancion;
    posicionActual = numHistorial - 1;
}

// Obtener cancion previa
int Usuario::obtenerCancionPrevia(int pasos) {
    if(posicionActual < 0 || numHistorial == 0) {
        return -1;
    }

    int nuevaPosicion = posicionActual - pasos;
    if(nuevaPosicion < 0) {
        return -1;
    }

    posicionActual = nuevaPosicion;
    return historialIds[posicionActual];
}

void Usuario::limpiarHistorial() {
    numHistorial = 0;
    posicionActual = -1;
}

// Verificacion
bool Usuario::verificarPassword(const string& pass) const {
    return password == pass;
}

bool Usuario::esPremium() const {
    return membresia == PREMIUM;
}

// Mostrar informacion
void Usuario::mostrarInfo() const {
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║ USUARIO: " << nickname << "\n";
    cout << "║ Membresia: " << getMembresiaStr() << "\n";
    cout << "║ Ubicacion: " << ciudad << ", " << pais << "\n";
    cout << "║ Fecha inscripcion: " << fechaInscripcion << "\n";
    cout << "║ Calidad audio: " << getBitrate() << " kbps\n";

    if(esPremium() && listaFavoritos != nullptr) {
        cout << "║ Favoritos: " << listaFavoritos->getNumCanciones() << " canciones\n";
    }

    cout << "╚═══════════════════════════════════════════════╝\n";
}

// Sobrecarga operador =
Usuario& Usuario::operator=(const Usuario& otro) {
    if(this != &otro) {
        liberarMemoria();
        copiarDatos(otro);
    }
    return *this;
}

// Sobrecarga operador ==
bool Usuario::operator==(const Usuario& otro) const {
    return nickname == otro.nickname;
}

// Calcular memoria
size_t Usuario::calcularMemoria() const {
    size_t total = sizeof(Usuario);
    total += nickname.capacity();
    total += password.capacity();
    total += ciudad.capacity();
    total += pais.capacity();
    total += fechaInscripcion.capacity();
    total += capacidadHistorial * sizeof(int);

    if(listaFavoritos != nullptr) {
        total += listaFavoritos->calcularMemoria();
    }

    return total;
}
