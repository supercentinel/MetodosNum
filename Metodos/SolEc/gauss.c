#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    //de m renglones y n columnas
    int m, n;
    long double **a;
}Matriz;

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

long double detGauss(Matriz m)
{
    long double det = 1;
    int i;

    for (i = 0; i < m.n; i++)
    {
        det = det * m.a[i][i];
    }

    return det;
}

int main(int argc, char const *argv[])
{
    Matriz a, b;
    long double det;

    CrearMat(&a, 4, 4);

    a.a[0][0] = 3;
    a.a[0][1] = 2;
    a.a[0][2] = 3;
    a.a[0][3] = -1;
    a.a[1][0] = 2;
    a.a[1][1] = 0;
    a.a[1][2] = 0;
    a.a[1][3] = 1;  
    a.a[2][0] = 3;
    a.a[2][1] = 1;
    a.a[2][2] = 3;
    a.a[2][3] = -1;
    a.a[3][0] = -3;
    a.a[3][1] = 1;
    a.a[3][2] = -2;
    a.a[3][3] = 5;

    ImpMat(a);
    printf("\n\n\n");

    b = gauss(a);

    printf("\n\n\n");
    ImpMat(b);   

    det = detGauss(b);

    printf("Le determinant des la matrix c'est: %LF", det);


    DestruirMat(a);
    DestruirMat(b);


    return 0;
}
