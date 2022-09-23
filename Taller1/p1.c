#include <stdio.h>
#include <stdlib.h>

int regla30(int ptrio){
	//int triof[3] = {*(ptrio),*(ptrio+1),*(ptrio+2)};
	int d = 0;
	switch(ptrio){
		case 0:
			d = 0;
			break;
      
		case 1:
			d = 1;
			break;
      
		case 10:
			d = 1;
			break;
		
		case 11:
			d = 1;
			break;
      
		case 100:
			d = 1;
			break;
      
		case 101:
			d = 0;
			break;
      
		case 110:
			d = 0;
			break;
      
		case 111:
			d = 0;
			break;
	}
	
	return d;
}
   

void main(int argc, char *argv[]){
	int nvert = atoi(argv[1]); //cantidad de cuadrdaditos hacia abajo
	printf("%d\n",nvert);
	int nhoriz = nvert*2+1; //cantidad de columnas (cuadraditos horizontales)
	printf("%d\n\n",nhoriz);
	int medio=nvert; //posición cuadradito del medio
	int fila[nhoriz]; //definicion del arreglo horizontal
	int fila_sgt[nhoriz];
 
	// Loop para inicializar arreglo en 0
	int i = 0;
	for(i=0; i<nhoriz; i++){
		fila[i]=0;
		fila_sgt[i]=0;
	}
	fila[medio] = 1;
	
	printf("Construyendo automata regla 30, con %d lineas:\n", nvert);
 
	
	//loop para imprimir la primera columna (sin primer y ultimo bloque)
	for (i=1; i<(nhoriz-1); i++){
		if(fila[i]){
			printf("x");
		}
		else{
			printf(" ");
		}
	}
	printf("\n");
  
	//
	int j = 0;
	for(j;j<nvert-1;j++){
		// loop que recorre el arreglo horizontal
		for(i=1; i<(nhoriz-1); i++){ 
			int trio = fila[i-1]*100+fila[i]*10+fila[i+1]; // abc -> d (guia)
			int d = regla30(trio);
			fila_sgt[i]=d;		   
		}
		
		//sobre escribe fila 
		for(i=0; i<nhoriz; i++){
			fila[i]=fila_sgt[i];
		}
		
		//imprimir filas
		for (i=1; i<(nhoriz-1); i++){
			if(fila[i]){
				printf("x");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
  }
}
