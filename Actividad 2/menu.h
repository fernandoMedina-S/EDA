#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

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
