#include "anuncio.h"
#include <iostream>
#include <cstring>
using namespace std;

// Constructor por defecto
Anuncio::Anuncio() : id(0), categoria(C), prioridad(1) {
    mensaje[0] = '\0';
}

// Constructor parametrizado
Anuncio::Anuncio(int id, const string& msg, CategoriaAnuncio cat)
    : id(id), categoria(cat) {

    // Copiar mensaje (max 500 caracteres)
    size_t len = msg.length() > 500 ? 500 : msg.length();
    for(size_t i = 0; i < len; i++) {
        mensaje[i] = msg[i];
    }
    mensaje[len] = '\0';

    // Asignar prioridad segun categoria
    switch(cat) {
    case C: prioridad = 1; break;
    case B: prioridad = 2; break;
    case AAA: prioridad = 3; break;
    }
}

// Constructor de copia
Anuncio::Anuncio(const Anuncio& otro)
    : id(otro.id), categoria(otro.categoria), prioridad(otro.prioridad) {
    for(int i = 0; i < 501; i++) {
        mensaje[i] = otro.mensaje[i];
    }
}

// Destructor
Anuncio::~Anuncio() {
    // No hay memoria dinamica
}

// Getters
int Anuncio::getId() const {
    return id;
}

string Anuncio::getMensaje() const {
    return string(mensaje);
}

CategoriaAnuncio Anuncio::getCategoria() const {
    return categoria;
}

int Anuncio::getPrioridad() const {
    return prioridad;
}

string Anuncio::getCategoriaStr() const {
    switch(categoria) {
    case C: return "C";
    case B: return "B";
    case AAA: return "AAA";
    default: return "C";
    }
}

// Setters
void Anuncio::setMensaje(const string& msg) {
    size_t len = msg.length() > 500 ? 500 : msg.length();
    for(size_t i = 0; i < len; i++) {
        mensaje[i] = msg[i];
    }
    mensaje[len] = '\0';
}

void Anuncio::setCategoria(CategoriaAnuncio cat) {
    categoria = cat;
    switch(cat) {
    case C: prioridad = 1; break;
    case B: prioridad = 2; break;
    case AAA: prioridad = 3; break;
    }
}

// Mostrar anuncio
void Anuncio::mostrar() const {
    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║                     PUBLICIDAD                        ║\n";
    cout << "╠═══════════════════════════════════════════════════════╣\n";
    cout << "║ " << mensaje << "\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

// Sobrecarga operador =
Anuncio& Anuncio::operator=(const Anuncio& otro) {
    if(this != &otro) {
        id = otro.id;
        categoria = otro.categoria;
        prioridad = otro.prioridad;
        for(int i = 0; i < 501; i++) {
            mensaje[i] = otro.mensaje[i];
        }
    }
    return *this;
}

// Sobrecarga operador ==
bool Anuncio::operator==(const Anuncio& otro) const {
    return id == otro.id;
}

// Calcular memoria
size_t Anuncio::calcularMemoria() const {
    return sizeof(Anuncio);
}
