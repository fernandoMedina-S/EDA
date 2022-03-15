#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#define PERMISO 777

#define SEPARADOR '|'

void capturar_usuario();
void leerUsuarios();
int menuPrincipal();
void selecPrincipal();


char nombre_archivo[20];
int contador;
int Archivo, tamanio=0;


int main()
{


    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    Archivo = open(nombre_archivo, O_RDWR | O_APPEND);

    if(Archivo == -1)
    {
    	printf("Creando nuevo archivo...\n");
        Archivo = creat(nombre_archivo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		//printf("Error! %d\n", errno);
        //perror("Program\n");
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

	lseek(Archivo, 0L, SEEK_END);


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


    write(Archivo, nombre, strlen(nombre));
    write(Archivo, "|", strlen("|"));
    write(Archivo, rfc, strlen(rfc));
    write(Archivo, "|", strlen("|"));
    write(Archivo, direccion, strlen(direccion));
    write(Archivo, "|", strlen("|"));
    write(Archivo, ciudad, strlen(ciudad));
    write(Archivo, "|", strlen("|"));
    write(Archivo, codigo_postal, strlen(codigo_postal));
    write(Archivo, "|", strlen("|"));
    write(Archivo, lesion, strlen(lesion));
    write(Archivo, "|", strlen("|"));
    write(Archivo, fisioterapeuta, strlen(fisioterapeuta));
    write(Archivo, "|", strlen("|"));


    system("pause");


}

void leerUsuarios()
{
	lseek(Archivo, 0, SEEK_SET);
    int i, aux=0;
    int sz;
	char auxC;
    char buffer[1024];

    sz = read(Archivo, buffer, 1024);

    for(i=0; i<strlen(buffer); i++){
    	auxC=buffer[i];

    	if(auxC == 124){
			printf("\n");
		}else if(auxC != 124){

			printf("%c", auxC);
		}
	}


    system("pause");

}
