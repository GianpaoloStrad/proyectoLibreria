#include <iostream>
#include "./lib/libro/libro.h"
#include "./lib/cliente/cliente.h"

using std::cout, std::endl;

int main() {
    cout << "Hola mundo" << endl;
    Libro libros[NUM_LIBROS] = {};
    Cliente clientes[NUM_CLIENTES] = {};

    ObtenerLibros(libros, "./data/libros.csv");
    ObtenerClientes(clientes, libros, "./data/clientes.csv");
}