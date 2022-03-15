#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

char nombre_archivo[50];
int Archivo, Archivo_indices;

int menuPrincipal();
void selecPrincipal();



int main(){

    char* extension = ".txt";
    char* lista_prefijo = "_indices.txt";

    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    char* archivo_indices = malloc(strlen(nombre_archivo) + 1 + strlen(lista_prefijo));
    char* nombre_archivo_completo = malloc(strlen(nombre_archivo) + 1 + strlen(extension));

    strcpy(archivo_indices, nombre_archivo);
    strcat(archivo_indices, lista_prefijo);

    strcpy(nombre_archivo_completo, nombre_archivo);
    strcat(nombre_archivo_completo, extension);

    printf("%s\n", archivo_indices);
    system("pause");

    Archivo = open(nombre_archivo_completo, O_RDWR | O_APPEND);
    Archivo_indices = open(archivo_indices, O_RDWR | O_APPEND);

    if(Archivo == -1)
    {
        printf("Creando nuevo archivo...\n");
        Archivo = creat(nombre_archivo_completo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        Archivo_indices = creat(archivo_indices, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

    selecPrincipal();

    close(Archivo);


    return 0;
}

int menuPrincipal()
{

    system("cls");
    int opcion;

    printf("1.- Ingresar cancion\n");
    printf("2.- Ver lista\n");
    printf("3.- Salir\n");

    scanf("%d", &opcion);
    fflush(stdin);
    return opcion;
}

void selecPrincipal()
{

    int continuar = 1;
    do
    {
        switch(menuPrincipal())
        {
        case 1:

            break;
        case 2:

            break;
        case 3:
            continuar=0;
            break;
        default:
            printf("Ingresa una opcion valida\n");
            break;
        }
    }
    while(continuar == 1);
}
