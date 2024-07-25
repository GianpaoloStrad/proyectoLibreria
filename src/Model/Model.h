#ifndef MODELO_H
#define MODELO_H

#include <iostream>

using namespace std;

struct Libro {
    int id;
    string nombre;
    string editorial;
    string edicion;
    int cantidad;
    double precio;
};

struct Usuario {
    string usuario;
    string contrasena;
    bool activo;
};

struct Cliente : public Usuario {
    Libro* libroPrestado;
};

struct Empleado : public Usuario {};

struct Admin : public Usuario {};

class Modelo {
private:
    Libro* libros;
    int numLibros;
    Cliente* clientes;
    int numClientes;
    Empleado* empleados;
    int numEmpleados;
    Admin* admins;
    int numAdmins;

public:
    Modelo();
    ~Modelo();

    Cliente BuscarCliente(const string& usuario);
    Empleado BuscarEmpleado(const string& usuario);
    Admin BuscarAdmin(const string& usuario);
    Libro BuscarLibro(const string& nombre);
    Libro BuscarLibroPorID(int id);

    void AnadirLibro();
    void EliminarLibro(const Libro& libro);
    void ModificarLibro(const Libro& libro);

    void ComprarLibro(Cliente& cliente, const Libro& libro);
    void DevolverLibro(Cliente& cliente);

    void CambiarEstadoCliente(const string& usuario);
    void CambiarEstadoEmpleado(const string& usuario);
    void CambiarEstadoAdmin(const string& usuario);

    void EliminarCliente(const string& usuario);
    void EliminarEmpleado(const string& usuario);
    void EliminarAdmin(const string& usuario, const std::string& usuarioActivo);

    Libro* getLibros() const { return libros; }
    int getNumLibros() const { return numLibros; }
};

#endif
