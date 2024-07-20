#pragma once
#include <string>
#include "../definiciones.h"

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

void ObtenerLibros(Libro libros[]);
Libro BuscarLibro(Libro libros[], string nombre);
Libro& BuscarLibroRef(Libro libros[], string nombre);
void ActualizarLibrosCSV(Libro libros[]);