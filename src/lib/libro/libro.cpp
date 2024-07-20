#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "libro.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl, std::stoi;

Libro::Libro() :
    id(-1), nombre(""), editorial(""), edicion(-1), cantidad(-1), precio(-1)
{}

void ObtenerLibros(Libro libros[], string csv) {
    ifstream csv_stream(csv);
    if (!csv_stream) {
        cout << "ERROR AL ABRIR `libros.csv`" << endl;
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
                    case 0: libros[i].id = stoi(campo); break;
                    case 1: libros[i].nombre = campo; break;
                    case 2: libros[i].cantidad = stoi(campo); break;
                    case 3: libros[i].editorial = campo; break;
                    case 4: libros[i].edicion = stoi(campo); break;
                    case 5: libros[i].precio = stoi(campo); break;
                    default: throw ("demasiados campos hallados"); break;
                }
            } catch (const char* e) {
                cout << "ERROR AL OBTENER LIBRO " << i + 1 << ": " << e << endl;
                throw;
            } catch (std::invalid_argument e) {
                cout << "ERROR AL OBTENER LIBRO " << i + 1 << ": " << e.what() << endl; 
                throw;
            }
        } 
    }
}

Libro BuscarLibro(Libro libros[], string nombre) {
    for (int i = 0; i < NUM_LIBROS; i++) {
        if (libros[i].nombre == nombre)
            return libros[i];
    }
    return Libro();
}