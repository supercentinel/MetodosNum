#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

typedef struct 
{
    long double c;
    long double r;
}Circulo;

Circulo* CirculosDeGerschgorin(Matriz a)
{
    Circulo *circulos;
    int i, j, sum = 0;

    if((circulos = calloc(a.n, sizeof(Circulo))) == NULL) return NULL;
    
    for ( i = 0; i < a.n; i++)
    {
        for ( j = 0; j < a.m; j++)
        {
            if(i == j) circulos[i].c = a.a[i][j];
            else sum += fabsl(a.a[i][j]);
        }
        circulos[i].r = sum;
        sum = 0;
    }
    
    return circulos;
}

long double MPotencias(Matriz a, long double tol, int maxI)
{
    int i, k = 0;
    Matriz xk, axk, xkp1;
    long double lamda, lambdam1, err;

    CrearMat(&xk, a.n, 1);
    
    for ( i = 0; i < xk.m; i++)
    {
        xk.a[i][0] = 1;
    }

    while(1)
    {
        lambdam1 = lamda;
        axk = ProdMat(a, xk);
        lamda = maxElmt(axk);
        err = fabsl(lamda - lambdam1);
        if(err < tol || k > maxI) break;
        printf("lambda  = %LF error = %LF k = %d\n", lamda, err, k);
        xkp1 = ProdEs(axk, 1/lamda);

        for (i = 0; i < xk.m; i++)
        {
            xk.a[i][0] = xkp1.a[i][0];
        }
        printf("Ax^k:\n");
        ImpMat(axk);
        printf("x^k+1:\n");
        ImpMat(xkp1);

        DestruirMat(xkp1);
        DestruirMat(axk);
        k++;
    }
    
    DestruirMat(xk);

    return lamda;
}


int main(int argc, char const *argv[])
{
    Matriz a;
    Circulo *circulos;
    int i;
    long double lambdaMax;

    CrearMat(&a, 4, 4);

    a.a[0][0] = 4;
    a.a[0][1] = 2;
    a.a[0][2] = -1;
    a.a[0][3] = 1;

    a.a[1][0] = 2;
    a.a[1][1] = 8;
    a.a[1][2] = 4;
    a.a[1][3] = -3;

    a.a[2][0] = 3;
    a.a[2][1] = 6;
    a.a[2][2] = 2;
    a.a[2][3] = 2;

    a.a[3][0] = 1;
    a.a[3][1] = 2;
    a.a[3][2] = 1;
    a.a[3][3] = -1;

    circulos = CirculosDeGerschgorin(a);

    for (i = 0; i < a.n; i++)
    {
        printf("Circulo [i]: c = %LF r = %LF\n", circulos[i].c, circulos[i].r);
    }
    
    lambdaMax = MPotencias(a, 0.0005, 100);

    printf("\nEl valor propio maximo es %LF\n", lambdaMax);

    free(circulos);
    DestruirMat(a);
    
    return 0;
}
