#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//#define STACK_MAX 20

typedef struct stacknode{
	int val;
	struct stacknode *next;
}STACK;

static STACK *head = NULL;

int nelem=0;

int STACKsize(){
	return(nelem);
}

void STACKclean(){
	int con=0;
	STACK *aux=NULL;
	//printf("%d\n",head->next);
	if(STACKsize()>0){
		while(head!=NULL){
			con++;
			printf("%d\n",con);
			aux=head->next;
			free(head);
			head=aux;
		}
	}
	
	//printf("Stack eliminado.\n");	
}


void STACKinit(int size){
	if(head!=NULL){
		STACKclean(head);
	}
		
}

int STACKempty(){
	return(head==NULL);
}

void STACKpush(int val,int max){
	if(STACKsize()<max){
		STACK* newNode =  malloc(sizeof(STACK));
		newNode -> val = val;
		newNode -> next = head;
		head = newNode;
		nelem++;
	}
	else{
		printf("ERROR: no queda espacio en el stack. Dato no se guardo.\n");
	}
}

int STACKpop(){
	if(STACKsize()>0){
		int res = head -> val;
		STACK *temp=head;
		head = head -> next;
		free(temp);
		nelem--;
		return res;
	}
	else{
		printf("ERROR: no hay más contenido en el stack\n");
		return 0;
	}
}


/*main para probar implementación
void main(int argc, char** argv){
	STACKinit(argc);
	int dato;
	int i = 1;
	for (i;i<argc;i++){
		dato = atoi(argv[i]);
		//printf("dato es %d\n",dato);
		STACKpush(dato,STACK_MAX);
		printf("el dato %d se guardo en espacio %d del stack\n",dato,nelem-1);
	}
	
	for (i=1;i<argc-2;i++){
		printf("del stack sale %d\n", STACKpop());	
	}
	printf("se va a limpiar el stack\n");
	STACKclean();
}*/