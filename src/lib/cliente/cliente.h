#include <string>
#include "../libro/libro.h"

using std::string;

struct Cliente {
    Cliente();
    string usuario;
    string contrasena;
    string primer_nombre;
    string apellido;
    char genero;
    Libro libro;
};

void ObtenerClientes(Cliente clientes[], string csv);