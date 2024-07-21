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
    bool suspendido;
};

void ObtenerEmpleados(Empleado empleados[]);
Empleado BuscarEmpleado(Empleado empleados[], string usuario);
void CambiarCantLibro(Libro libros[], Libro libro, int cantidad);
void EliminarLibro(Libro libros[], Libro libro);
void ModificarLibro(Libro libros[], Libro &libro);
void AnadirLibro(Libro libros[]);
void ActualizarEmpleadosCSV(Empleado clientes[]);