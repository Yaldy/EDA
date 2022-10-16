Taller 2 ELO320
Cristobal Caqueo ROL: 201921012-2
Natalia Vega Quinteros ROL: 201904501-6

El programa simula una calculadora polaca implementada con un stack. Este cuenta con dos implementaciones para hacer el stack, con arreglos o con listas.
Si se quiere ejecutar la implementación con arreglo se debe ingresar lo siguiente en la linea de comandos:

	gcc main.c stack_array.c -o Conarray
	./Conarray exp1 exp2 ... expn

Por otro lado, si se quiere ejecutar la implementación con lista se debe ingresar lo siguiente en la linea de comandos:

	gcc main.c stack_list.c -o Conlista
	./Conlista exp1 exp2 ... expn

donde expi son las expresiones en notacion polaca inversa

Para definir el tamaño máximo del stack se agrega una macro llamda SIZE_MAX en main.c.