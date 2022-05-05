#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define TAM_REG 64
char nombre_archivo[50];

int Archivo, Archivo_indices;

int menuPrincipal();
void selecPrincipal();
void capturar_corredor();
void leer_corredor();
void escribir_encabezado();
short leer_encabezado();
char* formatoTiempo(char* original);
void agrandar_lista();
void leer_indices_primarios();
char* formatoTiempoReves(char* original);
void imprimir_indices_primarios();
void ordenar_lista();
void escribir_indices_primarios();

typedef struct _indice_primario
{
    char num_participacion[5];
    short nrr;
    char tiempo[6];
} Indice_primario;

int tam = 2;
int contador_lista = 0;

Indice_primario* indices_primarios;

int main()
{

    char* extension = ".txt";
    char* lista_prefijo = "_indices.txt";

    indices_primarios = malloc(tam * sizeof(Indice_primario));

    printf("Ingresa el nombre del archivo a guardar:\n");
    gets(nombre_archivo);

    char* archivo_indices = malloc(strlen(nombre_archivo) + 1 + strlen(lista_prefijo));
    char* nombre_archivo_completo = malloc(strlen(nombre_archivo) + 1 + strlen(extension));

    strcpy(archivo_indices, nombre_archivo);
    strcat(archivo_indices, lista_prefijo);

    strcpy(nombre_archivo_completo, nombre_archivo);
    strcat(nombre_archivo_completo, extension);

    Archivo = open(nombre_archivo_completo, O_RDWR | O_APPEND);
    Archivo_indices = open(archivo_indices, O_RDWR | O_APPEND);
    leer_indices_primarios(); //Paso los indices del archivo a ram

    if(Archivo == -1)
    {
        printf("Creando nuevo archivo...\n");
        Archivo = creat(nombre_archivo_completo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        Archivo_indices = creat(archivo_indices, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        escribir_encabezado();
    }

    selecPrincipal();

    close(Archivo);


    return 0;
}

int menuPrincipal()
{

    system("cls");
    int opcion;

    printf("1.- Ingresar atleta\n");
    printf("2.- Ver lista\n");
    printf("3.- Mostrar indices primarios\n");
    printf("4.- Salir\n");

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
            imprimir_indices_primarios();
            ordenar_lista();
            break;
        case 4:
            escribir_indices_primarios();
            continuar=0;
            break;
        default:
            printf("Ingresa una opcion valida\n");
            break;
        }
    }
    while(continuar == 1);
}

void capturar_corredor()
{
    escribir_encabezado();
    lseek(Archivo, 0L, SEEK_END);
    short pos_guardada, pos_final;
    int i;

    char numero_participacion[4];
    char nombre_atleta[20];
    char direccion_atleta[10];
    char ciudad[10];
    char nacionalidad[10];
    char tiempo_clasificacion[7];
    char buffer[1024];
    char buffAux[10];
    for(i=0; i<1024; i++)
    {
        buffer[i] = NULL;
    }

    char tiempo_carrera_nuevo[7];


    printf("Ingrese la siguiente informacion requerida:\n");
    printf("Numero de participacion: ");
    gets(numero_participacion);
    strcat(buffer, numero_participacion);
    printf("buffer1: %s\n", buffer);

    printf("\nTiempo de clasificacion: ");
    gets(tiempo_clasificacion);
    strcat(buffer, formatoTiempo(tiempo_clasificacion));



    printf("\nNombre del atleta: ");
    gets(nombre_atleta);
    strcat(buffer, nombre_atleta);
    strcat(buffer, "|");


    printf("\nDireccion: ");
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

    printf("\nParticipacion en esta carrera: ");
    gets(tiempo_carrera_nuevo);


    printf("Buffer: %s\n", buffer);
    write(Archivo, buffer, 64);
    escribir_encabezado();
    pos_guardada = leer_encabezado();
    pos_guardada = ((pos_guardada -1) * TAM_REG) + 33;

    strcat(buffAux, formatoTiempo(tiempo_carrera_nuevo));
    printf("tiempo carrera: %d\n", pos_guardada);


    /*
    lseek(Archivo_indices, 0L, SEEK_END);
    write(Archivo_indices, numero_participacion, 4);
    write(Archivo_indices, &pos_guardada, sizeof(short));
    write(Archivo_indices, buffAux, strlen(buffAux));
    */

    Indice_primario *nuevo = (Indice_primario*)malloc(sizeof(Indice_primario));
    nuevo->nrr = pos_guardada;
    strcpy(nuevo->num_participacion, numero_participacion);
    strcpy(nuevo->tiempo, buffAux);

    if(contador_lista >= tam){
            agrandar_lista();
        }

    indices_primarios[contador_lista++] = *nuevo;

    system("pause");
}

void leer_corredor()
{
    lseek(Archivo, 32L, SEEK_SET);
    char buffer[1024];

    while((read(Archivo, buffer, 64)>=1))
    {
        printf("Linea de buffer: %s\n", buffer);
    }



    system("pause");
}

void escribir_encabezado()
{
    lseek(Archivo, 0L, SEEK_SET);
    short registros=0;
    char relleno[31];
    int i;

    for(i=0; i<30; i++)
    {
        relleno[i] = ' ';
    }


    char* buffer[65];

    lseek(Archivo, 32L, SEEK_SET);
    while((read(Archivo, buffer, 64)>=1))
    {
        registros++;
    }


    lseek(Archivo, 0L, SEEK_SET);

    //Escribirlo en archivo
    //printf("Registros para guardar en encabezado: %d\n", registros);
    write(Archivo, &registros, sizeof(registros));
    write(Archivo, relleno, 30);

}

short leer_encabezado()
{
    lseek(Archivo, 0, SEEK_SET);
    short registros;

    read(Archivo, &registros, 2);

    return registros;
}

char* formatoTiempo(char* original)
{
    char* formateada= malloc(6 * sizeof(char));;


    //9:10:22
    formateada[0] = original[0];
    formateada[1] = original[2];
    formateada[2] = original[3];
    formateada[3] = original[5];
    formateada[4] = original[6];
    formateada[5] = '\0';



    return formateada;
}

char* formatoTiempoReves(char* original)
{
    char* formateada= malloc(8 * sizeof(char));;


    //91022
    formateada[0] = original[0];
    formateada[1] = ':';
    formateada[2] = original[1];
    formateada[3] = original[2];
    formateada[4] = ':';
    formateada[5] = original[3];
    formateada[6] = original[4];
    formateada[7] = '\0';

    return formateada;
}

void agrandar_lista()
{
    tam = 2 * tam;
    indices_primarios = realloc(indices_primarios, tam * sizeof(Indice_primario));
}

void leer_indices_primarios()
{

    char numero_participacion[5];
    char buffer[1024];
    short nrr;
    char tiempo_carrera[6];
    char buffAux[10];
    int i;

    lseek(Archivo_indices, 0, SEEK_SET);

    while((read(Archivo_indices, numero_participacion, 4)) > 0)
    {
        numero_participacion[4] = '\0';

        read(Archivo_indices, &nrr, sizeof(short));

        read(Archivo_indices, tiempo_carrera, 5);
        tiempo_carrera[5] = '\0';

        Indice_primario *nuevo = (Indice_primario*)malloc(sizeof(Indice_primario));

        strcat(buffAux, formatoTiempoReves(tiempo_carrera));

        nuevo->nrr = nrr;
        strcpy(nuevo->num_participacion, numero_participacion);
        strcpy(nuevo->tiempo, tiempo_carrera);

        buffAux[0] = '\0';

        if(contador_lista >= tam){
            agrandar_lista();
        }
        indices_primarios[contador_lista++] = *nuevo;

    }
}


void imprimir_indices_primarios(){
    int i;
    for(i=0; i<contador_lista; i++){
        printf("Registro %d:\n", i+1);
        printf("Ubicacion archivo: %d\n", indices_primarios[i].nrr);
        printf("Tiempo de carrera: %s\n", formatoTiempoReves(indices_primarios[i].tiempo));
        printf("Numero de participacion: %s\n\n", indices_primarios[i].num_participacion);
    }
    system("pause");
}

void ordenar_lista(){
    Indice_primario aux;
    int i, j;
    for(i=0; i<contador_lista; i++){
        for(j=0; j<contador_lista-1; j++){
            if(strtol(indices_primarios[j].tiempo, NULL, 10) > strtol(indices_primarios[j+1].tiempo, NULL, 10)){
                aux = indices_primarios[j];
                indices_primarios[j] = indices_primarios[j+1];
                indices_primarios[j+1] = aux;
            }
        }
    }
}

void escribir_indices_primarios(){
    int i;

    lseek(Archivo_indices, 0L, SEEK_END);
    for(i=0; i<contador_lista; i++){
        write(Archivo_indices, indices_primarios[i].num_participacion, 4);
        write(Archivo_indices, &indices_primarios[i].nrr, sizeof(short));
        write(Archivo_indices, indices_primarios[i].tiempo, strlen(indices_primarios[i].tiempo));
    }
}
