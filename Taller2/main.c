#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define SIZE_MAX 20

int main(int argc, char **argv){
	if(argc<=1){
		printf("ERROR: ninguna formula ingresada.\n");
		exit(1);
	}
	int j = 1; //contaguro argv
	STACKinit(SIZE_MAX);
	for (j;j<=argc-1;j++){
		char* exp = argv[j]; // expresión
		int i = 0; //contador expresion
		//printf("%s\n",exp);
		for (i;exp[i]!=0;i++){
			//printf("el numero %c ascii es %d\n",exp[i],exp[i]);
			char num=exp[i];
			if((exp[i]>=48) && (exp[i]<=57)){
				int n = atoi(&num);
				//printf("dato:%d\n",n);
				STACKpush(n,SIZE_MAX);
			}
			else{
				//sacar del stack y operar
				int a = STACKpop();
				int b = STACKpop();
				int res=0;
				int flag=0;
				switch(exp[i]){
					case '+': 
						res = b + a;
						//printf("a+b\n");
						break;
					
					case '-':
						res = b - a;
						//printf("a-b\n");
						break;
					
					case '*':
						res = b * a;
						//printf("a*b\n");
						break;
					
					case '%':
						res = b % a;
						//printf("%d a %d = %d\n",a,b,res);
						break;
					
					default:
						//vaciar stack
						printf("Entrada %d invalida\n",j);
						flag = 1;
						break;
				}
				if(flag){
					break;
				}
				//meter resultado al stack
				
				STACKpush(res,SIZE_MAX);
			}
		}
		int resFinal = STACKpop();
		//txt(exp);
		//printf("%s=%d\n",exp,resFinal);
		
		/*___________________escribir en archivo____________________*/
		FILE *f = fopen("out.txt", "a");
		//printf("%s\n",str);
		if (f == NULL) {
    	    fprintf(stderr, "No se pudo crear el archivo trig.txt\n");
    	    exit(1);
    	}
		fprintf(f,"%s=%d", exp,resFinal);
		if(j!=argc-1){
			fprintf(f,"\n");
		}
		fclose(f);		
		/*----------------------------------------------------------*/
	}
	STACKclean();
	return 0;
}