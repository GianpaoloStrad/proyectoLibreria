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

    string usuario;
    string contrasena;
    Libro libro;
    string entrada_str = "";
    int tipo_usuario_otro = -1;
    Cliente cliente_otro = Cliente();
    Empleado empleado_otro = Empleado();
    Admin admin_otro = Admin();
    while (true) {
        bool error = false;
        bool reintentar = false;
        bool salir = false;
        char accion_c = ' ';
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

            case CLT_LIB:
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

            case CLT_LIB_RET:
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
            
            case CLT_LIB_CMP:
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

            case EMP_LIB:
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

            case EMP_LIB_ELI:
                EliminarLibro(libros, libro);
                cout << "El libro fue eliminado con exito";
                cin.ignore(1);
                getline(cin, entrada_str);
                break;
            
            case EMP_LIB_MOD:
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

            case ADM:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- ADMIN -----------" << endl << endl
                        << "Usuario: " << admin_activo.usuario << endl << endl
                        << "(1) Salir" << endl
                        << "(2) Buscar un libro" << endl
                        << "(3) Buscar un usuario" << endl
                        << "(4) Anadir un usuario" << endl << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 4);

                break;

            case ADM_CLT:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "------- ADMIN - CLIENTE -------" << endl << endl
                        << "Usuario: " << cliente_otro.usuario << endl
                        << "Nombre: " << cliente_otro.primer_nombre << ' ' << cliente_otro.apellido << endl
                        << "Genero: " << cliente_otro.genero << endl
                        << "Libro rentado: " << cliente_otro.libro.nombre << endl
                        << "Suspendido: " << (cliente_otro.suspendido ? "Si" : "No") << endl << endl
                        << "(1) Salir" << endl
                        << "(2) " << (cliente_otro.suspendido ? "Activar" : "Suspender") << endl
                        << "(3) Eliminar" << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case ADM_EMP:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "------- ADMIN - EMPLEADO ------" << endl << endl
                        << "Usuario: " << empleado_otro.usuario << endl
                        << "Nombre: " << empleado_otro.primer_nombre << ' ' << empleado_otro.apellido << endl
                        << "Genero: " << empleado_otro.genero << endl
                        << "Suspendido: " << (empleado_otro.suspendido ? "Si" : "No") << endl << endl
                        << "(1) Salir" << endl
                        << "(2) " << (empleado_otro.suspendido ? "Activar" : "Suspender") << endl
                        << "(3) Eliminar" << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case ADM_ADM:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "-------- ADMIN - ADMIN --------" << endl << endl
                        << "Usuario: " << admin_otro.usuario << endl
                        << "Nombre: " << admin_otro.primer_nombre << ' ' << admin_otro.apellido << endl
                        << "Genero: " << admin_otro.genero << endl
                        << "Suspendido: " << (admin_otro.suspendido ? "Si" : "No") << endl << endl
                        << "(1) Salir" << endl
                        << "(2) " << (admin_otro.suspendido ? "Activar" : "Suspender") << endl
                        << "(3) Eliminar" << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 3);

                break;

            case ADM_USR_SUS:
                switch (tipo_usuario_otro) {
                    case CLT: CambiarEstadoCliente(clientes, cliente_otro.usuario); break;
                    case EMP: CambiarEstadoEmpleado(empleados, empleado_otro.usuario); break;
                    case ADM: CambiarEstadoAdmin(admins, admin_otro.usuario); break;
                }

                cout << "El estado del usuario fue modificado con exito";

                cin.ignore(1);
                getline(cin, entrada_str);

                break;

            case ADM_USR_ELI:
                switch (tipo_usuario_otro) {
                    case CLT: error = EliminarCliente(clientes, cliente_otro.usuario); break;
                    case EMP: error = EliminarEmpleado(empleados, empleado_otro.usuario); break;
                    case ADM: error = EliminarAdmin(admins, admin_otro.usuario, admin_activo.usuario); break;
                }

                if (!error) 
                    cout << "El usuario fue eliminado con exito";
                else {
                    cout << "No es posible eliminar este usuario ya que esta siendo utilizado";
                    error = false;
                }

                cin.ignore(1);
                getline(cin, entrada_str);

                break;

            case ADM_USR_AND_1:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- ADMIN -----------" << endl << endl
                        << "(1) Salir" << endl
                        << "(2) Anadir cliente" << endl
                        << "(3) Anadir empleado" << endl
                        << "(4) Anadir admin" << endl << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 4);

                break;

            case ADM_USR_AND_2:
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "--- ADMIN - ANADIR USUARIO ---" << endl << endl
                        << "Usuario: ";
                switch (tipo_usuario_otro) {
                    case CLT: cin >> cliente_otro.usuario; break;
                    case EMP: cin >> empleado_otro.usuario; break;
                    case ADM: cin >> admin_otro.usuario; break;
                }
                cout << "Contrasena: ";
                switch (tipo_usuario_otro) {
                    case CLT: cin >> cliente_otro.contrasena; break;
                    case EMP: cin >> empleado_otro.contrasena; break;
                    case ADM: cin >> admin_otro.contrasena; break;
                }
                cout << "Primer nombre: ";
                switch (tipo_usuario_otro) {
                    case CLT: cin >> cliente_otro.primer_nombre; break;
                    case EMP: cin >> empleado_otro.primer_nombre; break;
                    case ADM: cin >> admin_otro.primer_nombre; break;
                }
                cout << "Apellido: ";
                switch (tipo_usuario_otro) {
                    case CLT: cin >> cliente_otro.apellido; break;
                    case EMP: cin >> empleado_otro.apellido; break;
                    case ADM: cin >> admin_otro.apellido; break;
                }
                cout << "Genero: ";
                do {
                    cin >> accion_c;
                    accion_c = toupper(accion_c);
                } while (accion_c != 'M' && accion_c != 'F');
                switch (tipo_usuario_otro) {
                    case CLT: cliente_otro.genero = accion_c; break;
                    case EMP: empleado_otro.genero = accion_c; break;
                    case ADM: admin_otro.genero = accion_c; break;
                }
                switch (tipo_usuario_otro) {
                    case CLT: AnadirCliente(clientes, cliente_otro); break;
                    case EMP: AnadirEmpleado(empleados, empleado_otro); break;
                    case ADM: AnadirAdmin(admins, admin_otro); break;
                }

                cout << "El " << CodUsuarioAString(tipo_usuario_otro) << " ha sido anadido con exito";

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

                    if (tolower(accion_c) == 'y') reintentar = true;
                    else reintentar = false;
                }
                break;

            case USR_BSC_1:
                temp = CodUsuarioAString(tipo_usuario);
                for (auto &c : temp)
                    c = toupper(c);
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl 
                        << "----------- " << temp << " -----------" << endl << endl
                        << "(1) Salir" << endl
                        << "(2) Buscar cliente" << endl
                        << "(3) Buscar empleado" << endl
                        << "(4) Buscar admin" << endl << endl
                        << "Ingrese una opcion: ";

                do {
                    cin >> accion_sig;
                } while (accion_sig < 1 || accion_sig > 4);

                break;

            case USR_BSC_2:
                temp = CodUsuarioAString(tipo_usuario);
                for (auto &c : temp)
                    c = toupper(c);
                system("cls");
                cout    << "TERMINAL DE USUARIO DE LIBRERIA" << endl
                        << "----------- " << temp << " -----------" << endl << endl
                        << "Ingrese el usuario del " << CodUsuarioAString(tipo_usuario_otro) << ": ";

                cin.ignore(1);
                getline(cin, entrada_str);

                switch (tipo_usuario_otro) {
                    case CLT:
                        cliente_otro = BuscarCliente(clientes, entrada_str);
                        if (cliente_otro.usuario == "") error = true;
                        break;
                    case EMP:
                        empleado_otro = BuscarEmpleado(empleados, entrada_str);
                        if (empleado_otro.usuario == "") error = true;
                        break;
                    case ADM:
                        admin_otro = BuscarAdmin(admins, entrada_str);
                        if (admin_otro.usuario == "") error = true;
                        break;
                }

                break;

            case ERR_USR:
                cout    << "No se encontro ningun " << CodUsuarioAString(tipo_usuario_otro) << " con el usuario `" << entrada_str << "`." << endl
                        << "Desea probar de nuevo? (y/n)";
                    
                do {
                    cin >> accion_c;
                } while (tolower(accion_c) != 'y' && tolower(accion_c) != 'n');

                if (tolower(accion_c) == 'y') reintentar = true;
                else reintentar = false;

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
            case CLT_LIB:
                switch (accion_sig) {
                    case 1: accion = CLT; break;
                    case 2: accion = CLT_LIB_RET; break;
                    case 3: accion = CLT_LIB_CMP; break;
                }
                break;
            case CLT_LIB_RET:
            case CLT_LIB_CMP:
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
            case EMP_LIB:
                switch (accion_sig) {
                    case 1: accion = EMP; break;
                    case 2: accion = EMP_LIB_ELI; break;
                    case 3: accion = EMP_LIB_MOD; break;
                }
                break;
            case EMP_LIB_ELI:
            case EMP_LIB_MOD:
                accion = tipo_usuario;
                break;
            case EMP_AND:
                accion = EMP;
                break;
            case ADM:
                switch (accion_sig) {
                    case 1: accion = LOG; break;
                    case 2: accion = LIB_BSC_1; break;
                    case 3: accion = USR_BSC_1; break;
                    case 4: accion = ADM_USR_AND_1; break;
                }
                break;
            case ADM_CLT:
            case ADM_EMP:
            case ADM_ADM:
                switch(accion_sig) {
                    case 1: accion = ADM; break;
                    case 2: accion = ADM_USR_SUS; break;
                    case 3: accion = ADM_USR_ELI; break;
                }
                break;
            case ADM_USR_SUS:
            case ADM_USR_ELI:
            case ADM_USR_AND_2:
                accion = ADM;
                break;
            case ADM_USR_AND_1:
                switch (accion_sig) {
                    case 1: accion = ADM; break;
                    case 2:
                    case 3:
                    case 4:
                        tipo_usuario_otro = accion_sig - 1;
                        accion = ADM_USR_AND_2;
                        break;
                }
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
                        case CLT: accion = CLT_LIB; break;
                        case EMP:
                        case ADM: accion = EMP_LIB; break;
                    }
                break;
            case USR_BSC_1:
                switch (accion_sig) {
                    case 1: accion = tipo_usuario; break;
                    case 2:
                    case 3:
                    case 4:
                        tipo_usuario_otro = accion_sig - 1;
                        accion = USR_BSC_2;
                        break;
                }
                break;
            case USR_BSC_2:
                if (error) accion = ERR_USR;
                else
                    switch (tipo_usuario) {
                        case CLT:
                        case EMP: throw("USR_BSC_2 no esta implementado para CLT o EMP"); break;
                        case ADM:
                            switch (tipo_usuario_otro) {
                                case CLT: accion = ADM_CLT; break;
                                case EMP: accion = ADM_EMP; break;
                                case ADM: accion = ADM_ADM; break;
                            }
                            break;
                    }
                break;
            case ERR_USR:
                if (reintentar) accion = USR_BSC_1;
                else accion = tipo_usuario;
                break;
            default:
                cout << "Accion no reconocida (no debio ser cambiada): " << accion << endl;
                throw;
        }
    }
    cout << endl << "Cerrando..." << endl;
}