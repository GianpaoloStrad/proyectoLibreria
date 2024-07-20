#pragma once
#include <string>

using std::string;

const int NUM_LIBROS = 100;

struct Libro {
    Libro();
    int id;
    string nombre;
    string editorial;
    int edicion;
    int cantidad;
    int precio;
};

void ObtenerLibros(Libro libros[], string csv);
Libro BuscarLibro(Libro libros[], string nombre);