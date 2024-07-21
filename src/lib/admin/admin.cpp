#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "admin.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl, std::ofstream;

Admin::Admin() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' ')
{}

void ObtenerAdmins(Admin admins[]) {
    ifstream csv_stream(ADMINS_CSV);
    if (!csv_stream) {
        cout << "ERROR AL ABRIR `admins.csv`" << endl;
        throw;
    }
    string linea;
    getline(csv_stream, linea);
    for (int i = 0; getline(csv_stream, linea); i++) {
        stringstream linea_stream(linea);
        string campo;
        for (int j = 0; getline(linea_stream, campo, ';'); j++) {
            try {
                switch (j) {
                    case 0: admins[i].usuario = campo; break;
                    case 1: admins[i].contrasena = campo; break;
                    case 2: admins[i].primer_nombre = campo; break;
                    case 3: admins[i].apellido = campo; break;
                    case 4: 
                        if (toupper(campo[0]) == 'M' || toupper(campo[0] == 'F'))
                            admins[i].genero = toupper(campo[0]);
                        else
                            throw ("genero invalido hallado");
                        break;
                    case 5:
                        switch (tolower(campo[0])) {
                            case 't': admins[i].suspendido = true; break;
                            case 'f': admins[i].suspendido = false; break;
                            default: throw("estado de suspension desconocido"); break;
                        }
                        break;
                    default: throw ("demasiados campos hallados"); break;
                }
            } catch (const char* e) {
                cout << "ERROR AL OBTENER admin " << i + 1 << ": " << e << endl;
                throw;
            } catch (std::invalid_argument e) {
                cout << "ERROR AL OBTENER admin " << i + 1 << ": " << e.what() << endl; 
                throw;
            }
        } 
    }
}

Admin BuscarAdmin(Admin admins[], string usuario) {
    for (int i = 0; i < NUM_ADMINS; i++) {
        if (admins[i].usuario == usuario)
            return admins[i];
    }
    return Admin();
}

void CambiarEstadoCliente(Cliente clientes[], string usuario) {
    for (int i = 0; i < NUM_CLIENTES; i++) {
        if (clientes[i].usuario == usuario) {
            clientes[i].suspendido = !clientes[i].suspendido;
            break;
        }
    }
    ActualizarClientesCSV(clientes);
}

void CambiarEstadoEmpleado(Empleado empleados[], string usuario) {
    for (int i = 0; i < NUM_EMPLEADOS; i++) {
        if (empleados[i].usuario == usuario) {
            empleados[i].suspendido = !empleados[i].suspendido;
            break;
        }
    }
    ActualizarEmpleadosCSV(empleados);
}

void CambiarEstadoAdmin(Admin admins[], string usuario) {
    for (int i = 0; i < NUM_ADMINS; i++) {
        if (admins[i].usuario == usuario) {
            admins[i].suspendido = !admins[i].suspendido;
            break;
        }
    } 
    ActualizarAdminsCSV(admins);
}

bool EliminarCliente(Cliente clientes[], string usuario) {
    for (int i = 0; i < NUM_CLIENTES - 1; i++) {
        if (clientes[i].usuario == usuario) {
            for (int j = i; j < NUM_CLIENTES - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            break;
        }
    }
    clientes[NUM_CLIENTES - 1] = Cliente();
    ActualizarClientesCSV(clientes);
    return 0;
}

bool EliminarEmpleado(Empleado empleados[], string usuario) {
    for (int i = 0; i < NUM_EMPLEADOS - 1; i++) {
        if (empleados[i].usuario == usuario) {
            for (int j = i; j < NUM_EMPLEADOS - 1; j++) {
                empleados[j] = empleados[j + 1];
            }
            break;
        }
    }
    empleados[NUM_EMPLEADOS - 1] = Empleado();
    ActualizarEmpleadosCSV(empleados);
    return 0;
}

bool EliminarAdmin(Admin admins[], string usuario, string usuario_admin_activo) {
    if (usuario == usuario_admin_activo) return 1;

    for (int i = 0; i < NUM_ADMINS - 1; i++) {
        if (admins[i].usuario == usuario) {
            for (int j = i; j < NUM_ADMINS - 1; j++) {
                admins[j] = admins[j + 1];
            }
            break;
        }
    }
    admins[NUM_ADMINS - 1] = Admin();
    ActualizarAdminsCSV(admins);
    return 0;
}

void AnadirCliente(Cliente clientes[], Cliente cliente) {
    for (int i = 0; i < NUM_CLIENTES; i++) {
        if (clientes[i].usuario == "") {
            clientes[i].usuario = cliente.usuario;
            clientes[i].contrasena = cliente.contrasena;
            clientes[i].primer_nombre = cliente.primer_nombre;
            clientes[i].apellido = cliente.apellido;
            clientes[i].genero = cliente.genero;
            clientes[i].suspendido = false;
            break;
        }
    }
    ActualizarClientesCSV(clientes);
}

void AnadirEmpleado(Empleado empleados[], Empleado empleado) {
    for (int i = 0; i < NUM_EMPLEADOS; i++) {
        if (empleados[i].usuario == "") {
            empleados[i].usuario = empleado.usuario;
            empleados[i].contrasena = empleado.contrasena;
            empleados[i].primer_nombre = empleado.primer_nombre;
            empleados[i].apellido = empleado.apellido;
            empleados[i].genero = empleado.genero;
            empleados[i].suspendido = false;
            break;
        }
    }
    ActualizarEmpleadosCSV(empleados);
}

void AnadirAdmin(Admin admins[], Admin admin) {
    for (int i = 0; i < NUM_ADMINS; i++) {
        if (admins[i].usuario == "") {
            admins[i].usuario = admin.usuario;
            admins[i].contrasena = admin.contrasena;
            admins[i].primer_nombre = admin.primer_nombre;
            admins[i].apellido = admin.apellido;
            admins[i].genero = admin.genero;
            admins[i].suspendido = false;
            break;
        }
    }
    ActualizarAdminsCSV(admins);
}

void ActualizarAdminsCSV(Admin admins[]) {
    ifstream csv_ifstream(ADMINS_CSV);
    string encabezado = "";
    getline(csv_ifstream, encabezado);
    csv_ifstream.close();

    string del = "del ";
    string csv = ADMINS_CSV;
    for (auto &c : csv)
        if (c == '/') c = '\\';

    system((del + csv).c_str());

    ofstream csv_ofstream(ADMINS_CSV);
    csv_ofstream << encabezado << '\n';
    for (int i = 0; i < NUM_ADMINS; i++) {
        if (admins[i].usuario == "") return;
        csv_ofstream    << admins[i].usuario << ';'
                        << admins[i].contrasena << ';'
                        << admins[i].primer_nombre << ';'
                        << admins[i].apellido << ';'
                        << admins[i].genero << ';'
                        << (admins[i].suspendido ? "true" : "false") << '\n';
    }
}