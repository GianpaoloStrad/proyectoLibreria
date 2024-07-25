#include <iostream>
#include "../Model/Model.h"

using namespace std;

class Vista {
public:
    int mostrarMenuLogin() {
        cout << "----------- MENU LOGIN -------------" << endl << endl
             << "(1) Cliente" << endl
             << "(2) Empleado" << endl
             << "(3) Admin" << endl
             << "(4) Salir" << endl << endl
             << "Ingrese una opcion: ";
        int opcion;
        cin >> opcion;
        return opcion;
    }

    string ingresarUsuario() {
        cout << "Ingrese su usuario: ";
        string usuario;
        cin >> usuario;
        return usuario;
    }

    string ingresarContrasena() {
        cout << "Ingrese su contraseña: ";
        string contrasena;
        cin >> contrasena;
        return contrasena;
    }

    void mostrarMensajeErrorLogin(const string& tipoUsuario) {
        cout << "Error: Usuario o contraseña incorrectos para " << tipoUsuario << "." << endl;
    }

    void mostrarMenuCliente() {
        cout << "----------- MENU CLIENTE -------------" << endl << endl
             << "(1) Ver catalogo de libros" << endl
             << "(2) Comprar libro" << endl
             << "(3) Devolver libro" << endl
             << "(4) Salir" << endl << endl
             << "Ingrese una opcion: ";
    }

    void mostrarMenuEmpleado() {
        cout << "----------- MENU EMPLEADO -------------" << endl << endl
             << "(1) Ver catalogo de libros" << endl
             << "(2) Gestionar libros" << endl
             << "(3) Gestionar clientes" << endl
             << "(4) Gestionar empleados" << endl
             << "(5) Salir" << endl << endl
             << "Ingrese una opcion: ";
    }

    void mostrarMenuAdmin() {
        cout << "----------- MENU ADMIN -------------" << endl << endl
             << "(1) Ver catalogo de libros" << endl
             << "(2) Gestionar libros" << endl
             << "(3) Gestionar clientes" << endl
             << "(4) Gestionar empleados" << endl
             << "(5) Gestionar admins" << endl
             << "(6) Salir" << endl << endl
             << "Ingrese una opcion: ";
    }

    void mostrarMenuGestionLibros() {
        cout << "----------- GESTIONAR LIBROS -------------" << endl << endl
             << "(1) Eliminar libro" << endl
             << "(2) Modificar libro" << endl
             << "(3) Añadir libro" << endl
             << "(4) Volver" << endl << endl
             << "Ingrese una opcion: ";
    }

    void mostrarMensajeError(const string& mensaje) {
        cout << "Error: " << mensaje << endl;
    }

    void mostrarCatalogoLibros(Libro* libros, int numLibros) {
        cout << "----------- CATALOGO DE LIBROS -------------" << endl << endl;
        for (int i = 0; i < numLibros; ++i) {
            cout << "ID: " << libros[i].id << endl
                 << "Nombre: " << libros[i].nombre << endl
                 << "Editorial: " << libros[i].editorial << endl
                 << "Edicion: " << libros[i].edicion << endl
                 << "Cantidad: " << libros[i].cantidad << endl
                 << "Precio: " << libros[i].precio << endl << endl;
        }
    }

    void mostrarMenuAccionUsuario(const string& tipoUsuario) {
        cout << "----------- MENU ACCIONES " << tipoUsuario << " -------------" << endl << endl
             << "(1) Cambiar estado de usuario" << endl
             << "(2) Eliminar usuario" << endl
             << "(3) Volver" << endl << endl
             << "Ingrese una opcion: ";
    }
};
