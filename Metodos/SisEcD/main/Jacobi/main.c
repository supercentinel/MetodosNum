#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

Matriz gauss(Matriz m)
{
    int i, j, k;
    long double fm, r_1, r_2;

    Matriz d;

    if( m.m != m.n) return d;

    CrearMat(&d, m.m, m.n);

    for (i = 0; i < m.n; i++)
    {
        for (j = 0; j < m.m; j++)
        {
            d.a[i][j] = m.a[i][j];
        }
    }

    for ( k = 0; k < d.n - 1; k++)
    {
        for ( i = k+1; i < d.n; i++)
        {
            fm = -((d.a[i][k])/(d.a[k][k]));

            for ( j = k; j < d.m; j++)
            {
                r_1 = (d.a[k][j]);
                r_2 = (d.a[i][j]);
                d.a[i][j] = ((fm) * (r_1)) + (r_2);
            }   
        }
    }

    return d;
}

long double detGauss(Matriz a)
{
    Matriz m;

    m = gauss(a);

    long double det = 1;
    int i;

    for (i = 0; i < m.n; i++)
    {
        det = det * m.a[i][i];
    }

    DestruirMat(m);

    return det;
}

int esEDD(Matriz a)
{
    int i, j;
    long double sum;

    for ( i = 0; i < a.m; i++)
    {
        sum = 0;

        for (j = 0; j < a.n; j++)
        {
            if(j == i) continue;;
            sum += fabsl(a.a[i][j]);
        }
        if(fabsl(a.a[i][i]) < sum) return -1;
    }
    return 0;
}

int tolerancia(Matriz Ne, long double tol)
{
    int i;

    for (i = 0; i < Ne.m; i++)
    {
        if(Ne.a[i][0] > tol) return 0;
    }
    return 1;
}

Matriz jacobi(Matriz a, Matriz b)
{
    int i = 0, j = 0, k = 0, maxK = 100;
    long double tol = 0.005;

    
    Matriz sol, solk, solT;
    CrearMat(&sol, b.m, 1);
    CrearMat(&solk, b.m, 1);
    CrearMat(&solT, b.m, 1);

    sol.a[0][0] = (b.a[0][0]/a.a[0][0]);
    sol.a[1][0] = (b.a[1][0]/a.a[1][1]);
    sol.a[2][0] = (b.a[2][0]/a.a[2][2]);
    sol.a[3][0] = (b.a[3][0]/a.a[3][3]);

    solk.a[0][0] = 1;
    solk.a[1][0] = 1;
    solk.a[2][0] = 1;
    solk.a[3][0] = 1;

    while (k < maxK)
    {
        
        for(i = 0; i < sol.m; i++)
        {

            for (j = 0; j < a.n; j++)
            {
                sol.a[i][0] += ((((-a.a[i][j]) * (solk.a[i][0]))/(a.a[i][i])) + ((b.a[i][0])/(a.a[i][i])));
            }
            
            solk.a[i][0] = sol.a[i][0];
            solT.a[i][0] =  ((fabsl((sol.a[i][0]) - (solk.a[i][0]))));

        }

        printf("s\n");
        ImpMat(sol);
        printf("\n");

        if(tolerancia(solT, tol) == 1) break;

        k++;
    }

    printf("\nIteraciones totales = %d\n", k);
    
    DestruirMat(solT);
    DestruirMat(solk);

    return sol;
}


int main(int argc, char const *argv[])
{
    Matriz a , b, s;

    CrearMat(&b, 4, 1);

    CrearMat(&a, 4, 4);

    b.a[0][0] = 6;
    b.a[1][0] = 25;
    b.a[2][0] = -11;
    b.a[3][0] = 15;


    a.a[0][0] = 10;
    a.a[0][1] = -1;
    a.a[0][2] = 2;
    a.a[0][3] = 0;

    a.a[1][0] = -1;
    a.a[1][1] = 11;
    a.a[1][2] = -1;
    a.a[1][3] = 3;

    a.a[2][0] = 2;
    a.a[2][1] = 1;
    a.a[2][2] = 10;
    a.a[2][3] = -1;

    a.a[3][0] = 0;
    a.a[3][1] = 3;
    a.a[3][2] = -1;
    a.a[3][3] = 8;

    ImpMat(a);

    printf("\nsi es 0 = %d, es EDD", esEDD(a));
    printf("\nDeterminante es: %LF\n", detGauss(a));
    
    ImpMat(b);

    printf("\nLa solucion es\n");

    s = jacobi(a, b);

    ImpMat(s);

    DestruirMat(s);
    DestruirMat(b);
    DestruirMat(a);

    return 0;
}
