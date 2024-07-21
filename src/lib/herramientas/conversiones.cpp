#include "conversiones.h"
#include "../definiciones.h"

string CodUsuarioAString(int codigo) {
    switch (codigo) {
        case CLT: return "cliente"; break;
        case EMP: return "empleado"; break;
        case ADM: return "admin"; break;
        default: throw("CodUsuarioAString: codigo de usuario invalido"); break;
    }
}