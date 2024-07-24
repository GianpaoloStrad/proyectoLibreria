#pragma once

// Login
#define LOG 0

// Login como cliente
#define LOG_CLT 111
// Login como empleado
#define LOG_EMP 222
// Login como admin
#define LOG_ADM 333

// Codigos para definir el tipo de usuario
#define CLT 1
#define EMP 2
#define ADM 3

// Salida del cliente
#define CLT_SAL 4
// Cliente - Libro
#define CLT_LIB 5
// Cliente - Devolver un libro
#define CLT_DVL 6

// Cliente - Salir del libro
#define CLT_LIB_SAL 7
// Cliente - Retirar libro
#define CLT_LIB_RET 8
// Cliente - Comprar libro
#define CLT_LIB_CMP 9

// Empleado - Libro
#define EMP_LIB 30
// Empleado - Anadir libro
#define EMP_AND 31

// Empleado - Salir del libro
#define EMP_LIB_SAL 32
// Empleado - Eliminar libro
#define EMP_LIB_ELI 33
// Empleado - Modificar libro
#define EMP_LIB_MOD 34

// Admin - Crear cliente
#define ADM_CLT 60
// Admin - Crear empleado
#define ADM_EMP 61
// Admin - Crear administrador
#define ADM_ADM 62

// Admin - Suspender usuario
#define ADM_USR_SUS 63
// Admin - Eliminar usuario
#define ADM_USR_ELI 64

// Admin - Anadir usuario 1
#define ADM_USR_AND_1 65
// Admin - Anadir usuario 2
#define ADM_USR_AND_2 66

// Buscar un libro 1
#define LIB_BSC_1 500
// Buscar un libro 2
#define LIB_BSC_2 501

// Buscar un usuario 1
#define USR_BSC_1 510
// Buscar un usuario 2
#define USR_BSC_2 51

// Error - Login: Usuario no encontrado
#define ERR_LOG_NEN 900
// Error - Login: Usuario suspendido
#define ERR_LOG_SUS 901
// Error - Usuario no encontrado
#define ERR_USR 902

extern const char* LIBROS_CSV;
extern const char* CLIENTES_CSV;
extern const char* EMPLEADOS_CSV;
extern const char* ADMINS_CSV;