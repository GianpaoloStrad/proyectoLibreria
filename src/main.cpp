#include <iostream>
#include "./lib/libro/libro.h"
#include "./lib/cliente/cliente.h"
#include "./lib/empleado/empleado.h"
#include "./lib/admin/admin.h"
#include "./lib/definiciones.h"
#include "./lib/herramientas/conversiones.h"

using std::cout, std::endl, std::cin, std::getline;

int main() {
    cout << "Iniciando..." << endl << endl;

    Libro libros[NUM_LIBROS] = {};
    Cliente clientes[NUM_CLIENTES] = {};
    Empleado empleados[NUM_EMPLEADOS] = {};
    Admin admins[NUM_ADMINS] = {};

    ObtenerLibros(libros);
    ObtenerClientes(clientes, libros);
    ObtenerEmpleados(empleados);
    ObtenerAdmins(admins);

    while (true) {
        Cliente cliente_activo = Cliente();
        Empleado empleado_activo = Empleado();
        Admin admin_activo = Admin();
        int tipo_usuario = -1;
        int accion = -1;
        char accion_c = ' ';

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
                cout    <<  "No se encontro ningun " << CodUsuarioAString(tipo_usuario) << " con las credenciales introducidas." << endl
                        <<  "Desea probar de nuevo? (y/n): ";
                do {
                    cin >> accion_c;
                } while (tolower(accion_c) != 'y' && tolower(accion_c) != 'n');

                if (accion_c == 'y') {
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

        while (true) {
            bool break1 = false;

            system("cls");
            string temp = "";
            for(auto c : CodUsuarioAString(tipo_usuario))
                temp += toupper(c);

            cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                    << "---------- " << temp << " ------------" << endl << endl
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

            Libro libro;
            string entrada_str = "";
            switch (tipo_usuario) {
                case U_CLT:
                    cout    << endl << "Libro rentado: " << cliente_activo.libro.nombre << endl << endl
                            << "(1) Salir" << endl
                            << "(2) Buscar un libro" << endl
                            << "(3) Devolver libro" << endl << endl
                            << "Ingrese una opcion: ";

                    do {
                        cin >> accion;
                    } while (accion < 1 || accion > 3);

                    while (true) {
                        bool break2 = false;

                        system("cls");
                        cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                                << "---------- " << temp << " ------------" << endl << endl;
                        cin.ignore(1);
                        switch (accion) {
                            case 1:
                                break1 = true;
                                break2 = true;
                                break;
                            case 2:
                                cout << "Ingrese el nombre del libro (Salir: e): ";
                                getline(cin, entrada_str);
                                if (entrada_str == "e") {
                                    break2 = true;
                                    break;
                                }
                                libro = BuscarLibro(libros, entrada_str);
                                if (libro.id != -1) {
                                    system("cls");
                                    cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                                            << "----------- LIBRO -------------" << endl << endl
                                            << "ID: " << libro.id << endl
                                            << "Nombre: " << libro.nombre << endl
                                            << "Editorial: " << libro.editorial << endl
                                            << "Edicion: " << libro.edicion << endl
                                            << "Cantidad disp.: " << libro.cantidad << endl
                                            << "Precio: " << libro.precio << '$' << endl << endl
                                            << "(1) Salir" << endl
                                            << "(2) Retirar" << endl
                                            << "(3) Comprar" << endl << endl
                                            << "Ingrese una opcion: ";

                                    do {
                                        cin >> accion;
                                    } while (accion < 1 || accion > 3);

                                    switch (accion) {
                                        case 1: break;
                                        case 2:
                                            if (libro.cantidad <= 0) {
                                                cout << "Este libro no esta en existencia actualmente" << endl;
                                            } else if (cliente_activo.libro.id != -1) {
                                                cout    << "Ya has retirado un libro. Debes devolverlo antes" << endl
                                                        << "de poder retirar otro";
                                            } else {
                                                RetirarLibro(clientes, libros, cliente_activo, libro);
                                                cout << "El libro ha sido retirado con exito";
                                            }
                                            cin.ignore(1);
                                            getline(cin, entrada_str);
                                            break2 = true;
                                            break;
                                        case 3:
                                            if (libro.cantidad <= 0) {
                                                cout << "Este libro no esta en existencia actualmente" << endl;
                                            } else {
                                                ComprarLibro(clientes, libros, cliente_activo, libro);
                                                cout << "El libro ha sido comprado con exito";
                                            }
                                            cin.ignore(1);
                                            getline(cin, entrada_str);
                                            break2 = true;
                                            break;
                                    }
                                } else {
                                    cout    << "No se encontro ningun libro con el nombre `" << entrada_str << "`." << endl
                                            << "Desea probar de nuevo? (y/n)";

                                    do {
                                        cout << 'a' << endl;
                                        cin >> accion_c;
                                    } while (tolower(accion_c) != 'y' && tolower(accion_c) != 'n');

                                    if (accion_c == 'y') {
                                        break2 = false;
                                    } else {
                                        break2 = true;
                                    }
                                }
                                break;
                            case 3:
                                if (cliente_activo.libro.id != -1) {
                                    DevolverLibro(clientes, libros, cliente_activo);
                                    cout << "El libro ha sido devuelto con exito" << endl;
                                } else {
                                    cout << "No has rentado ningun libro" << endl;
                                }
                                cin.ignore(1);
                                getline(cin, entrada_str);
                                break2 = true;
                                break;
                        }
                        if (break2)
                            break;
                    }
                    break;
                case U_EMP:
                    Libro libro;
                    cout    << endl << endl
                            << "(1) Salir" << endl
                            << "(2) Buscar un libro" << endl
                            << "(3) Anadir un libro" << endl << endl
                            << "Ingrese una opcion: ";
                    do {
                        cin >> accion;
                    } while (accion < 1 || accion > 3);

                    while (true) {
                        bool break2 = false;

                        system("cls");
                        cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                                << "---------- " << temp << " ------------" << endl << endl;
                        cin.ignore(1);
                        switch (accion) {
                            case 1:
                                break1 = true;
                                break2 = true;
                                break;
                            case 2:
                                cout << "Ingrese el nombre del libro (Salir: e): ";
                                getline(cin, entrada_str);
                                if (entrada_str == "e") {
                                    break2 = true;
                                    break;
                                }
                                libro = BuscarLibro(libros, entrada_str);
                                if (libro.id != -1) {
                                    system("cls");
                                    cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                                            << "----------- LIBRO -------------" << endl << endl
                                            << "ID: " << libro.id << endl
                                            << "Nombre: " << libro.nombre << endl
                                            << "Editorial: " << libro.editorial << endl
                                            << "Edicion: " << libro.edicion << endl
                                            << "Cantidad disp.: " << libro.cantidad << endl
                                            << "Precio: " << libro.precio << '$' << endl << endl
                                            << "(1) Salir"
                                            << "(2) Eliminar" << endl
                                            << "(3) Modificar" << endl << endl
                                            << "Ingrese una opcion: ";
                                    
                                    do {
                                        cin >> accion;
                                    } while (accion < 1 || accion > 3);

                                    switch (accion) {
                                        case 1: break;
                                        case 2:
                                            EliminarLibro(libros, libro);
                                            cout << "El libro fue eliminado con exito";
                                            cin.ignore(1);
                                            getline(cin, entrada_str);
                                            break;
                                        case 3:
                                            ModificarLibro(libros, libro);
                                            cout << "El libro fue modificado con exito";
                                            cin.ignore(1);
                                            getline(cin, entrada_str);
                                            break;
                                    }
                                }
                                break;
                            case 3:
                                AnadirLibro(libros);
                                cout << "El libro fue anadido con exito";
                                cin.ignore(1);
                                getline(cin, entrada_str);
                                break;
                        }
                    }
                    break;
            }
            if (break1)
                break;
        }
    }
    cout << endl << "Cerrando..." << endl;
}