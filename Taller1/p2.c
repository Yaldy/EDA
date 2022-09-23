
#include <stdio.h>
#include <stdlib.h>

// Función quqe codifica las reglas
int reglaXX(int ptrio, int* pbin){
	//int triof[3] = {*(ptrio),*(ptrio+1),*(ptrio+2)};
	int d = 0;
	switch(ptrio){
		case 0:
			d = *(pbin+7);
			break;
      
		case 1:
			d = *(pbin+6);
			break;
      
		case 10:
			d = *(pbin+5);
			break;
		
    case 11:
			d = *(pbin+4);
			break;
      
		case 100:
			d = *(pbin+3);
			break;
      
		case 101:
			d = *(pbin+2);
			break;
      
		case 110:
			d = *(pbin+1);
			break;
      
		case 111:
			d = *(pbin);
			break;
	}
	
	return d;
}

// Función para pasar de decimal a binario
void dec2bin(int rule, int* bin){
  int i = 7;
  // loop para calcular binario
  while((rule>0)&&(i>=0)){
    *(bin+i) = rule%2;
    rule =rule/2;
    i--;
  }
  
}

void main(int argc, char *argv[]){
  //Variables para bin
  int nregla = atoi(argv[1]); // numero de la regla
  int arreglo_bin[8]= {0}; //arreglo para guardar número binario
  dec2bin(nregla, &arreglo_bin[0]);
  
  //variables para piramide
	int nvert = atoi(argv[2]); //cantidad de cuadrdaditos hacia abajo
	//printf("%d\n",nvert);
	int nhoriz = nvert*2+1; //cantidad de columnas (cuadraditos horizontales) +2
  //printf("%d\n\n",nhoriz);
	int medio=nvert; //posición cuadradito del medio
	int fila[nhoriz]; //definicion del arreglo horizontal
  int fila_sgt[nhoriz];
 
  // Loop para inicializar los arreglos en 0
  int i = 0;
  for(i=0; i<nhoriz; i++){
    fila[i]=0;
    fila_sgt[i]=0;
  }
	fila[medio] = 1; //semilla de primera fila
 
  printf("Construyendo automata regla %d, con %d lineas:\n", nregla, nvert);
 
	
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
    
  
  int j = 0;
	for(j;j<nvert-1;j++){
    // loop que recorre el arreglo horizontal
    for(i=1; i<(nhoriz-1); i++){ 
      int trio = fila[i-1]*100+fila[i]*10+fila[i+1]; // abc -> d (guia)
      
      //printf("%d\n",trio); ///!!!!!!!!!!!!!!!!!!!!!!
      
      int d = reglaXX(trio,&arreglo_bin[0]);
      fila_sgt[i]=d;		   
    }
    
    //printf("\n\n\n");
    
    //sobre escribe fila 
    for(i=0; i<nhoriz; i++){
      fila[i]=fila_sgt[i];
    }
  	
  	//imprime fila
  	/*for (i=1; i<(nhoriz-1); i++){
      if(fila[i]){
  		printf("%d",fila[i]);
      }
      else{
      }
  	}*/
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
