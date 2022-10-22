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
int dividirCuadrantesw(int w_or,int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top);
int dividirCuadrantesh(int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top);
int recorrerCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top);
void llenarQuadtree(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact, int niveles);
Quadtree* addNode(int dato);
int readNode(Quadtree* p);
void llenarImg(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact);
void rallarCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top,int valor);
Quadtree* borrarArbol(Quadtree* t);

/*variables globales*/


/*MAIN*/
int main(int argc, char **argv){
	int width, height, bpp;
	char *imgname = argv[1];
	int niveles = atoi(argv[2]);
	
	
	//uint8_t valor = 0;
	
	// Para cargar la imagen de entrada, y guardarla en img
	uint8_t* img = stbi_load(imgname, &width, &height, &bpp, 0);
	printf("Imagen %s cargada! width %d, height %d, bpp %d\n", imgname, width, height, bpp);
	
	printf("El valor del 1er pixel es %d.\n",*(img));

	// Escriba aca su codigo. Cree y utilice las funciones que estime pertinente.
	int width_aux=width, height_aux=height, bpp_aux=bpp; 
	
	//printf("puntero original: %p\n",img);
	
	/*dubug
	dividirCuadrantes(&width_aux, &height_aux, cuadrantes, img);
	printf("I:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[0])); 
	printf("II:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[1]));
	printf("III:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[2]));
	printf("IV:%d\n",recorrerCuadrante(width_aux, height_aux, cuadrantes[3]));
	*/
	Quadtree* raiz = addNode(recorrerCuadrante(width,width_aux, height_aux, img));
	
	llenarQuadtree(width,width_aux, height_aux,img, raiz,0, niveles);
	
	//printf("aux:%d,%d\n",width_aux, height_aux);
	
	llenarImg(width,width_aux, height_aux, img, raiz,0);
	
	
	
	/*---------------------------------
	int i,j;
	uint8_t *pix;
	uint8_t value;
	int flag = 0;

	for(j = 0; j < height; j++)
	{
		pix = img + j*width;
		for(i = 0; i < width; i++)
		{

			if(*pix<255 && *pix >128) printf(" ");
			//else printf("*");
			
			else if(*pix<128 && *pix >0){
				printf("@");
			}else{
				printf(".");
			}
			pix++;
		}
		printf("\n");
	}
	/*----------------------------------*/
	
	
	
	
	
	
	
	
	// Para guardar la imagen resultante, almacenada en img, en out.jpg
	stbi_write_jpg("out.jpg", width, height, CHANNEL_NUM, img, 100);
	// Liberando espacio de memoria de la imagen creada
	stbi_image_free(img);
	
	borrarArbol(raiz);
	
}

/*-----------------------------------API quad-tree--------------------------------------*/
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

int readNode(Quadtree* p){
	return(p->color);
}

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

int dividirCuadrantesw(int w_or,int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top){ //left_top-> puntero del primer pixel del cuadrante
	int i = 0;
	//int w;
	//int width_aux=width, height_aux=height, bpp_aux=bpp;
	int width_mitad, height_mitad;
	
	if((width_aux)%2==0){ //par
		width_mitad=(width_aux)/2;
	}
	else{ //impar
		width_mitad=((width_aux)-1)/2;
	}
	
	if((height_aux)%2==0){ //par
		height_mitad=(height_aux)/2;
	}
	else{ //impar
		height_mitad=((height_aux)-1)/2;
	}
	//w=width_mitad;
	//printf("w=%d\n",*(width_aux));
	//printf("w=%d\n",width_mitad);
	
	/*printf("%d\n",left_top);
	printf("%d\n",left_top+width_mitad-1);
	printf("%d\n",left_top+width_mitad*height_mitad-height_mitad-1);
	printf("%d\n",left_top+width_mitad*height_mitad-1);
	
	printf("%d\n",*(left_top));
	printf("%d\n",*(left_top+width_mitad-1));
	printf("%d\n",*(left_top+width_mitad*height_mitad-height_mitad-1));
	printf("%d\n",*(left_top+width_mitad*height_mitad-1));*/
	
	(cuadrantes[0])=left_top;
	(cuadrantes[1])=left_top+width_mitad;
	(cuadrantes[2])=left_top+w_or*(height_mitad);
	(cuadrantes[3])=left_top+w_or*(height_mitad)+width_mitad;
	//printf("w: la mitad de %d es %d.\n ",width_aux,width_mitad);
	return width_mitad;
}

int dividirCuadrantesh(int width_aux, int height_aux, uint8_t* cuadrantes[4], uint8_t* left_top){ //left_top-> puntero del primer pixel del cuadrante
	int i = 0;
	//int width_aux=width, height_aux=height, bpp_aux=bpp;
	int width_mitad, height_mitad;
	
	if((width_aux)%2==0){ //par
		width_mitad=(width_aux)/2;
	}
	else{ //impar
		width_mitad=((width_aux)-1)/2;
	}
	
	if((height_aux)%2==0){ //par
		height_mitad=(height_aux)/2;
	}
	else{ //impar
		height_mitad=((height_aux)-1)/2;
	}
	//printf("h: la mitad de %d es %d.\n ",height_aux,height_mitad);
	return height_mitad;
}

int recorrerCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top){
	int i=1;
	int c = 0;
	int bpp_act=0;//bpp actual
	int bpp_first=*left_top; //primer pixel
	//recorrer
	if(width_aux>1){
		for (i,c; c<(height_aux); i++){ 
			bpp_act=*(left_top+i);
			if(bpp_first!=bpp_act){
				return 2;
			}
			if(i==width_aux){
				i=-1;
				left_top+=w_or;
				c++;
			}
		}
	}
	//return
	if (bpp_first>=0 && bpp_first<=128){
		return 0;
	}
	else if(bpp_first<=255 && bpp_first>128){
		return 1;
	}
	/*else{
		return 2;
	}*/
	printf("errorsito");
	exit(1);
}

void llenarQuadtree(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact,int niveles){
	int f=recorrerCuadrante(w_or,width_aux, height_aux, p);
	int w=width_aux,h=height_aux;
	//printf("%d",f);
	//uint8_t** cuadrantes[4];
	//dividirCuadrantes(width_aux, height_aux, cuadrantes, p);
	//printf("nact=%d, niveles=%d\n",nact, niveles);
	if(w==1)printf("%d",f);
	if(f==2 && nact<niveles && w>1){
		//printf("entra");
		nact++;
		uint8_t* cuadrantes[4];
		w=dividirCuadrantesw(w_or,w, h, cuadrantes, p);
		h=dividirCuadrantesh(w, h, cuadrantes, p);
		//printf("w=%d\n",w);
		//printf("h=%d\n",h);
		
		(nodo->nodos[0]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[0]));
	//	printf("el nodo 0 es %d\n",recorrerCuadrante(w, h, cuadrantes[0]));
		
		llenarQuadtree(w_or,w, h,cuadrantes[0],nodo->nodos[0],nact, niveles);
		
		
		(nodo->nodos[1]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[1]));
		//printf("el nodo 1 es %d\n",recorrerCuadrante(w, h, cuadrantes[1]));
		llenarQuadtree(w_or,w,h,cuadrantes[1],nodo->nodos[1],nact, niveles);
		
		(nodo->nodos[2]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[2]));
		//printf("el nodo 2 es %d\n",recorrerCuadrante(w, h, cuadrantes[2]));
		llenarQuadtree(w_or,w, h,cuadrantes[2],nodo->nodos[2],nact, niveles);
		
		(nodo->nodos[3]) = addNode(recorrerCuadrante(w_or,w, h, cuadrantes[3]));
		//printf("el nodo 3 es %d\n",recorrerCuadrante(w, h, cuadrantes[3]));
		llenarQuadtree(w_or,w, h,cuadrantes[3],nodo->nodos[3],nact, niveles);
	}
	
}
/*de acá para arriba funaciona todo u.u*/
/*impleentación lectura de quadtree y escritura de imagen*/
/*void rallarCuadrante(int width_aux, int height_aux, uint8_t* left_top,int valor){
	int i=0;
	//recorrer
	for (i; i<=(width_aux*height_aux*3); i++){ 
		switch(valor){
			case 0: *(left_top+i)=0;
			case 1: *(left_top+i)=255;
			case 2: *(left_top+i)=128;
		
		}
	}
}*/
/*void rallarCuadrante(int w_or, int width_aux, int height_aux, uint8_t* left_top,int valor){
	int i=0;
	int c = 1;
	int a = 0;
	//recorrer
	for (i,c; c<height_aux; i++){ 
		//printf("w=%d  i=%d,\n",width_aux,i);
		switch(valor){
			case 0: *(left_top+i)=0; 
					break;
			case 1: *(left_top+i)=255;
					break;
			case 2: *(left_top+i)=128;
					break;
		}
		if(i==width_aux-1){
			i=0;
			left_top+=w_or;
			c++;
		}
		//printf("%d ralla\n",a);
		a++;
	}
}*/

void rallarCuadrante(int w_or,int width_aux, int height_aux, uint8_t* left_top,int valor){
	int i = 0;
	int c =0;
	//recorrer
	//printf("w=%d\n",width_aux);
	for (i,c; c<height_aux; i++){ 
		//printf("w=%d  i=%d,\n",width_aux,i);
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
		//printf("i=%d\n",i);
		if(i==width_aux){
			i=-1;
			left_top+=w_or;
			c++;
		//	printf("c+1=%d",c);
		}
		//printf("%d ralla\n",a);
	}
}

void llenarImg(int w_or,int width_aux, int height_aux,uint8_t* p, Quadtree* nodo,int nact){
	int w=width_aux,h=height_aux;
	if(nodo->nodos[0]!=NULL){
		//nact;
		
		uint8_t* cuadrantes[4];
		w=dividirCuadrantesw(w_or,w, h, cuadrantes, p);
		h=dividirCuadrantesh(w, h, cuadrantes, p);
		
		llenarImg(w_or,w, h,cuadrantes[0],nodo->nodos[0],nact);
		llenarImg(w_or,w, h,cuadrantes[1],nodo->nodos[1],nact);
		llenarImg(w_or,w, h,cuadrantes[2],nodo->nodos[2],nact);
		llenarImg(w_or,w, h,cuadrantes[3],nodo->nodos[3],nact);
	}
	else{
		//printf("w=%d\n",w);
		//printf("h=%d\n",h);
		int valor=0;
		valor = readNode(nodo);
		//printf("queadtree tiene valor %d.\n",valor);
		//printf("puntero a rallar: %p\n",p);
		rallarCuadrante(w_or,w,h, p,valor);
		
	}
	
}