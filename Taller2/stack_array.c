#include <stdio.h>

#define STACK_SIZE 20

typedef int STACK; 
static STACK *stack = NULL;
int indice;

void STACKinit(int size){
	stack = (*STACK) malloc(size*sizeof(STACK));
	indice = 0;
}


int STACKempty(){
	reeturn(indice==0);
}


void STACKpush(int val);{
	satck[indice]=val;
	indice++;
}

int STACKpop(){
	indice--;
	return stack[indice];
}

int STACKsize(){
	return indice;
} //tamaño actual


/* STACKclean: vacia el stack liberando la memoria cuando sea necesario */
void STACKclean(){
	
}