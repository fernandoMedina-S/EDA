#include <stdlib.h>
#include <stdio.h>
#define SEPARADOR '|'

void capturar_usuario();
void leerUsuarios();
int menuPrincipal();
void selecPrincipal();


char nombre_archivo[20];
FILE* archivo;
int contador;


int main()
{


    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    archivo = fopen(nombre_archivo, "a+");

    if(archivo == NULL)
    {
        printf("Error!");
        exit(1);
    }

    selecPrincipal();

    fclose(archivo);
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


    fprintf(archivo, "%s|%s|%s|%s|%s|%s|%s|\n", nombre, rfc, direccion, ciudad, codigo_postal, lesion, fisioterapeuta);
    system("pause");


}

void leerUsuarios(){
    fseek(archivo, 0, 0);
    int i, aux=0;
    char nombre[30];
    char rfc[14];
    char direccion[30];
    char ciudad[20];
    char codigo_postal[10];
    char lesion[35];
    char fisioterapeuta[30];

    char buffer[1024];
    //|| buffer[i]!='\0' || buffer[i]!='\n'
    while((fgets(buffer, 1024, archivo))){





        if(buffer[0]==' '){
            break;
        }
        for(i=0; buffer[i]!=SEPARADOR; i++){
            nombre[i] = buffer[i];
        }
        nombre[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            rfc[i] = buffer[i];
        }
        rfc[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            direccion[i] = buffer[i];
        }
        direccion[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            ciudad[i] = buffer[i];
        }
        ciudad[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            codigo_postal[i] = buffer[i];
        }
        codigo_postal[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            lesion[i] = buffer[i];
        }
        lesion[i] = '\0';
        aux=i;

        for(i=0; buffer[i]!=SEPARADOR; i++){
            fisioterapeuta[i] = buffer[i];
        }
        fisioterapeuta[i] = '\0';
        aux=i;

        printf("Nombre: %s\n", nombre);
        printf("RFC: %s\n", rfc);
        printf("Direccion: %s\n", direccion);
        printf("Ciudad: %s\n", ciudad);
        printf("Codigo postal: %s\n", codigo_postal);
        printf("Lesion: %s\n", lesion);
        printf("Fisioterapeuta: %s\n", fisioterapeuta);
        printf("\n==========================\n");
        system("pause");
    }

}
