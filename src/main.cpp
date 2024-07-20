#include <iostream>
#include "./lib/libro/libro.h"
#include "./lib/cliente/cliente.h"
#include "./lib/empleado/empleado.h"
#include "./lib/admin/admin.h"
#include "./lib/definiciones.h"
#include "./lib/herramientas/conversiones.h"

using std::cout, std::endl, std::cin;

const char* LIBROS_CSV = "./data/libros.csv";
const char* CLIENTES_CSV = "./data/clientes.csv";
const char* EMPLEADOS_CSV = "./data/empleados.csv";
const char* ADMINS_CSV = "./data/admins.csv";

int main() {
    cout << "Iniciando..." << endl << endl;

    Libro libros[NUM_LIBROS] = {};
    Cliente clientes[NUM_CLIENTES] = {};
    Empleado empleados[NUM_EMPLEADOS] = {};
    Admin admins[NUM_ADMINS] = {};

    ObtenerLibros(libros, LIBROS_CSV);
    ObtenerClientes(clientes, libros, CLIENTES_CSV);
    ObtenerEmpleados(empleados, EMPLEADOS_CSV);
    ObtenerAdmins(admins, ADMINS_CSV);

    while (true) {
        Cliente cliente_activo = Cliente();
        Empleado empleado_activo = Empleado();
        Admin admin_activo = Admin();
        int tipo_usuario = -1;
        int accion = -1;

        system("cls");
        cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                << "----------- LOGIN -------------" << endl << endl
                << "(1) Cliente" << endl << endl
                << "(2) Empleado" << endl << endl
                << "(3) Admin" << endl << endl
                << "Ingrese una opcion: ";

        do {
            cin >> accion;
        } while (accion < 1 || accion > 3);

        tipo_usuario = accion;

        bool error = false;
        while (true) {
            string usuario = "";
            string contrasena = "";
            system("cls");
            cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                    << "----------- LOGIN -------------" << endl << endl
                    << "Usuario: ";

            cin >> usuario;
            cout << "Contrasena: ";
            cin >> contrasena;

            switch (tipo_usuario) {
                case U_CLT:
                    cliente_activo = BuscarCliente(clientes, usuario);
                    error = (cliente_activo.usuario != usuario || cliente_activo.contrasena != contrasena);
                    break;
                case U_EMP:
                    empleado_activo = BuscarEmpleado(empleados, usuario);
                    error = (empleado_activo.usuario != usuario || empleado_activo.contrasena != contrasena);
                    break;
                case U_ADM:
                    admin_activo = BuscarAdmin(admins, usuario);
                    error = (admin_activo.usuario != usuario || admin_activo.contrasena != contrasena);
                    break;
            }

            if (error) {
                char accion = ' ';
                cout    <<  "No se encontro ningun " << CodUsuarioAString(tipo_usuario) << " con las credenciales introducidas." << endl
                        <<  "Desea probar de nuevo? (y/n): ";
                do {
                    cin >> accion;
                } while (tolower(accion) != 'y' && tolower(accion) != 'n');

                if (accion == 'y') {
                    cliente_activo = Cliente();
                    empleado_activo = Empleado();
                    admin_activo = Admin();
                    error = false;
                } else {
                    break;
                }
            }

            break;
        }
        if (error) {
            error = false;
            continue;
        }

        system("cls");
        string temp = "";
        for(auto c : CodUsuarioAString(tipo_usuario))
            temp += toupper(c);

        cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                << "----------- " << temp << " -------------" << endl << endl
                << "Usuario: ";
        switch (tipo_usuario) {
            case U_CLT: cout << cliente_activo.usuario; break;
            case U_EMP: cout << empleado_activo.usuario; break;
            case U_ADM: cout << admin_activo.usuario; break;
        }
        cout    << endl << "Nombre: ";
        switch (tipo_usuario) {
            case U_CLT: cout << cliente_activo.primer_nombre << ' ' << cliente_activo.apellido; break;
            case U_EMP: cout << empleado_activo.primer_nombre << ' ' << empleado_activo.apellido; break;
            case U_ADM: cout << admin_activo.primer_nombre << ' ' << admin_activo.apellido; break;
        }
        if (tipo_usuario == U_CLT) {
            cout    << endl << "Libro rentado: " << cliente_activo.libro.nombre << endl << endl
                    << "(1) Buscar un libro" << endl << endl
                    << "Ingrese una opcion: ";

            do {
                cin >> accion;
            } while (accion < 1 || accion > 1);
        }
    }

    cout << endl << "Cerrando..." << endl;
}