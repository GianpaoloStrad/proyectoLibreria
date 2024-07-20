#pragma once
#include <string>

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

void ObtenerEmpleados(Empleado empleados[], string csv);