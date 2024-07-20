#pragma once
#include <string>
#include "../libro/libro.h"

using std::string;

const int NUM_CLIENTES = 100;

struct Cliente {
    Cliente();
    string usuario;
    string contrasena;
    string primer_nombre;
    string apellido;
    char genero;
    Libro libro;
};

void ObtenerClientes(Cliente clientes[], Libro libros[], string csv);
Cliente BuscarCliente(Cliente clientes[], string usuario);