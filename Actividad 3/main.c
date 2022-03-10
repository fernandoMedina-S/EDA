#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

int menuPrincipal();
void selecPrincipal();
void capturar_cancion();
void leer_cancion();


char nombre_archivo[50];
int Archivo;

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
            capturar_cancion();
            break;
        case 2:
            leer_cancion();
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

void capturar_cancion()
{

    lseek(Archivo, 0L, SEEK_END);

    Cancion nueva;
    char buffer[1024];
    int i, total=0, j, tam_buffer;
    char char_buffer[5];

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

    total = strlen(nueva.titulo) + strlen(nueva.artista) + strlen(nueva.autor) + strlen(nueva.distribuidora) + strlen(nueva.genero) + strlen(nueva.anio) + strlen(nueva.premios);



    for(j=0, i=0; j<strlen(nueva.titulo); j++, i++)
    {
        buffer[i] = nueva.titulo[j];
    }

    buffer[i] = '|';
    i++;

    for(j=0; j<strlen(nueva.artista); j++, i++)
    {
        buffer[i] = nueva.artista[j];
    }
    buffer[i] = '|';
    i++;
    for(j=0; j<strlen(nueva.autor); j++, i++)
    {
        buffer[i] = nueva.autor[j];
    }
    buffer[i] = '|';
    i++;
    for(j=0; j<strlen(nueva.distribuidora); j++, i++)
    {
        buffer[i] = nueva.distribuidora[j];
    }
    buffer[i] = '|';
    i++;
    for(j=0; j<strlen(nueva.genero); j++, i++)
    {
        buffer[i] = nueva.genero[j];
    }
    buffer[i] = '|';
    i++;
    for(j=0; j<strlen(nueva.anio); j++, i++)
    {
        buffer[i] = nueva.anio[j];
    }
    buffer[i] = '|';
    i++;
    for(j=0; j<strlen(nueva.premios); j++, i++)
    {
        buffer[i] = nueva.premios[j];
    }
    buffer[i] = '|';
    i++;
    buffer[i] = '\0';

    tam_buffer = strlen(buffer);

    sprintf(char_buffer, "%d", tam_buffer);

    write(Archivo, char_buffer, strlen(char_buffer));
    write(Archivo, buffer, tam_buffer);
    printf("Cancion agregada\n");


    system("pause");
}

void leer_cancion()
{
    lseek(Archivo, 0, SEEK_SET);
    char buffer[1024];
    char tam_buffer[3];
    char auxC;
    int tam_buffer_int, leido=1, i;



    while((read(Archivo, tam_buffer, 2))>=1)
    {
        printf("\nCancion numero %d\n", leido++);
        tam_buffer_int = atoi(tam_buffer);

        char registro[tam_buffer_int+1];

        read(Archivo, registro, tam_buffer_int);
        registro[tam_buffer_int] = '\0';


        for(i=0; i<strlen(registro); i++)
        {
            auxC=registro[i];

            if(auxC == 124)
            {
                printf("\n");
            }
            else if(auxC != 124)
            {

                printf("%c", auxC);
            }
        }

    }

    system("pause");

}
