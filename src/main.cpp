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

    Cliente cliente_activo = Cliente();
    Empleado empleado_activo = Empleado();
    Admin admin_activo = Admin();
    int tipo_usuario = -1;
    int accion = 0;
    int accion_ant = -1;
    int accion_sig = -1;
    char accion_c = ' ';

    string usuario;
    string contrasena;
    Libro libro;
    string entrada_str = "";
    while (true) {
        bool error = false;
        bool reintentar = false;
        bool salir = false;
        string temp = "";
        switch (accion) {
            case LOG:
                system("cls");
                cout << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                << "----------- LOGIN -------------" << endl << endl
                << "(1) Cliente" << endl
                << "(2) Empleado" << endl
                << "(3) Admin" << endl
                << "(4) Salir" << endl << endl
                << "Ingrese una opcion: ";
                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 4);
                
                if (accion_sig == 4) return 0;

                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                        << "----------- LOGIN -------------" << endl << endl
                        << "Usuario: ";

                cin >> usuario;
                cout << "Contrasena: ";
                cin >> contrasena;
                break;

            case LOG_CLT:
                cliente_activo = BuscarCliente(clientes, usuario);
                error = (cliente_activo.usuario != usuario || cliente_activo.contrasena != contrasena);
                break;

            case LOG_EMP:
                empleado_activo = BuscarEmpleado(empleados, usuario);
                error = (empleado_activo.usuario != usuario || empleado_activo.contrasena != contrasena);
                break;

            case LOG_ADM:
                admin_activo = BuscarAdmin(admins, usuario);
                error = (admin_activo.usuario != usuario || admin_activo.contrasena != contrasena);
                break;

            case ERR_LOG:
                cout    <<  "No se encontro ningun " << CodUsuarioAString(tipo_usuario) << " con las credenciales introducidas." << endl
                        <<  "Desea probar de nuevo? (y/n): ";
                do {
                    cin >> accion_c;
                } while (tolower(accion_c) != 'y' && tolower(accion_c) != 'n');

                if (accion_c == 'y') {
                    cliente_activo = Cliente();
                    empleado_activo = Empleado();
                    admin_activo = Admin();
                    reintentar = true;
                } else {
                    reintentar = false;
                }
                break;

            case CLT:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- CLIENTE -----------" << endl << endl
                        << "Usuario: " << cliente_activo.usuario << endl
                        << "Libro rentado: " << cliente_activo.libro.nombre << endl << endl
                        << "(1) Salir" << endl
                        << "(2) Buscar un libro" << endl
                        << "(3) Devolver libro" << endl << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case CLT_BSC:
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
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case CLT_BSC_RET:
                if (libro.cantidad <= 0)
                    cout << "Este libro no esta en existencia actualmente" << endl;
                else if (cliente_activo.libro.id != -1) {
                    cout    << "Ya has retirado un libro. Debes devolverlo antes" << endl
                            << "de poder retirar otro";
                } else {
                    RetirarLibro(clientes, libros, cliente_activo, libro);
                    cout << "El libro ha sido retirado con exito";
                }
                cin.ignore(1);
                getline(cin, entrada_str);
                break;
            
            case CLT_BSC_CMP:
                if (libro.cantidad <= 0) {
                    cout << "Este libro no esta en existencia actualmente" << endl;
                } else {
                    ComprarLibro(clientes, libros, cliente_activo, libro);
                    cout << "El libro ha sido comprado con exito";
                }
                cin.ignore(1);
                getline(cin, entrada_str);
                break;

            case CLT_DVL:
                if (cliente_activo.libro.id != -1) {
                    DevolverLibro(clientes, libros, cliente_activo);
                    cout << "El libro ha sido devuelto con exito" << endl;
                } else {
                    cout << "No has rentado ningun libro" << endl;
                }
                cin.ignore(1);
                getline(cin, entrada_str);
                break;

            case EMP:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- EMPLEADO -----------" << endl << endl
                        << "(1) Salir" << endl
                        << "(2) Buscar un libro" << endl
                        << "(3) Anadir un libro" << endl << endl
                        << "Ingrese una opcion: ";
                
                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case EMP_BSC:
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
                        << "(2) Eliminar" << endl
                        << "(3) Modificar" << endl << endl
                        << "Ingrese una opcion: ";
                
                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case EMP_BSC_ELI:
                EliminarLibro(libros, libro);
                cout << "El libro fue eliminado con exito";
                cin.ignore(1);
                getline(cin, entrada_str);
                break;
            
            case EMP_BSC_MOD:
                ModificarLibro(libros, libro);
                cout << "El libro fue modificado con exito";
                cin.ignore(1);
                getline(cin, entrada_str);
                break;

            case EMP_AND:
                AnadirLibro(libros);
                cout << "El libro fue anadido con exito";
                cin.ignore(1);
                getline(cin, entrada_str);
                break;

            case LIB_BSC_1:
                temp = CodUsuarioAString(tipo_usuario);
                for (auto &c : temp)
                    c = toupper(c);
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- " << temp << " -----------" << endl << endl;

                cout << "Ingrese el nombre del libro (Salir: e): ";
                cin.ignore(1);
                getline(cin, entrada_str);

                if (entrada_str == "e") {
                    salir = true;
                }

                break;
            
            case LIB_BSC_2:
                libro = BuscarLibro(libros, entrada_str);
                if (libro.id == -1) {
                    error = true;

                    cout    << "No se encontro ningun libro con el nombre `" << entrada_str << "`." << endl
                            << "Desea probar de nuevo? (y/n)";
                    
                    do {
                        cin >> accion_c;
                    } while (tolower(accion_c) != 'y' && tolower(accion_c) != 'n');

                    if (accion_c == 'y') reintentar = true;
                    else reintentar = false;
                }
                break;

            default:
                cout << "Accion no reconocida: " << accion << endl;
                throw;
        }
        accion_ant = accion;
        switch (accion) {
            case LOG:
                tipo_usuario = accion_sig;
                switch (accion_sig) {
                    case 1: accion = LOG_CLT; break;
                    case 2: accion = LOG_EMP; break;
                    case 3: accion = LOG_ADM; break;
                }
                break;
            case LOG_CLT:
                if (error) accion = ERR_LOG;
                else accion = CLT;
                break;
            case LOG_EMP:
                if (error) accion = ERR_LOG;
                else accion = EMP;
                break;
            case LOG_ADM:
                if (error) accion = ERR_LOG;
                else accion = ADM;
                break;
            case ERR_LOG:
                error = false;
                if (reintentar) accion = LOG;
                else return 0;
                break;
            case CLT:
                switch (accion_sig) {
                    case 1: accion = LOG; break;
                    case 2: accion = LIB_BSC_1; break;
                    case 3: accion = CLT_DVL; break;
                }
                break;
            case CLT_BSC:
                switch (accion_sig) {
                    case 1: accion = CLT; break;
                    case 2: accion = CLT_BSC_RET; break;
                    case 3: accion = CLT_BSC_CMP; break;
                }
                break;
            case CLT_BSC_RET:
            case CLT_BSC_CMP:
            case CLT_DVL:
                accion = CLT;
                break;
            case EMP:
                switch (accion_sig) {
                    case 1: accion = LOG; break;
                    case 2: accion = LIB_BSC_1; break;
                    case 3: accion = EMP_AND; break;
                }
                break;
            case EMP_BSC:
                switch (accion_sig) {
                    case 1: accion = EMP; break;
                    case 2: accion = EMP_BSC_ELI; break;
                    case 3: accion = EMP_BSC_MOD; break;
                }
                break;
            case EMP_BSC_ELI:
            case EMP_BSC_MOD:
            case EMP_AND:
                accion = EMP;
                break;
            case LIB_BSC_1:
                if (salir) accion = tipo_usuario;
                else accion = LIB_BSC_2;
                break;
            case LIB_BSC_2:
                if (error)
                    if (reintentar) accion = LIB_BSC_1;
                    else accion = tipo_usuario;
                else
                    switch (tipo_usuario) {
                        case CLT: accion = CLT_BSC; break;
                        case EMP: accion = EMP_BSC; break;
                        case ADM: throw("no hay LIB_BSC_2 definido para admin"); break;
                    }
                break;
            default:
                cout << "Accion no reconocida (no debio ser cambiada): " << accion << endl;
                throw;
        }
    }
    cout << endl << "Cerrando..." << endl;
}