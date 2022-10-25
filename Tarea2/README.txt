README tarea 2 ELO320
Natalia Vega Quinteros

CONTENIDO:
Este programa permite crear un Quad-tree a partir de una imagen de entrada y la cantidad de niveles que se quiere, para luego econstruila a partir de esta estructura de datos. Para esto se utilizan 2 bibliotecas usuario para manipular la imagen ("stb_image.h" y "stb_image_write.h"). 

El archivo tarea2.c contiene el código del programa. Este está dividido en distintas secciones que contienen los prototipos de las funciones implementadas, la función principal y la implementación de las funciones utilizadas para la cronstruccion y deconstrucciones del Quad-tree.

COMPILACIÓN:
Para compilar 
	gcc tarea2.c -lm -o tarea2
	./tarea2 imagen niveles

donde 'imagen' es el nombre de la imagen a ingresar en el algoritmo (ej. perro.jpg) y 'niveles' es el máximo de niveles que se quiere para el quadtree (ej. 10). Notar que si este número supera el máximo de divisiones que permite la imagen, no se logrará llegar a este nivel pero se tendrá la imágen lo más recontruida posible.

CONSIDERACIONES:
Este programa solo funciona con imagenes cuadradas, con número de pixeles potencia de dos y bpp = 1. 
Si la imagen de entrada no cumple con estas especificaciones no se obtendrá el resultado esperado.
En el archivo entregado se adjuntan 2 imagenes que cumplen con los requisitos. 