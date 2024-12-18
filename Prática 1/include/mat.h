#ifndef MAT_H
#define MAT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <getopt.h>

// Definições de constantes
#define MAXTAM 100
#define INITRANDOMRANGE 10
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

// Definição da estrutura de matriz
typedef struct mat {
    double m[MAXTAM][MAXTAM];
    int tamx, tamy;
    int id;
} mat_tipo;

// Funções de manipulação de matriz
void criaMatriz(mat_tipo *mat, int tx, int ty, int id);
void inicializaMatrizNula(mat_tipo *mat);
void inicializaMatrizAleatoria(mat_tipo *mat);
double acessaMatriz(mat_tipo *mat);
void imprimeMatriz(mat_tipo *mat);
void salvaMatriz(mat_tipo *mat, FILE *out);
void escreveElemento(mat_tipo *mat, int x, int y, double v);
double leElemento(mat_tipo *mat, int x, int y);
void copiaMatriz(mat_tipo *src, mat_tipo *dst, int dst_id);
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void transpoeMatriz(mat_tipo *a);
void destroiMatriz(mat_tipo *a);

#endif // MAT_H

