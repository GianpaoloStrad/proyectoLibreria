#pragma once
#include <string>
#include "../libro/libro.h"
#include "../definiciones.h"
#include "../empleado/empleado.h"

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
    bool suspendido;
};

void ObtenerClientes(Cliente clientes[], Libro libros[]);
Cliente BuscarCliente(Cliente clientes[], string usuario);
void RetirarLibro(Cliente clientes[], Libro libros[], Cliente &cliente, Libro &libro);
void ActualizarClientesCSV(Cliente clientes[]);