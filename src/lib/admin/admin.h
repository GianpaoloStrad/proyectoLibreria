#pragma once
#include <string>
#include "../definiciones.h"

using std::string;

const int NUM_ADMINS = 10;

struct Admin {
    Admin();
    string usuario;
    string contrasena;
    string primer_nombre;
    string apellido;
    char genero;
};

void ObtenerAdmins(Admin admins[]);
Admin BuscarAdmin(Admin clientes[], string usuario);