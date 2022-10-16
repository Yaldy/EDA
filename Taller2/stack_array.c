#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"


typedef int STACK; 
static STACK *stack = NULL;
int indice;

void STACKinit(int size){
	stack = (int*) malloc(size*sizeof(STACK));
	indice = 0;
}

/* STACKclean: vacia el stack liberando la memoria cuando sea necesario */
void STACKclean(){
	free(stack);
}

int STACKempty(){
	return(indice==0);
}


void STACKpush(int val,int max){

	if(STACKsize()<max){
		stack[indice]=val;
		indice++;
	}
	else{
		printf("ERROR: no queda espacio en el stack. Dato no se guardo en el stack.\n");
		//STACKclean();
		//exit(1);
	}
}

int STACKpop(){
	if(indice>0){
		indice--;
		return stack[indice];
	}
	else{
		printf("ERROR: no hay más contenido en el stack");
		//STACKclean();
		//exit(1);
	}
}

int STACKsize(){
	return indice;
} //tamaño actua

/* main para probar funciones
#define 
void main(int argc, char** argv){
	STACKinit(argc);
	int dato;
	int i = 1;
	for (i;i<argc;i++){
		dato = atoi(argv[i]);
		printf("dato es %d\n",dato);
		STACKpush(dato);
		printf("dato se guardo en  %d del stack\n",indice-1);
	}
	
	for (i=1;i<argc;i++){
		printf("del stack sale %d\n", STACKpop());	
	}

	STACKclean();
}
*/