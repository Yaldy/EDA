#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 1

/*
negro: 0
gris: 128
blanco: 255

bpp # 8-bit components per pixel
*/

typedef struct qtree{
int color; // 0: negro, 1: blanco, 2:gris
struct qtree *nodos[4];
}Quadtree;

/*Funcion para revisar es blanco, negro o gris*/


int main(int argc, char **argv){
	int width, height, bpp;
	char *imgname = argv[1];
	int niveles = atoi(argv[2]);
	
	
	//uint8_t valor = 0;
	
	// Para cargar la imagen de entrada, y guardarla en img
	uint8_t* img = stbi_load(imgname, &width, &height, &bpp, 0);
	printf("Imagen %s cargada! width %d, height %d, bpp %d\n", imgname, width, height, bpp);
	
	//printf("El valor es %d.\n",*(img+width*height-width));

	// Escriba aca su codigo. Cree y utilice las funciones que estime pertinente.
	int width_aux=width, height_aux=height, bpp_aux=bpp;
	uint8_t** cuadrantes[4] //por cada nodo, deberia ir dentro de un for o algo
	
	
	
	
	
	
	// Para guardar la imagen resultante, almacenada en img, en out.jpg
	stbi_write_jpg("out.jpg", width, height, CHANNEL_NUM, img, 100);
	// Liberando espacio de memoria de la imagen creada
	stbi_image_free(img);
	
	
}

/*-----------------------------------API quad-tree--------------------------------------*/
Quadtree *addNode(int colorin,){
	Quadtree* node=malloc(sizeof(Quadtree));
	if (node==NULL){
		exit(1);
	}
	else{
		node->color = colorin;
		node->nodos[0]=NULL;
		node->nodos[1]=NULL;
		node->nodos[2]=NULL;
		node->nodos[3]=NULL;
		
	}
	
}

/*-------------------------------------FUNCIONES----------------------------------------*/

void dividirCuadrantes(int width_aux, int height_aux, uint8_t** cuadrantes[4], uint8_t left_top){ //left_top-> puntero del primer pixel del cuadrante
	int i = 0;
	//int width_aux=width, height_aux=height, bpp_aux=bpp;
	int width_mitad, height_mitad;
	
	if(width_aux%2==0){ //par
		width_mitad=width_aux/2;
	}
	else{ //impar
		width_mitad=(width_aux+1)/2;
	}
	
	if(height_aux%2==0){ //par
		height_mitad=height_aux/2
	}
	else{ //impar
		height_mitad=(height_aux+1)/2
	}
	
	*(cuadrantes[0])=left_top;
	*(cuadrantes[1])=left_top+width_mitad-1;
	*(cuadrantes[2])=left_top+width_mitad*height_mitad-height_mitad-1;
	*(cuadrantes[3])=left_top+width_mitad*height_mitad-1;
}

int recorrerCuadrante(int width_aux, int height_aux, uint8_t* left_top){
	int i=1;
	int bpp_act=0;//bpp actual
	int bpp_first=*left_top; //primer pixel
	//recorrer
	for (i; i<(width_aux*height_aux); i++){
		bpp_act=*(left_top+i);
		if(bpp_first!=bpp_act){
			return 2;
		}
	}
	
	//return
	if (bpp_act==0){
		return 0;
	}
	else if(bpp_act==255){
		return 1;
	}
	else{
		return 2;
	}
}