#include <string>

using std::string;

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