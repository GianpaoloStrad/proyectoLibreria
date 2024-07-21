#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "cliente.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl, std::ofstream;

Cliente::Cliente() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' '), libro(Libro()), suspendido(true)
{}

void ObtenerClientes(Cliente clientes[], Libro libros[]) {
    ifstream csv_stream(CLIENTES_CSV);
    if (!csv_stream) {
        cout << "ERROR AL ABRIR `clientes.csv`" << endl;
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
                    case 0: clientes[i].usuario = campo; break;
                    case 1: clientes[i].contrasena = campo; break;
                    case 2: clientes[i].primer_nombre = campo; break;
                    case 3: clientes[i].apellido = campo; break;
                    case 4: 
                        if (toupper(campo[0]) == 'M' || toupper(campo[0] == 'F'))
                            clientes[i].genero = toupper(campo[0]);
                        else
                            throw ("genero invalido hallado");
                        break;
                    case 5:
                        if (campo != "") {
                            clientes[i].libro = BuscarLibro(libros, campo);
                            if (clientes[i].libro.id == -1)
                                throw ("libro no hallado en `libros.csv`");
                        }
                        break;
                    case 6:
                        switch (tolower(campo[0])) {
                            case 't': clientes[i].suspendido = true; break;
                            case 'f': clientes[i].suspendido = false; break;
                            default: throw("estado de suspension desconocido"); break;
                        }
                        break;
                    default: throw ("demasiados campos hallados"); break;
                }
            } catch (const char* e) {
                cout << "ERROR AL OBTENER CLIENTE " << i + 1 << ": " << e << endl;
                throw;
            } catch (std::invalid_argument e) {
                cout << "ERROR AL OBTENER CLIENTE " << i + 1 << ": " << e.what() << endl; 
                throw;
            }
        } 
    }
}

Cliente BuscarCliente(Cliente clientes[], string usuario) {
    for (int i = 0; i < NUM_CLIENTES; i++) {
        if (clientes[i].usuario == usuario)
            return clientes[i];
    }
    return Cliente();
}

Cliente& BuscarClienteRef(Cliente clientes[], string usuario) {
    for (int i = 0; i < NUM_CLIENTES; i++) {
        if (clientes[i].usuario == usuario)
            return clientes[i];
    }
    throw("BuscarClienteRef: el cliente no existe");
}

void RetirarLibro(Cliente clientes[], Libro libros[], Cliente &cliente, Libro libro) {
    CambiarCantLibro(libros, libro, libro.cantidad - 1);
    Cliente &cliente_ref = BuscarClienteRef(clientes, cliente.usuario);
    cliente_ref.libro = libro;
    cliente.libro = libro;
    ActualizarClientesCSV(clientes);
}

void ComprarLibro(Cliente clientes[], Libro libros[], Cliente cliente, Libro libro) {
    CambiarCantLibro(libros, libro, libro.cantidad - 1);
}

void DevolverLibro(Cliente clientes[], Libro libros[], Cliente &cliente) {
    Libro &libro = BuscarLibroRef(libros, cliente.libro.nombre);
    CambiarCantLibro(libros, libro, libro.cantidad + 1);
    Cliente &cliente_ref = BuscarClienteRef(clientes, cliente.usuario);
    cliente_ref.libro = Libro();
    cliente.libro = Libro();
    ActualizarClientesCSV(clientes);
}

void ActualizarClientesCSV(Cliente clientes[]) {
    ifstream csv_ifstream(CLIENTES_CSV);
    string encabezado = "";
    getline(csv_ifstream, encabezado);
    csv_ifstream.close();

    string del = "del ";
    string csv = CLIENTES_CSV;
    for (auto &c : csv)
        if (c == '/') c = '\\';

    system((del + csv).c_str());

    ofstream csv_ofstream(CLIENTES_CSV);
    csv_ofstream << encabezado << '\n';
    for (int i = 0; i < NUM_CLIENTES; i++) {
        if (clientes[i].usuario == "") return;
        csv_ofstream    << clientes[i].usuario << ';'
                        << clientes[i].contrasena << ';'
                        << clientes[i].primer_nombre << ';'
                        << clientes[i].apellido << ';'
                        << clientes[i].genero << ';'
                        << clientes[i].libro.nombre << ';'
                        << (clientes[i].suspendido ? "true" : "false") << '\n';
    }
}