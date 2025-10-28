#ifndef ANUNCIO_H
#define ANUNCIO_H
#include <string>
using namespace std;

// Categoria de anuncio
enum CategoriaAnuncio {
    C = 1,    // Prioridad simple
    B = 2,    // Doble prioridad
    AAA = 3   // Triple prioridad
};

class Anuncio {
private:
    int id;
    char mensaje[501]; // Max 500 caracteres + '\0'
    CategoriaAnuncio categoria;
    int prioridad; // 1, 2 o 3

public:
    // Constructores
    Anuncio();
    Anuncio(int id, const string& msg, CategoriaAnuncio cat);
    Anuncio(const Anuncio& otro); // Constructor de copia

    // Destructor
    ~Anuncio();

    // Getters
    int getId() const;
    string getMensaje() const;
    CategoriaAnuncio getCategoria() const;
    int getPrioridad() const;
    string getCategoriaStr() const;

    // Setters
    void setMensaje(const string& msg);
    void setCategoria(CategoriaAnuncio cat);

    // Operaciones
    void mostrar() const;

    // Sobrecarga de operadores
    Anuncio& operator=(const Anuncio& otro);
    bool operator==(const Anuncio& otro) const;

    // Calcular memoria
    size_t calcularMemoria() const;
};

#endif
