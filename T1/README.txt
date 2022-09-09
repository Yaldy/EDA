Archivo README tarea1_ELO32.
Natalia Vega Quinteros.
ROL: 201904501-6.

El archivo tarea1.c contiene la implementación de la función principal (main) que consiste en un programa que interactua con el usuario para consultarle qué acción quiere que haga.
Además, contiene la implementación de las 5 funciones que son llamadas en main.
	funcion1: entrega los números pares del 0 al 50.
	funcion2: entrega los números impares del 0 al 50.
	funcion3: calcula el factorial de un número ENTERO. Esta función solicita que el usuario ingrese un dato. 
	funcion4: calcula el volumen de una esfera. El radio de esta es ingresado por el usuario, y las unidades de la salida deben ser interpretadas por este, según las unidades del dato que ingresó. La constante pi se aproxima como 3.14159265. Resultado entrega hasta 6 decimales
	funcion5: entrega un valor aleatorio de 1 a 6.
estas funciones son llamasdas según el número que el usuario ingrese (de 1 a 5). En caso de que se ingrese un valor fuera de este rango, el programa calificará la entrada como no válida.
	
El archivo tarea.h contiene la definición de las 5 funciones mencionadas anteriormente. Este archivo está incluida como librería usuaria en el archivo tarea1.c.

Para compilar este programa se debe teclear en la consola de aragorn el siguiente comando

	gcc tarea1.c -o tarea1

Para ejecutar el programa se debe teaclear el  comando 

	./tarea1