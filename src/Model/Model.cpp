#include "../Model/Model.h"

#include <cstring>

Modelo::Modelo() {
    libros = nullptr;
    numLibros = 0;
    clientes = nullptr;
    numClientes = 0;
    empleados = nullptr;
    numEmpleados = 0;
    admins = nullptr;
    numAdmins = 0;
};

Modelo::~Modelo() {
    delete[] libros;
    delete[] clientes;
    delete[] empleados;
    delete[] admins;
}

Cliente Modelo::BuscarCliente(const std::string& usuario) {
    // Implementación de búsqueda de cliente
}

Empleado Modelo::BuscarEmpleado(const std::string& usuario) {
    // Implementación de búsqueda de empleado
}

Admin Modelo::BuscarAdmin(const std::string& usuario) {
    // Implementación de búsqueda de admin
}

Libro Modelo::BuscarLibro(const std::string& nombre) {
    // Implementación de búsqueda de libro por nombre
}

Libro Modelo::BuscarLibroPorID(int id) {
    // Implementación de búsqueda de libro por ID
}

void Modelo::AnadirLibro() {
    // Implementación para añadir un libro al arreglo dinámico de libros
}

void Modelo::EliminarLibro(const Libro& libro) {
    // Implementación para eliminar un libro del arreglo dinámico de libros
}

void Modelo::ModificarLibro(const Libro& libro) {
    // Implementación para modificar un libro en el arreglo dinámico de libros
}

void Modelo::ComprarLibro(Cliente& cliente, const Libro& libro) {
    // Implementación para comprar un libro
}

void Modelo::DevolverLibro(Cliente& cliente) {
    // Implementación para devolver un libro
}

void Modelo::CambiarEstadoCliente(const std::string& usuario) {
    // Implementación para cambiar el estado de un cliente
}

void Modelo::CambiarEstadoEmpleado(const std::string& usuario) {
    // Implementación para cambiar el estado de un empleado
}

void Modelo::CambiarEstadoAdmin(const std::string& usuario) {
    // Implementación para cambiar el estado de un admin
}

void Modelo::EliminarCliente(const std::string& usuario) {
    // Implementación para eliminar un cliente
}

void Modelo::EliminarEmpleado(const std::string& usuario) {
    // Implementación para eliminar un empleado
}

void Modelo::EliminarAdmin(const std::string& usuario, const std::string& usuarioActivo) {
    // Implementación para eliminar un admin
}
