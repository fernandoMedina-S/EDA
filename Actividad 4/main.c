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
void capturar_corredor();
void leer_corredor();



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
            capturar_corredor();
            break;
        case 2:
            leer_corredor();
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

void capturar_corredor(){

    lseek(Archivo, 0L, SEEK_END);

    char numero_participacion[4];
    char nombre_atleta[10];
    char direccion_atleta[10];
    char ciudad[10];
    char nacionalidad[10];
    char tiempo_clasificacion[10];
    char buffer[1024];


    printf("Ingrese la siguiente informacion requerida:\n");
    printf("Numero de participacion: ");
    gets(numero_participacion);
    strcat(buffer, numero_participacion);
    strcat(buffer, "|");

    printf("\nNombre del atleta: ");
    gets(nombre_atleta);
    strcat(buffer, nombre_atleta);
    strcat(buffer, "|");

    printf("\Direccion: ");
    gets(direccion_atleta);
    strcat(buffer, direccion_atleta);
    strcat(buffer, "|");

    printf("\nCiudad: ");
    gets(ciudad);
    strcat(buffer, ciudad);
    strcat(buffer, "|");

    printf("\nNacionalidad: ");
    gets(nacionalidad);
    strcat(buffer, nacionalidad);
    strcat(buffer, "|");

    printf("\nTiempo de clasificacion: ");
    gets(tiempo_clasificacion);
    strcat(buffer, tiempo_clasificacion);
    strcat(buffer, "|");


    write(Archivo, buffer, 64);
    printf("\nBuffer: %s\n", buffer);
    system("pause");
}

void leer_corredor(){
    lseek(Archivo, 0, SEEK_SET);
    char buffer[1024];

    while((read(Archivo, buffer, 64)>=1)){
        printf("Linea de buffer: %s\n", buffer);
    }

    system("pause");
}
