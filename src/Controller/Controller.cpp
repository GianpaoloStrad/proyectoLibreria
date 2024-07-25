#include <iostream>
#include "../lib/libro/libro.h"
#include "../lib/cliente/cliente.h"
#include "../lib/empleado/empleado.h"
#include "../lib/admin/admin.h"
#include "../lib/definiciones.h"
#include "../lib/herramientas/conversiones.h"
#include "../View/View.cpp"
#include "../Model/Model.h"

using std::cout, std::endl, std::cin, std::getline;

class Controller {
private:
    Modelo Modelo;
    Vista vista;
    string usuarioActivo;
    int tipoUsuarioActivo;

public:
    void iniciar() {
        int opcion;
        do {
            opcion = vista.mostrarMenuLogin();

            switch (opcion) {
                case 1:
                    gestionarLogin("Cliente");
                    break;
                case 2:
                    gestionarLogin("Empleado");
                    break;
                case 3:
                    gestionarLogin("Admin");
                    break;
                case 4:
                    cout << "Saliendo..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 4);
    }

    void gestionarLogin(const string& tipoUsuario) {
        string usuario = vista.ingresarUsuario();
        string contrasena = vista.ingresarContrasena();

        if (tipoUsuario == "Cliente") {
            Cliente cliente = Modelo.BuscarCliente(usuario);
            if (cliente.contrasena == contrasena && cliente.activo) {
                usuarioActivo = cliente.usuario;
                tipoUsuarioActivo = 1;
                gestionarMenuCliente();
            } else {
                vista.mostrarMensajeErrorLogin("cliente");
            }
        } else if (tipoUsuario == "Empleado") {
            Empleado empleado = Modelo.BuscarEmpleado(usuario);
            if (empleado.contrasena == contrasena && empleado.activo) {
                usuarioActivo = empleado.usuario;
                tipoUsuarioActivo = 2;
                gestionarMenuEmpleado();
            } else {
                vista.mostrarMensajeErrorLogin("empleado");
            }
        } else if (tipoUsuario == "Admin") {
            Admin admin = Modelo.BuscarAdmin(usuario);
            if (admin.contrasena == contrasena && admin.activo) {
                usuarioActivo = admin.usuario;
                tipoUsuarioActivo = 3;
                gestionarMenuAdmin();
            } else {
                vista.mostrarMensajeErrorLogin("admin");
            }
        }
    }

    void gestionarMenuCliente() {
        int opcion;
        do {
            vista.mostrarMenuCliente();
            cin >> opcion;

            switch (opcion) {
                case 1:
                    vista.mostrarCatalogoLibros(Modelo.getLibros(), Modelo.getNumLibros());
                    break;
                case 2:
                     if (libro.cantidad <= 0) {
                    cout << "Este libro no esta en existencia actualmente" << endl;
                } else {
                    ComprarLibro(clientes, libros, cliente_activo, libro);
                    cout << "El libro ha sido comprado con exito";
                }
                cin.ignore(1);
                getline(cin, entrada_str);
                break;
                    break;
                case 3:
                     if (cliente_activo.libro.id != -1) {
                    DevolverLibro(clientes, libros, cliente_activo);
                    cout << "El libro ha sido devuelto con exito" << endl;
                } else {
                    cout << "No has rentado ningun libro" << endl;
                    break;
                case 4:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 4);
    }

    void gestionarMenuEmpleado() {
        int opcion;
        do {
            vista.mostrarMenuEmpleado();
            cin >> opcion;

            switch (opcion) {
                case 1:
                    vista.mostrarCatalogoLibros(Modelo.getLibros(), Modelo.getNumLibros());
                    break;
                case 2:
                    gestionarMenuGestionLibros();
                    break;
                case 3:
                    gestionarMenuGestionUsuarios("cliente");
                    break;
                case 4:
                    gestionarMenuGestionUsuarios("empleado");
                    break;
                case 5:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 5);
    }

    void gestionarMenuAdmin() {
        int opcion;
        do {
            vista.mostrarMenuAdmin();
            cin >> opcion;

            switch (opcion) {
                case 1:
                    vista.mostrarCatalogoLibros(Modelo.getLibros(), Modelo.getNumLibros());
                    break;
                case 2:
                    gestionarMenuGestionLibros();
                    break;
                case 3:
                    gestionarMenuGestionUsuarios("cliente");
                    break;
                case 4:
                    gestionarMenuGestionUsuarios("empleado");
                    break;
                case 5:
                    gestionarMenuGestionUsuarios("admin");
                    break;
                case 6:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 6);
    }

    void gestionarMenuGestionLibros() {
        int opcion;
        do {
            vista.mostrarMenuGestionLibros();
            cin >> opcion;

            switch (opcion) {
                case 1:
                    gestionarEliminarLibro();
                    break;
                case 2:
                    gestionarModificarLibro();
                    break;
                case 3:
                    Modelo.AnadirLibro();
                    cout << "Libro añadido correctamente." << endl;
                    break;
                case 4:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 4);
    }

    void gestionarEliminarLibro() {
        int id;
        cout << "Ingrese el ID del libro a eliminar: ";
        cin >> id;

        Libro libro = Modelo.BuscarLibroPorID(id);
        if (libro.id != -1) {
            Modelo.EliminarLibro(libro);
            cout << "Libro eliminado exitosamente." << endl;
        } else {
            cout << "Libro no encontrado." << endl;
        }
    }

    void gestionarModificarLibro() {
        int id;
        cout << "Ingrese el ID del libro a modificar: ";
        cin >> id;

        Libro libro = Modelo.BuscarLibroPorID(id);
        if (libro.id != -1) {
            // Lógica para modificar el libro
            Modelo.ModificarLibro(libro);
            cout << "Libro modificado exitosamente." << endl;
        } else {
            cout << "Libro no encontrado." << endl;
        }
    }

    void gestionarMenuGestionUsuarios(const string& tipoUsuario) {
        int opcion;
        do {
            vista.mostrarMenuAccionUsuario(tipoUsuario);
            cin >> opcion;

            switch (opcion) {
                case 1:
                    gestionarCambiarEstadoUsuario(tipoUsuario);
                    break;
                case 2:
                    gestionarEliminarUsuario(tipoUsuario);
                    break;
                case 3:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo." << endl;
                    break;
            }
        } while (opcion != 3);
    }

    void gestionarCambiarEstadoUsuario(const string& tipoUsuario) {
        string usuario;
        cout << "Ingrese el usuario a cambiar el estado: ";
        cin >> usuario;

        if (tipoUsuario == "cliente") {
            Modelo.CambiarEstadoCliente(usuario);
        } else if (tipoUsuario == "empleado") {
            Modelo.CambiarEstadoEmpleado(usuario);
        } else if (tipoUsuario == "admin") {
            Modelo.CambiarEstadoAdmin(usuario);
        }
    }

    void gestionarEliminarUsuario(const string& tipoUsuario) {
        string usuario;
        cout << "Ingrese el usuario a eliminar: ";
        cin >> usuario;

        if (tipoUsuario == "cliente") {
            Modelo.EliminarCliente(usuario);
        } else if (tipoUsuario == "empleado") {
            Modelo.EliminarEmpleado(usuario);
        } else if (tipoUsuario == "admin") {
            Modelo.EliminarAdmin(usuario, usuarioActivo);
        }
    }
};