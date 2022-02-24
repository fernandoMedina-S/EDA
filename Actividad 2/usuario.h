#include <stdlib.h>

typedef struct Cliente{
    char nombre[30];
    char rfc[14];
    char* direccion;
    char* ciudad;
    char* estado;
    char* codigo_postal;
    char* lesion;
    char* fisioterapeuta;
}Cliente;
