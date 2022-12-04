/*
    matriz.h
*/
#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct 
{
    //de m renglones y n columnas
    int m, n;
    long double **a;
}Matriz;

void CrearMat(Matriz *a,int m ,int n);
void DestruirMat(Matriz a);
void ImpMat(Matriz m);

Matriz ProdMat(Matriz a, Matriz b);
Matriz ProdEs(Matriz a, long double b);
Matriz MatT(Matriz m);

long double maxElmt(Matriz a);

#endif