#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

int menuPrincipal();
void selecPrincipal();
void capturar_cancion();

typedef struct _Cancion
{
    char titulo[50];
    char artista[50];
    char autor[50];
    char distribuidora[30];
    char genero[20];
    char anio[10];
    char premios[5];
} Cancion;

int main()
{

    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    Archivo = open(nombre_archivo, O_RDWR | O_APPEND);

    if(Archivo == -1)
    {
        printf("Creando nuevo archivo...\n");
        Archivo = creat(nombre_archivo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        printf("Error! %d\n", errno);
        perror("Program\n");
        system("pause");
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

void capturar_cancion(){
    Cancion nueva;

    printf("Nombre de la cancion:\n");
    gets(nueva.titulo);

    printf("Artista de la cancion:\n");
    gets(nueva.artista);

    printf("Autor de la cancion:\n");
    gets(nueva.autor);

    printf("Distribuidora de la cancion:\n");
    gets(nueva.distribuidora);

    printf("Genero de la cancion:\n");
    gets(nueva.genero);

    printf("Anio de la cancion:\n");
    gets(nueva.anio);

    printf("Numero de premios de la cancion:\n");
    gets(nueva.premios);
}
