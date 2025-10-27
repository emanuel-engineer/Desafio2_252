#ifndef CREDITO_H
#define CREDITO_H
#include <string>

// Enumeracion para tipo de credito
enum TipoCredito {
    PRODUCTOR,
    MUSICO,
    COMPOSITOR
};

class Credito {
private:
    std::string nombres;
    std::string apellidos;
    char codigoAfiliacion[11]; // 10 caracteres + '\0'
    TipoCredito tipo;

public:
    // Constructores
    Credito();
    Credito(const std::string& nom, const std::string& ape,
            const std::string& codigo, TipoCredito t);
    Credito(const Credito& otro); // Constructor de copia

    // Destructor
    ~Credito();

    // Getters
    std::string getNombres() const;
    std::string getApellidos() const;
    std::string getCodigoAfiliacion() const;
    TipoCredito getTipo() const;
    std::string getTipoStr() const;

    // Setters
    void setNombres(const std::string& nom);
    void setApellidos(const std::string& ape);
    void setCodigoAfiliacion(const std::string& codigo);
    void setTipo(TipoCredito t);

    // Sobrecarga de operadores
    Credito& operator=(const Credito& otro);
    bool operator==(const Credito& otro) const;

    // Metodos auxiliares
    void mostrarInfo() const;
    size_t calcularMemoria() const;
};

#endif // CREDITO_H
