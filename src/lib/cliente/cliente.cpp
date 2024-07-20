#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "cliente.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl;

Cliente::Cliente() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' '), libro(Libro())
{}

void ObtenerClientes(Cliente clientes[], Libro libros[], string csv) {
    ifstream csv_stream(csv);
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
                        clientes[i].libro = BuscarLibro(libros, campo);
                        if (clientes[i].libro.id == -1)
                            throw ("libro no hallado en `libros.csv`");
                        break;
                    default: throw ("demasiados campos hallados"); break;
                }
            } catch (const char* e) {
                cout << "ERROR AL OBTENER CLIENTE " << i + 1 << ": " << e << endl;
                return;
            } catch (std::invalid_argument e) {
                cout << "ERROR AL OBTENER CLIENTE " << i + 1 << ": " << e.what() << endl; 
                return;
            }
        } 
    }
}