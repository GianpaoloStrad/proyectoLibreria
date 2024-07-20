#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "libro.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl, std::stoi, std::ofstream;

Libro::Libro() :
    id(-1), nombre(""), editorial(""), edicion(-1), cantidad(-1), precio(-1)
{}

void ObtenerLibros(Libro libros[]) {
    ifstream csv_stream(LIBROS_CSV);
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
        cout << libros[i].nombre << endl;
        if (libros[i].nombre == nombre)
            return libros[i];
    }
    return Libro();
}

Libro& BuscarLibroRef(Libro libros[], string nombre) {
    for (int i = 0; i < NUM_LIBROS; i++) {
        cout << libros[i].nombre << endl;
        if (libros[i].nombre == nombre)
            return libros[i];
    }
    throw("BuscarLibroRef: el libro no existe");
}

void ActualizarLibrosCSV(Libro libros[]) {
    ifstream csv_ifstream(LIBROS_CSV);
    string encabezado = "";
    getline(csv_ifstream, encabezado);
    csv_ifstream.close();

    string del = "del ";
    string csv = LIBROS_CSV;
    for (auto &c : csv)
        if (c == '/') c = '\\';

    system((del + csv).c_str());

    ofstream csv_ofstream(LIBROS_CSV);
    csv_ofstream << encabezado << '\n';
    for (int i = 0; i < NUM_LIBROS; i++) {
        csv_ofstream    << libros[i].id << ';'
                        << libros[i].nombre << ';'
                        << libros[i].cantidad << ';'
                        << libros[i].editorial << ';'
                        << libros[i].edicion << ';'
                        << libros[i].precio << '\n';
    }
}