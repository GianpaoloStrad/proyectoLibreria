#include <iostream>
#include "./lib/libro/libro.h"
#include "./lib/cliente/cliente.h"
#include "./lib/empleado/empleado.h"
#include "./lib/admin/admin.h"

using std::cout, std::endl;

const char* LIBROS_CSV = "./data/libros.csv";
const char* CLIENTES_CSV = "./data/clientes.csv";
const char* EMPLEADOS_CSV = "./data/empleados.csv";
const char* ADMINS_CSV = "./data/admins.csv";

int main() {
    cout << "Iniciando..." << endl;

    Libro libros[NUM_LIBROS] = {};
    Cliente clientes[NUM_CLIENTES] = {};
    Empleado empleados[NUM_EMPLEADOS] = {};
    Admin admins[NUM_ADMINS] = {};

    ObtenerLibros(libros, LIBROS_CSV);
    ObtenerClientes(clientes, libros, CLIENTES_CSV);
    ObtenerEmpleados(empleados, EMPLEADOS_CSV);
    ObtenerAdmins(admins, ADMINS_CSV);

    cout << "Cerrando..." << endl;
}