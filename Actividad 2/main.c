#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define SEPARADOR '|'

void capturar_usuario();
void leerUsuarios();
int menuPrincipal();
void selecPrincipal();


char nombre_archivo[20];
FILE* archivo;
int contador;
int Archivo, tamanio;


int main()
{


    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    Archivo = open(nombre_archivo, O_RDWR);

    if(Archivo == -1)
    {
        printf("Error! %d", errno);
        perror("Program");
        exit(1);
    }

    selecPrincipal();

    close(Archivo);
    return 0;
}




int menuPrincipal()
{

    system("cls");
    int opcion;

    printf("1.- Ingresar usuario\n");
    printf("2.- Mostrar usuarios\n");
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
            capturar_usuario();
            break;
        case 2:
            leerUsuarios();
            break;
        case 3:
            continuar=0;
            fprintf(archivo, "\n");
            break;
        default:
            printf("Ingresa una opcion valida\n");
            break;
        }
    }
    while(continuar == 1);
}

void capturar_usuario()
{
    char buff[1024];
    int num;
    char nombre[30];
    char rfc[14];
    char direccion[30];
    char ciudad[20];
    char codigo_postal[10];
    char lesion[35];
    char fisioterapeuta[30];




    printf("Ingresa el nombre del cliente:\n");
    gets(nombre);

    printf("Ingresa el RFC:\n");
    gets(rfc);

    printf("Ingresa direccioin:\n");
    gets(direccion);

    printf("Ingresa ciudad:\n");
    gets(ciudad);

    printf("Ingresa codigo postal:\n");
    gets(codigo_postal);

    printf("Ingresa lesion:\n");
    gets(lesion);

    printf("Ingresa fisioterapeuta encargado:\n");
    gets(fisioterapeuta);


    tamanio = write(Archivo, nombre, strlen(nombre));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, rfc, strlen(rfc));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, direccion, strlen(direccion));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, ciudad, strlen(ciudad));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, codigo_postal, strlen(codigo_postal));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, lesion, strlen(lesion));
    tamanio+= write(Archivo, "|", strlen("|"));
    tamanio+= write(Archivo, fisioterapeuta, strlen(fisioterapeuta));
    tamanio+= write(Archivo, "|", strlen("|"));


    system("pause");


}

void leerUsuarios()
{

    int i, aux=0;
    int sz;

    char buffer[1024];

    sz = read(Archivo, buffer, 1024);
    printf("%d", sz);


    system("pause");

}
