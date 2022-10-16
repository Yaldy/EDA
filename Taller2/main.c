#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define SIZE_MAX 20

int main(int argc, char **argv){
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
				printf("dato:%d\n",n);
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
		//int resFinal = STACKpop();
		printf("%s=%d\n",exp,STACKpop());
	}
	STACKclean();
	return 0;
}