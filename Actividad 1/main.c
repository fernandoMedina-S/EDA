#include <stdio.h>
#include <stdlib.h>

int main(){
	int blancos, otros, contador;
	int tam = 2;
	blancos = otros = contador = 0;
	char entrada;
	char *digitos;

	digitos = malloc(tam * sizeof(char));

       	
	while((entrada = getchar()) != EOF){
		if(entrada == 32 || entrada == 9 || entrada == 10){
			blancos++;
		}
		else if(entrada >= 48 && entrada <= 57){
			if(contador == tam){
				tam *= 2;
				digitos = realloc(digitos, tam * sizeof(char));
			}
			digitos[contador++] = entrada;
		}
		else{
			otros++;
		}
	}	
	printf("\nNumero de blancos: %d\n", blancos);
	printf("numero de digitos: %d\nDigitos ingresados: ", contador);
	for(int i=0; i<contador; i++){
		printf("%c", digitos[i]);
	}
	printf("\nOtros caracteres: %d\n", otros);
	return 0;
}
