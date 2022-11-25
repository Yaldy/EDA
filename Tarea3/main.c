#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"

#define TAM_TABLA 2000

extern int col1;
extern int col2;
extern int col3;

void main(int argc, char* argv[]){
	int m = TAM_TABLA; //tamaño de la tabla hash
	char* nchar = argv[1];// elementos en el mapa de ocupación (char)
	int n = atoi(argv[1]); // elementos en el mapa de ocupación (int)
	
	//crear tablas
	int T1[m];
	int T2[m];
	int T3[m];
	
	//inicializar tablas en -1 (vacias)
	int i=0;
	for(i;i<m;i++){ 
		T1[i]=-1;
		T2[i]=-1;
		T3[i]=-1;
	}
	
	//generar arreglo de números random
	srand (time(NULL));
	int nrandom[m];
	for(i=0; i<m; i++){
		nrandom[i]=rand() % 1000000;
	}
	
	
	//lenar tabla hash
	for(i=0; i<n; i++){
		hash_insert_3T(T1, T2, T3, nrandom[i], m); //particular, 3 tablas
	}
	
	//colisiones por cada tecnica
	//printf("COLISIONES: %d con 1, %d con 2 y %d con 3\n",col1,col2,col3);
	
	//archivos
	char name1[14+6];
	char name2[14+9];
	char name3[14+6];
	char cero[4];	
	
	switch(strlen(nchar)){
		case 1:
			strcpy(cero,  "000");
			sprintf(nchar,"%s",nchar);
			strcat(cero, nchar);
			break;
		case 2:
			strcpy(cero,  "00");
			sprintf(nchar,"%s",nchar);
			strcat(cero, nchar);
			break;
		case 3:
			strcpy(cero,  "0");
			sprintf(nchar,"%s",nchar);
			strcat(cero, nchar);
			break;
		default:
			strcpy(cero,  "");
			sprintf(nchar,"%s",nchar);
			strcat(cero, nchar);
			break;
	}
	
	sprintf(name1,"hash_linear_%s.txt",cero);
	sprintf(name2,"hash_quadratic_%s.txt",cero);
	sprintf(name3,"hash_double_%s.txt",cero);
	archivo(T1, name1);
	archivo(T2, name2);
	archivo(T3, name3);	
}

/*DUDAS
	en el primer task, hay que crear una función que agregue un elemento a 3 tablas distintas?
	no entiendo punto 4
	hay que crear siempre 2000 numeros random o basta con crear la catidad que se va a meter a la tabla?
	la llave es el dato? no tiene sentido:( 
*/

/* COMENTARIOS
	buscar parámetros de tecnicas para argumentar ren README
	para ver cuantos elementos meter en la tabla es interacción con el usuario
*/