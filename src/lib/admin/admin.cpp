#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "admin.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl;

Admin::Admin() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' ')
{}

void ObtenerAdmins(Admin admins[], string csv) {
    ifstream csv_stream(csv);
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