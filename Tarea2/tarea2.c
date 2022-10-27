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
*/

typedef struct qtree{
int color; // 0: negro, 1: blanco, 2:gris
struct qtree *nodos[4];
}Quadtree;

/*Prototipos de funciones*/
int dividirCuadrantesw(int w_or,int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top);
int dividirCuadrantesh(int height_aux);
int recorrerCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top);
void llenarQuadtree(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact, int niveles);
Quadtree* addNode(int dato);
int readNode(Quadtree* p);
void llenarImg(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact);
void rallarCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top,int valor);
Quadtree* borrarArbol(Quadtree* t);


/*MAIN*/
int main(int argc, char **argv){
	int width, height, bpp;
	char *imgname = argv[1];
	int niveles = atoi(argv[2]);
		
	// Para cargar la imagen de entrada, y guardarla en img
	uint8_t* img = stbi_load(imgname, &width, &height, &bpp, 0);
	printf("Imagen %s cargada! width %d, height %d, bpp %d\n", imgname, width, height, bpp);

	// Escriba aca su codigo. Cree y utilice las funciones que estime pertinente.
	int width_aux=width, height_aux=height, bpp_aux=bpp; 
	Quadtree* raiz = addNode(recorrerCuadrante(width,width_aux, height_aux, img));
	llenarQuadtree(width,width_aux, height_aux,img, raiz,0, niveles);
	llenarImg(width,width_aux, height_aux, img, raiz,0);
	
	// Para guardar la imagen resultante, almacenada en img, en out.jpg
	stbi_write_jpg("out.jpg", width, height, CHANNEL_NUM, img, 100);
	
	// Liberando espacio de memoria de la imagen creada y el Quad-tree
	stbi_image_free(img);
	borrarArbol(raiz);
	
}

/*-----------------------------------API quad-tree--------------------------------------*/
// Para crear nodo de quad-tree
Quadtree* addNode(int dato){
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

// Para leer color de un nodo (un poco inncesario)
int readNode(Quadtree* p){
	return(p->color);
}

// Para eliminar arbol y liberar memoria de cada nodo
Quadtree* borrarArbol(Quadtree* t){
	if(t!=NULL){
		t->nodos[0]=borrarArbol(t->nodos[0]);
		t->nodos[1]=borrarArbol(t->nodos[1]);
		t->nodos[2]=borrarArbol(t->nodos[2]);
		t->nodos[3]=borrarArbol(t->nodos[3]);
		free(t);
	}
}

/*-------------------------------------FUNCIONES----------------------------------------*/
// Para dividir un cuadrante en 4, devuelve el width de los cuadrantes resultantes
int dividirCuadrantesw(int w_or,int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top){ //left_top-> puntero del primer pixel del cuadrante
	int i = 0;
	int width_mitad, height_mitad;
	
	//dividir width
	if((width_aux)%2==0){ //par
		width_mitad=(width_aux)/2;
	}
	else{ //impar
		width_mitad=((width_aux)-1)/2;
	}
	
	// dividir height
	if((height_aux)%2==0){ //par
		height_mitad=(height_aux)/2;
	}
	else{ //impar
		height_mitad=((height_aux)-1)/2;
	}
	
	// guardar puntero al primer pixel de los 4 cuadrantes resultantes
	(cuadrantes[0])=left_top;
	(cuadrantes[1])=left_top+width_mitad*CHANNEL_NUM;
	(cuadrantes[2])=left_top+w_or*(height_mitad)*CHANNEL_NUM;
	(cuadrantes[3])=left_top+w_or*(height_mitad)*CHANNEL_NUM+width_mitad*CHANNEL_NUM;
	
	return width_mitad;
}

// Para dividir un cuadrante en 4, devuelve el height de los cuadrantes resultantes
int dividirCuadrantesh(int height_aux){ 
	int i = 0;
	int height_mitad;
	
	if((height_aux)%2==0){ //par
		height_mitad=(height_aux)/2;
	}
	else{ //impar
		height_mitad=((height_aux)-1)/2;
	}
	
	return height_mitad;
}

// Para recorrer cuadrante y definir el color del nodo correspondiente. Devuleve 0: negro, 1: blanco, 2: gris
/*Si el cuadrante ya no se puede dividir, duelve un 0 si el color del pixel esta entre 0 y 150 y 1 en otro caso. 
Esto es para que al dividir lo más posible la imágen, esta quede bien definida y no queden pixeles grises*/
int recorrerCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top){
	int i=1;
	int c = 0;
	int bpp_act=0;//bpp actual
	int bpp_first=*left_top; //primer pixel
	if(width_aux>1){ 
		for (i,c; c<(height_aux); i++){ 
			bpp_act=*(left_top+i);
			if(bpp_first!=bpp_act){
				return 2;
			}
			if(i==width_aux*CHANNEL_NUM){
				i=-1;
				left_top+=w_or*CHANNEL_NUM;
				c++;
			}
		}
	}
	if (bpp_first>=0 && bpp_first<=150){
		return 0;
	}
	else if(bpp_first<=255 && bpp_first>150){
		return 1;
	}
	// Si no logra definir el cuadrante
	printf("errorsito");
	exit(1);
}

// Para armar el quad-tree
void llenarQuadtree(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact,int niveles){
	int f=recorrerCuadrante(w_or,width_aux, height_aux, p);
	int w=width_aux,h=height_aux;
	
	if(f==2 && nact<niveles && w>1){ //condición de entrada
		nact++;
		uint8_t* cuadrantes[4];
		w=dividirCuadrantesw(w_or,w, h, cuadrantes, p);
		h=dividirCuadrantesh(h);
		
		// Se crean lo 4 hijos de cada nodo
		(nodo->nodos[0]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[0]));		
		llenarQuadtree(w_or,w, h,cuadrantes[0],nodo->nodos[0],nact, niveles);
		
		(nodo->nodos[1]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[1]));
		llenarQuadtree(w_or,w,h,cuadrantes[1],nodo->nodos[1],nact, niveles);
		
		(nodo->nodos[2]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[2]));
		llenarQuadtree(w_or,w, h,cuadrantes[2],nodo->nodos[2],nact, niveles);
		
		(nodo->nodos[3]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[3]));
		llenarQuadtree(w_or,w, h,cuadrantes[3],nodo->nodos[3],nact, niveles);
	}
	
}

// Para pintar el cuadrante del color correspondiente pixel por pixel
void rallarCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top,int valor){
	int i = 0;
	int c =0;
	//recorrer cuadrante
	for (i,c; c<height_aux; i++){ 
		switch(valor){
			case 0: *(left_top+i)=0; 
					//printf("negro");
					break;
			case 1: *(left_top+i)=255;
					//printf("blanco");
					break;
			case 2: *(left_top+i)=128;
					//printf("gris");
					break;
		}
		if(i==width_aux*CHANNEL_NUM-1){
			i=-1;
			left_top+=w_or*CHANNEL_NUM;
			c++;
		}
	}
}

// Para reconstruir la imagen a partir del quadtree
void llenarImg(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact){
	int w=width_aux,h=height_aux;
	if(nodo->nodos[0]!=NULL){
		
		uint8_t* cuadrantes[4];
		w=dividirCuadrantesw(w_or,w, h, cuadrantes, p);
		h=dividirCuadrantesh(h);
		
		llenarImg(w_or,w, h,cuadrantes[0],nodo->nodos[0],nact);
		llenarImg(w_or,w, h,cuadrantes[1],nodo->nodos[1],nact);
		llenarImg(w_or,w, h,cuadrantes[2],nodo->nodos[2],nact);
		llenarImg(w_or,w, h,cuadrantes[3],nodo->nodos[3],nact);
	}
	else{
		int valor=0;
		valor = readNode(nodo);
		rallarCuadrante(w_or,w,h, p,valor);
	}
}