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

/*Prototipos de funciones*/
void dividirCuadrantes(int* width_aux, int* height_aux, uint8_t* cuadrantes[4], uint8_t* left_top);
int recorrerCuadrante(int width_aux, int height_aux, uint8_t* left_top);
void llenarQuadtree(int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact, int niveles);
Quadtree* addNode(int dato);


int main(int argc, char **argv){
	int width, height, bpp;
	char *imgname = argv[1];
	int niveles = atoi(argv[2]);
	
	
	//uint8_t valor = 0;
	
	// Para cargar la imagen de entrada, y guardarla en img
	uint8_t* img = stbi_load(imgname, &width, &height, &bpp, 0);
	printf("Imagen %s cargada! width %d, height %d, bpp %d\n", imgname, width, height, bpp);
	
	/
	printf("El valor del 1er pixel es %d.\n",*(img));

	// Escriba aca su codigo. Cree y utilice las funciones que estime pertinente.
	int width_aux=width, height_aux=height, bpp_aux=bpp; 
	
	
	
	/*dubug
	dividirCuadrantes(&width_aux, &height_aux, cuadrantes, img);
	printf("I:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[0])); 
	printf("II:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[1]));
	printf("III:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[2]));
	printf("IV:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[3]));
	*/
	Quadtree* raiz = addNode(recorrerCuadrante(width_aux, height_aux, img));
	
	llenarQuadtree(width_aux, height_aux,img, raiz,0, niveles);
	
	printf("%d,%d\n",width, height);	
	
	// Para guardar la imagen resultante, almacenada en img, en out.jpg
	stbi_write_jpg("out.jpg", width, height, CHANNEL_NUM, img, 100);
	// Liberando espacio de memoria de la imagen creada
	stbi_image_free(img);
	
	
}

/*-----------------------------------API quad-tree--------------------------------------*/
void *addNode(int dato){
	Quadtree* node=malloc(sizeof(Quadtree));
	if (node==NULL){
		exit(1);
	}
	else{
		node->color = dato;
		node->nodos[0]=NULL;
		node->nodos[1]=NULL;
		node->nodos[2]=NULL;
		node->nodos[3]=NULL;
	}
	return node;
}

/*-------------------------------------FUNCIONES----------------------------------------*/
void llenarQuadtree(int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact,int niveles){
	int f=recorrerCuadrante(width_aux, height_aux, p);
	int w=width_aux,h=height_aux;
	//uint8_t** cuadrantes[4];
	//dividirCuadrantes(width_aux, height_aux, cuadrantes, p);
	printf("nact=%d, niveles=%d\n",nact, niveles);
	if(f==2 && nact<=niveles){
		nact++;
		uint8_t* cuadrantes[4];
		dividirCuadrantes(&w, &h, cuadrantes, p);
		
		(nodo->nodos[0]) = addNode(recorrerCuadrante(w, h, cuadrantes[0]));
		printf("el nodo 0 es %d\n",recorrerCuadrante(w, h, cuadrantes[0]));
		printf("w=%d\n",w);
		printf("h=%d\n",h);
		llenarQuadtree(w, h,cuadrantes[0],nodo->nodos[0],nact, niveles);
		
		
		(nodo->nodos[1]) = addNode(recorrerCuadrante(w, h, cuadrantes[1]));
		printf("el nodo 1 es %d\n",recorrerCuadrante(w, h, cuadrantes[1]));
		llenarQuadtree(w,h,cuadrantes[1],nodo->nodos[1],nact, niveles);
		
		(nodo->nodos[2]) = addNode(recorrerCuadrante(w, h, cuadrantes[2]));
		printf("el nodo 2 es %d\n",recorrerCuadrante(w, h, cuadrantes[2]));
		llenarQuadtree(w, h,cuadrantes[2],nodo->nodos[2],nact, niveles);
		
		(nodo->nodos[3]) = addNode(recorrerCuadrante(w, h, cuadrantes[3]));
		printf("el nodo 3 es %d\n",recorrerCuadrante(w, h, cuadrantes[3]));
		llenarQuadtree(w, h,cuadrantes[3],nodo->nodos[3],nact, niveles);
	}
	
}


void dividirCuadrantes(int* width_aux, int* height_aux, uint8_t* cuadrantes[4], uint8_t* left_top){ //left_top-> puntero del primer pixel del cuadrante
	int i = 0;
	//int width_aux=width, height_aux=height, bpp_aux=bpp;
	int width_mitad, height_mitad;
	
	if(*(width_aux)%2==0){ //par
		width_mitad=*(width_aux)/2;
	}
	else{ //impar
		width_mitad=(*(width_aux)-1)/2;
	}
	
	if(*(height_aux)%2==0){ //par
		height_mitad=*(height_aux)/2;
	}
	else{ //impar
		height_mitad=(*(height_aux)-1)/2;
	}
	*(width_aux)=width_mitad;
	*(height_aux)=height_mitad;
	/*printf("w=%d\n",*(width_aux));
	printf("h=%d\n",*(height_aux));
	
	printf("%d\n",left_top);
	printf("%d\n",left_top+width_mitad-1);
	printf("%d\n",left_top+width_mitad*height_mitad-height_mitad-1);
	printf("%d\n",left_top+width_mitad*height_mitad-1);
	
	printf("%d\n",*(left_top));
	printf("%d\n",*(left_top+width_mitad-1));
	printf("%d\n",*(left_top+width_mitad*height_mitad-height_mitad-1));
	printf("%d\n",*(left_top+width_mitad*height_mitad-1));*/
	
	(cuadrantes[0])=left_top;
	(cuadrantes[1])=left_top+width_mitad-1;
	(cuadrantes[2])=left_top+width_mitad*height_mitad-height_mitad-1;
	(cuadrantes[3])=left_top+width_mitad*height_mitad-1;
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

int valorNodo(){}