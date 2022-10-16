#include <stdio.h>
#include <string.h>
#include "stack.h"

int main(int argc, char **argv){
	int j = 1; //contaguro argv
	for (j;j<=argc-1;j++){
		char* exp = argv[j]; // expresión
		int i = 0; //contador expresion
		printf("%s\n",exp);
		for (i;exp[i]!=0;i++){
			//printf("el numero %c ascii es %d\n",exp[i],exp[i]);
			char num=exp[i];
			if((exp[i]>=48) && (exp[i]<=57)){
				int n = atoi(&num);
				printf("%d\n",n);
				//meter al stack
			}
			else{
				//sacar del stack y operar
				int a;
				int b;
				int res;
				int flag=0;
				switch(exp[i]){
					case '+': 
						res = a + b;
						printf("a+b\n");
						break;
					
					case '-':
						res = a - b;
						printf("a-b\n");
						break;
					
					case '*':
						res = a * b;
						printf("a*b\n");
						break;
					
					case '%':
						res = a % b;
						printf("a%b\n");
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
				
			}
		}
	}
	
	return 0;
}