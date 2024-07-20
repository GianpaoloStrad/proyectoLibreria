#pragma once
#include <string>
#include "../libro/libro.h"
#include "../definiciones.h"

using std::string;

const int NUM_EMPLEADOS = 10;

struct Empleado {
    Empleado();
    string usuario;
    string contrasena;
    string primer_nombre;
    string apellido;
    char genero;
};

void ObtenerEmpleados(Empleado empleados[]);
Empleado BuscarEmpleado(Empleado clientes[], string usuario);
void CambiarCantLibro(Libro libros[], string nombre, int cantidad);