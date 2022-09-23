#include <stdio.h>
#include <stdlib.h> 
#include "tarea1.h"


#define PI 3.14159265 //se utiliza pi en el cálculo del volumen

// Coloque aca la implementacion de las funciones definidas en tarea1.h

// Implementación funcion1: numeros pares de 1 a 50
void funcion1(){
	int i=0;
	int par = 0;
	//loop para imprimir los números pares
	for(i; i<=50/2; i++){
		par = 2*i;
		printf("%d ",par);
	}
	printf("\n");
}

// Implementación funcion2: números impares de 1 a 50
void funcion2(){
	int i=0; //contador
	int impar = 0;
	// loop para imprimir los números impares
	for(i; i<50/2; i++){ //el contador llega hasta 25-1 para que no incluya el 51
		impar = 2*i+1;
		printf("%d ",impar);
	}
	printf("\n");
}


// Implementación funcion3: factorial
void funcion3(){
	float n; //número a ingrsar
	int i=1; //contador
	unsigned long fact=1; //variable que guarda el cálculo (guarda 8bytes, hasta 2^32)
  
	// ingreso de valor
	printf("Calcular factorial de (ingresar numero): ");
	scanf("%float",&n);
	
	//para verificar si el numero ingrsado es entero
	int a = n; // pasar n a entero
	float dec = n-a; //separa aprte entera de parte decimal
	
	
	if(dec>0){ //decimal
		printf("Valor invalido, debe ser un numero entero.\n");
	}
  
	else if(n>20 || n<0){ //cálculo entrada correcta
		printf("Numero ingresado debe estar entre 0 y 20.\n");
	}
  
	else if((0<n) && (n<=20)){ //solo alcanza a calcular hasta 20!
    
		for (i; i<=n; i++){
  			fact*=i;
		} 
		printf("El factorial de %d es %lu.\n", a, fact);
	}
 
	else if (n==0){ //factorial de 0
		fact = 1;
		printf("El factorial de %d es %lu.\n", a, fact);
	}
	
	
}


// Implementación funcion4: volumen de la esfera
void funcion4(){
	float r = 0;
	float v = 0;
	printf("Ingresar valor del radio: ");
	scanf("%float", &r);
	if (r<0){
		printf("Valor invalido\n");
	}
	else {
		v = 4*r*r*r*PI/3; //cálculo del volumen
		printf("El volumen de una esfera de radio %f es %f\n", r, v); //resultado con 6 decimales
	}
}

// Implementación funcion5: dado de 6 caras
void funcion5(){
	int dado = 0;
	srand(time(NULL)); //semilla del random según fecha/hora
	dado = rand() % 6 + 1; // número aleatorio de 1 a 6
	printf("El valor del dado es %d\n",dado);

}

//------------- Función principal --------------------
int main(int argc, char **argv){
	int opcion=0;
	
// Aca se desarrollara el resto del codigo

	printf("\nIngrese la funcion que desea implementar:\n");
	printf("\t1. Mostrar los numeros pares del 1 al 50\n");
	printf("\t2. Mostrar los numeros impares del 1 al 50\n");
	printf("\t3. Calcular el factorial de algun numero\n");
	printf("\t4. Calcular el volumen de una esfera a partir de su radio\n");
	printf("\t5. Muestre por pantalla el resultado de lanzar un dado de 6 caras\n\n");
	printf("Ingrese su opcion: ");
	scanf(" %d", &opcion);
	switch(opcion){
		case 1:
		//Llame a funcion1 y muestre el resultado
			funcion1();
		break;
		case 2:
		//Llame a funcion2 y muestre el resultado
			funcion2();
		break;
		case 3:
		//Llame a funcion3 y muestre el resultado
			funcion3();
			
		break;
		case 4:
		//Llame a funcion4 y muestre el resultado
			funcion4();
		break;
		case 5:
		//Llame a funcion5 y muestre el resultado
			funcion5();
		break;
		default:
		printf("Opcion no valida\n\n");
		break;
	}
}