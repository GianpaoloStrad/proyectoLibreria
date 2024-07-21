#pragma once

#define LOG 0

#define LOG_CLT 111
#define LOG_EMP 222
#define LOG_ADM 333

#define CLT 1
#define EMP 2
#define ADM 3

#define CLT_SAL 4
#define CLT_BSC 5
#define CLT_DVL 6

#define CLT_BSC_SAL 7
#define CLT_BSC_RET 8
#define CLT_BSC_CMP 9

#define EMP_BSC 30
#define EMP_AND 31

#define EMP_BSC_SAL 32
#define EMP_BSC_ELI 33
#define EMP_BSC_MOD 34

#define LIB_BSC_1 500
#define LIB_BSC_2 501

#define ERR_LOG 999

extern const char* LIBROS_CSV;
extern const char* CLIENTES_CSV;
extern const char* EMPLEADOS_CSV;
extern const char* ADMINS_CSV;