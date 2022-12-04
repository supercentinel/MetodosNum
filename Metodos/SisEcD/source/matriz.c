/*
    matriz.c    
*/

#include <stdlib.h>
#include <stdio.h>

#include "matriz.h"

void CrearMat(Matriz *a,int m ,int n)
{
    int i;

    a->m = m;
    a->n = n;

    a->a = (long double **)calloc(m, sizeof(long double *));

    for (i = 0; i < m; i++)
    {
        a->a[i] = (long double *)calloc(n, sizeof(long double));
    }
}

void DestruirMat(Matriz a)
{
    int i, j;

        for(i = 0; i < a.m; i++)
        {
            a.a[i] = NULL;
            free(a.a[i]);
        }
    a.a = NULL;
    free(a.a);
}

void ImpMat(Matriz m)
{
    int i, j;

    for (i = 0; i < m.m; i++)
    {
        for (j = 0; j < m.n; j++)
        {
            printf("%LF ", m.a[i][j]); 
        }
        printf("\n");
    }
}

Matriz ProdMat(Matriz a, Matriz b)
{
    Matriz prod;
    int i, j, k;

    CrearMat(&prod, a.m, b.n);

    for ( i = 0; i < a.m; i++)
    {
        for ( j = 0; j < b.n; j++)
        {
            for ( k = 0; k < a.n; k++)
            {
                prod.a[i][j] += a.a[i][k] * b.a[k][j];
            }
            
        }
        
    }
    
    return prod;
}

Matriz ProdEs(Matriz a, long double b)
{
    Matriz Prod;
    int i, j;

    CrearMat(&Prod, a.m, a.n);

    for ( i = 0; i < a.m; i++)
    {
        for ( j = 0; j < a.n; j++)
        {
            Prod.a[i][j] = b * a.a[i][j];
        }
    }

    return Prod;
}

Matriz MatT(Matriz m)
{
    Matriz t;
    int i, j;

    CrearMat(&t, m.m, m.n);

    for ( i = 0; i < m.m; i++)
    {
        for ( j = 0; j < m.n; j++)
        {
            t.a[j][i] = m.a[i][j];
        }
    }
    
    return t;
}

long double maxElmt(Matriz a)
{
    int i, j;
    long double max;

    for ( i = 0; i < a.m; i++)
    {
        for ( j = 0; j < a.n; j++)
        {
            if(i == 0 && j == 0) max = a.a[i][j];
            if(a.a[i][j] > max) max = a.a[i][j];
        }
    }
    
    return max;
}