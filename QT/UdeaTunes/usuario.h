#ifndef USUARIO_H
#define USUARIO_H
#include <string>


class Usuario
{
private:
    int userID;
    std::string username;
    std::string password;
    char tipoUsuario;
public:
    Usuario();
    bool login();
    bool logout();
};

#endif // USUARIO_H
