#include <stdio.h>
#include <stdlib.h>

//hash_init

int h_lin_prob(int k,int i,int m){
	return (k%m+i)%m;
}

int h_quad_prob(int k, int i, int m){
	int c1 = 1;
	int c2 = 3;
	return (k%m+c1*i+c2*i^2)%m;
}

int h_doub_hash(int k, int i, int m){
	return (k%m + i*(1+k%(m-1)))%m;
}

void hash_insert(int T[], int k, int m, int tec){ //tabla hash, key, tamaño tabla, tecnica
	int i = 0;
	while(i != m){
		int j = 0;
		switch (tec){	//llmara a la técnica deseada
			case 1:
				j = h_lin_prob(k,i,m); 
				break;
			case 2:
				j = h_quad_prob(k,i,m); 
				break;
			case 3:
				j = h_doub_hash(k,i,m); 
				break;
		}
		if (T[j]==-1){ //las casillas vacías tienen -1, ver si se puede marcar de otra forma
			T[j]=k;
			return j;
		}
		else{
			i++;
		}
	}
	printf("hash table overflow");
	return -1; //retorna -1 en caso de error
}

void hash_insert_3T(int T1[], int T2[], int T3[], int k, int m){
	void hash_insert(T1[], k, m, 1); // linear probing
	void hash_insert(T2[], k, m, 2); // quadratic probing
	void hash_insert(T3[], k, m, 3); //	double hashing
}


//crear y escribir en archivo
void archivo(int T[], char* arch_name){
	FILE *arch;
	
	arch = fopen(arch_name,"w");
	if(arch==NULL){
		fputs("File errpr",stderr);
		exit(1);
	}
	
	
	//escribir archivo
	int j = 0;
	int i = 0;
	for(i=0;i<2000;i++){
		if(T[i]==-1){
			fprintf(arch, "%s", " ");
		}
		else{
			fprintf(arch, "%s", "X");
		}
		if(j == 99 && i != 1999){
			fprintf(arch, "%s", "\n");
			j=0;
		}
		else{
			j++;
		}
	}
	
	fclose (arch);
}