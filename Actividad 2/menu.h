#include <stdio.h>
#include <stdlib.h>

void capturar_usuario();


int menuPrincipal(){


    int opcion;

    printf("1.- Ingresar usuario\n");
    printf("2.- Mostrar usuarios\n");
    printf("3.- Salir\n");

    scanf("%d", &opcion);
    fflush(stdin);
    return opcion;
}

void selecPrincipal(){

    int continuar = 1;
    do{
        switch(menuPrincipal()){
            case 1:
                capturar_usuario();
                break;
            case 3:
                continuar=0;
                break;
            default:
                printf("Ingresa una opcion valida\n");
                break;
        }
    }while(continuar == 1);
}

void capturar_usuario(){
    char nombre_archivo[20];
    FILE* archivo;
    int num;
    char nombre[30];
    char rfc[14];
    char direccion[30];
    char ciudad[20];
    char codigo_postal[10];
    char lesion[35];
    char fisioterapeuta[30];


    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    archivo = fopen(nombre_archivo, "w+");

    if(archivo == NULL)
   {
      printf("Error!");
      exit(1);
   }

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



}
