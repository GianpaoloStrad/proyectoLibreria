#pragma once

#define LOG 0

#define LOG_CLT 111
#define LOG_EMP 222
#define LOG_ADM 333

#define CLT 1
#define EMP 2
#define ADM 3

#define CLT_SAL 4
#define CLT_LIB 5
#define CLT_DVL 6

#define CLT_LIB_SAL 7
#define CLT_LIB_RET 8
#define CLT_LIB_CMP 9

#define EMP_LIB 30
#define EMP_AND 31

#define EMP_LIB_SAL 32
#define EMP_LIB_ELI 33
#define EMP_LIB_MOD 34

#define ADM_CLT 60
#define ADM_EMP 61
#define ADM_ADM 62

#define ADM_USR_SUS 63
#define ADM_USR_ELI 64

#define ADM_USR_AND_1 65
#define ADM_USR_AND_2 66

#define LIB_BSC_1 500
#define LIB_BSC_2 501

#define USR_BSC_1 510
#define USR_BSC_2 51

#define ERR_LOG_NEN 900
#define ERR_LOG_SUS 901
#define ERR_USR 902

extern const char* LIBROS_CSV;
extern const char* CLIENTES_CSV;
extern const char* EMPLEADOS_CSV;
extern const char* ADMINS_CSV;