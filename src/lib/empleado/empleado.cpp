#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "empleado.h"

using   std::string, std::ifstream, std::getline, std::stringstream,
        std::cout, std::endl;

Empleado::Empleado() :
    usuario(""), contrasena(""), primer_nombre(""), apellido(""), genero(' ')
{}

void ObtenerEmpleados(Empleado empleados[], string csv) {
    ifstream csv_stream(csv);
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