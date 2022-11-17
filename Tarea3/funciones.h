#ifndef __FUNCIONES__
#define __FUNCIONES__
//técnicas de open addressing
int h_lin_prob(int k,int i,int m);
int h_quad_prob(int k, int i, int m);
int h_doub_hash(int k, int i, int m);

//insertar dato
int hash_insert(int T[], int k, int m, int tec); //general

void hash_insert_3T(int T1[], int T2[], int T3[], int k, int m); //particular, 3 tablas

//archivo
void archivo(int T[], char* arch_name);

#endif // __TAREA1__