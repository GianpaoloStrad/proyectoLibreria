#pragma once
#include <string>
#include "../cliente/cliente.h"
#include "../empleado/empleado.h"
#include "../definiciones.h"

using std::string;

const int NUM_ADMINS = 10;

struct Admin {
    Admin();
    string usuario;
    string contrasena;
    string primer_nombre;
    string apellido;
    char genero;
    bool suspendido;
};

void ObtenerAdmins(Admin admins[]);
Admin BuscarAdmin(Admin admins[], string usuario);
void CambiarEstadoCliente(Cliente clientes[], string usuario);
void CambiarEstadoEmpleado(Empleado empleados[], string usuario);
void CambiarEstadoAdmin(Admin admins[], string usuario);
bool EliminarCliente(Cliente clientes[], string usuario);
bool EliminarEmpleado(Empleado empleados[], string usuario);
bool EliminarAdmin(Admin admins[], string usuario, string usuario_admin_activo);
void ActualizarAdminsCSV(Admin admins[]);