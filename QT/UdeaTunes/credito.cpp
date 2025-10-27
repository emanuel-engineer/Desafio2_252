#include "credito.h"
#include <iostream>
#include <cstring>
using namespace std;

// Constructor por defecto
Credito::Credito() : tipo(COMPOSITOR) {
    nombres = "";
    apellidos = "";
    for(int i = 0; i < 11; i++) {
        codigoAfiliacion[i] = '\0';
    }
}

// Constructor parametrizado
Credito::Credito(const string& nom, const string& ape,
                 const string& codigo, TipoCredito t)
    : nombres(nom), apellidos(ape), tipo(t) {
    // Copiar codigo de afiliacion (max 10 caracteres)
    size_t len = codigo.length() > 10 ? 10 : codigo.length();
    for(size_t i = 0; i < len; i++) {
        codigoAfiliacion[i] = codigo[i];
    }
    codigoAfiliacion[len] = '\0';
}

// Constructor de copia
Credito::Credito(const Credito& otro)
    : nombres(otro.nombres), apellidos(otro.apellidos), tipo(otro.tipo) {
    for(int i = 0; i < 11; i++) {
        codigoAfiliacion[i] = otro.codigoAfiliacion[i];
    }
}

// Destructor
Credito::~Credito() {
    // No hay memoria dinamica que liberar
}

// Getters
string Credito::getNombres() const {
    return nombres;
}

string Credito::getApellidos() const {
    return apellidos;
}

string Credito::getCodigoAfiliacion() const {
    return string(codigoAfiliacion);
}

TipoCredito Credito::getTipo() const {
    return tipo;
}

string Credito::getTipoStr() const {
    switch(tipo) {
    case PRODUCTOR: return "Productor";
    case MUSICO: return "Musico";
    case COMPOSITOR: return "Compositor";
    default: return "Desconocido";
    }
}

// Setters
void Credito::setNombres(const string& nom) {
    nombres = nom;
}

void Credito::setApellidos(const string& ape) {
    apellidos = ape;
}

void Credito::setCodigoAfiliacion(const string& codigo) {
    size_t len = codigo.length() > 10 ? 10 : codigo.length();
    for(size_t i = 0; i < len; i++) {
        codigoAfiliacion[i] = codigo[i];
    }
    codigoAfiliacion[len] = '\0';
}

void Credito::setTipo(TipoCredito t) {
    tipo = t;
}

// Sobrecarga operador =
Credito& Credito::operator=(const Credito& otro) {
    if(this != &otro) {
        nombres = otro.nombres;
        apellidos = otro.apellidos;
        tipo = otro.tipo;
        for(int i = 0; i < 11; i++) {
            codigoAfiliacion[i] = otro.codigoAfiliacion[i];
        }
    }
    return *this;
}

// Sobrecarga operador ==
bool Credito::operator==(const Credito& otro) const {
    return (strcmp(codigoAfiliacion, otro.codigoAfiliacion) == 0);
}

// Mostrar informacion
void Credito::mostrarInfo() const {
    cout << getTipoStr() << ": " << nombres << " " << apellidos
              << " [" << codigoAfiliacion << "]";
}

// Calcular memoria
size_t Credito::calcularMemoria() const {
    return sizeof(Credito) + nombres.capacity() + apellidos.capacity();
}
