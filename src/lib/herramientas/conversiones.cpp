#include "conversiones.h"
#include "../definiciones.h"

string CodUsuarioAString(int codigo) {
    switch (codigo) {
        case U_CLT: return "cliente"; break;
        case U_EMP: return "empleado"; break;
        case U_ADM: return "admin"; break;
        default: throw("CodUsuarioAString: codigo de usuario invalido"); break;
    }
}