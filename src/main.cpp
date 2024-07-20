#include <iostream>
#include "./lib/libro/libro.h"

using std::cout, std::endl;

int main() {
    cout << "Hola mundo" << endl;
    Libro libros[100] = {};

    ObtenerLibros(libros, "./data/libros.csv");
}