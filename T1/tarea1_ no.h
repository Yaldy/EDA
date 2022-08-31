#ifndef __TAREA1__
#define __TAREA1__
// Definicion funcion1: numeros pares de 1 a 50   (ok)
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

// Definicion funcion2: números impares de 1 a 50   (ok)
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
// Definicion funcion3: factorial   (ok)
void funcion3(){
	int n; //número a ingrsar
	int i=1; //contador
	int fact=1; //variable que guarda el cáulculo
	
	printf("Calcular factorial de (ingresar numero): ");
	scanf("%int",&n);
	
	
	if(n!=0){
		// loop para multiplicar los numeros de 1 a n
		for (i; i<=n; i++){
			fact*=i;
		}
	}
	else{
		fact = 1;
	}
	
	printf("El fatorial de %d es %d\n", n, fact);
}

// Definicion funcion4: volumen de la esfera
void funcion4(){
	float r = 0;
	float v = 0;
	printf("Ingresar valor del radio: ");
	scanf("%float", &r);
	v = 4*r*r*r/3; //cálculo del volumen
	printf("El volumen de una esfera de radio %f es %f", r, v);
}
// Definicion funcion5: dado de 6 caras
void funcion5(){
	
}
#endif // __TAREA1__
