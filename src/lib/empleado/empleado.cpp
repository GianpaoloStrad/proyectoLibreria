#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "empleado.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl, std::ofstream, std::cin;

Empleado::Empleado() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' '), suspendido(true)
{}

void ObtenerEmpleados(Empleado empleados[]) {
    ifstream csv_stream(EMPLEADOS_CSV);
    if (!csv_stream) {
        cout << "ERROR AL ABRIR `empleados.csv`" << endl;
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
                    case 0: empleados[i].usuario = campo; break;
                    case 1: empleados[i].contrasena = campo; break;
                    case 2: empleados[i].primer_nombre = campo; break;
                    case 3: empleados[i].apellido = campo; break;
                    case 4: 
                        if (toupper(campo[0]) == 'M' || toupper(campo[0] == 'F'))
                            empleados[i].genero = toupper(campo[0]);
                        else
                            throw ("genero invalido hallado");
                        break;
                    case 5:
                        switch (tolower(campo[0])) {
                            case 't': empleados[i].suspendido = true; break;
                            case 'f': empleados[i].suspendido = false; break;
                            default: throw("estado de suspension desconocido"); break;
                        }
                        break;
                    default: throw ("demasiados campos hallados"); break;
                }
            } catch (const char* e) {
                cout << "ERROR AL OBTENER EMPLEADO " << i + 1 << ": " << e << endl;
                throw;
            } catch (std::invalid_argument e) {
                cout << "ERROR AL OBTENER EMPLEADO " << i + 1 << ": " << e.what() << endl; 
                throw;
            }
        } 
    }
}

Empleado BuscarEmpleado(Empleado empleados[], string usuario) {
    for (int i = 0; i < NUM_EMPLEADOS; i++) {
        if (empleados[i].usuario == usuario)
            return empleados[i];
    }
    return Empleado();
}

void CambiarCantLibro(Libro libros[], Libro libro, int cantidad) {
    Libro &libro_ref = BuscarLibroRef(libros, libro.nombre);
    libro_ref.cantidad = cantidad;
    ActualizarLibrosCSV(libros);
}

void EliminarLibro(Libro libros[], Libro libro) {
    for (int i = 0; i < NUM_LIBROS - 1; i++) {
        if (libros[i].id == libro.id) {
            for (int j = i; j < NUM_LIBROS - 1; j++) {
                libros[j] = libros[j + 1];
            }
            break;
        }
    }
    libros[NUM_LIBROS - 1] = Libro();
    ActualizarLibrosCSV(libros);
}

void CrearLibro(Libro &libro) {
    string entrada_str = "";
    cin.ignore(1);

    cout << "Nombre: ";
    getline(cin, libro.nombre);
    cout << "Editorial: ";
    getline(cin, libro.editorial);
    cout << "Edicion: ";
    cin >> entrada_str;
    libro.edicion = stoi(entrada_str);
    cout << "Cantidad: ";
    cin >> entrada_str;
    libro.cantidad = stoi(entrada_str);
    cout << "Precio: ";
    cin >> entrada_str;
    libro.precio = stoi(entrada_str); 
}

void ModificarLibro(Libro libros[], Libro &libro) {
    CrearLibro(libro);
    for (int i = 0; i < NUM_LIBROS - 1; i++) {
        if (libros[i].id == libro.id) {
            libros[i] = libro;
            break;
        }
    }
    ActualizarLibrosCSV(libros);
}

void AnadirLibro(Libro libros[]) {
    Libro libro;
    CrearLibro(libro);
    for (int i = 0; i < NUM_LIBROS; i++) {
        if (libros[i].id == -1) {
            libro.id = i + 1;
            libros[i] = libro;
        }
    }
    ActualizarLibrosCSV(libros);
}

void ActualizarEmpleadosCSV(Empleado empleados[]) {
    ifstream csv_ifstream(EMPLEADOS_CSV);
    string encabezado = "";
    getline(csv_ifstream, encabezado);
    csv_ifstream.close();

    string del = "del ";
    string csv = EMPLEADOS_CSV;
    for (auto &c : csv)
        if (c == '/') c = '\\';

    system((del + csv).c_str());

    ofstream csv_ofstream(EMPLEADOS_CSV);
    csv_ofstream << encabezado << '\n';
    for (int i = 0; i < NUM_EMPLEADOS; i++) {
        if (empleados[i].usuario == "") return;
        csv_ofstream    << empleados[i].usuario << ';'
                        << empleados[i].contrasena << ';'
                        << empleados[i].primer_nombre << ';'
                        << empleados[i].apellido << ';'
                        << empleados[i].genero << ';'
                        << (empleados[i].suspendido ? "true" : "false") << '\n';
    }
}