TAREA 3 ELO320, 2022-2
Natalia Vega Quinteros

PARA COMPILAR:
	gcc main.c funciones.c -o tarea3

	./tarea3 n_elem

 donde n_elem es la cantidad de elementos a ingrasar en la tabla.

El tamaño de la tabla se define dentro del código, en una macro llamada TAM_TABLA.

OBSERVACIONES
 - Linear probing busca una posición desocupada verificando una por una todas las posiciones en orden, es decir, verifica si la casilla contigua está descopuda, si no lo está, revisa la siguiente. Un problema de esta técnica es que se tienden a formar grupos a medida que las llaves colisionan, provocando que cada vez sea más ineficiente la ubicacion de cada llave.

 - Quadratic probing reduce el problema mencionado, pero es más probable que la tabla hash tenga overflow antes de llenarse completamente, debido a que el algoritmo hizo las iteraciones correspondientes y no calzó con nigún espacio vacío.

 - Double hashing reduce y optimiza el problema del linear probing, pero es la tecnica que tiene alto overflow de la tabla hash. Esta utiliza dos fucniones hash combinadas.

CONCLUSIONES:
 - La técnica de linear probing asegura que todas las casillas de la tabla hash serán utilizadas, es decir, solo hay hash table overflow si la cantidad de llaves es mayor al tamaño de la tabla. 

 - Al probar con numero de llaves al rededor de 1800 se comienzan a presentar hash table overflow, la mayoría de las veces con la técnica 3 en primera intancia. Miesntras más aumena la cantidad de llaves, más aumeta el overflow con las técnicas 2 y 3. El momento en que comience a generarse el overflow dependerá de los numeros que se generen aleatoriamente.

 - Sobre los patrones de llenado, con un número considerable de llaves (1000) se puede ver que en el linear probing las llaves se encuentran más agrupadas, las otras dos técnicas no parecen tener un patrón determinado.

 - Analizando en número de colisiones se puede ver que la tecnica double hashing siempre es la que tiene menos colisiones.