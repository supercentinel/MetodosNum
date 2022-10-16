#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct 
{
    //de m renglones y n columnas
    int m, n;
    long double **a;
}Matriz;
typedef struct
{
    int grado;
    long double *c;
}Polinomio;
void CrearPol(Polinomio *p, int grado)
{
    p->grado = grado;
    p->c = (long double *)calloc(grado + 1, sizeof(long double));
}
void DestruirPol(Polinomio p)
{
    p.c = NULL;
    free(p.c);
}
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
//Unicamente para matrices de 2x2. El retrasado que programa esto se saltó Álgebra Superior
long double MatDet(Matriz m)
{
    return (m.a[0][0] * m.a[1][1]) - (m.a[0][1] * m.a[1][0]);
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
Matriz MatAdj(Matriz m)
{
    Matriz adj;

    CrearMat(&adj, m.m, m.n);

    adj.a[0][0] = +m.a[1][1];
    adj.a[0][1] = -m.a[1][0];
    adj.a[1][0] = -m.a[0][1];
    adj.a[1][1] = +m.a[0][0];

    return adj;
}
//El determinante como parametro es para comprobar si tiene inversa ya que si det = 0 -> mat^-1 /E
Matriz MatInv(Matriz m, long double det)
{
    Matriz Inv, t, adj;

    CrearMat(&Inv, m.m, m.n);

    t = MatT(m);
    adj = MatAdj(t);

    Inv = ProdEs(adj, 1/det);

    DestruirMat(t);
    DestruirMat(adj);

    return Inv;
}

long double MetodoBaristow(Polinomio p, long double r, long double s, double tolerancia)
{
    int i, k = 0;   
    double err_rp, err_sp;
    long double nu_r = r, nu_s = s;
    //division sintetica
    Matriz divisionS, mat_c, mat_b, mat_prod, mat_inv;

    CrearMat(&divisionS, 7, p.grado + 2);
    CrearMat(&mat_c, 2, 2);
    CrearMat(&mat_b, 2, 1);

    divisionS.a[1][0] = nu_r;
    divisionS.a[2][0] = nu_s;
    divisionS.a[4][0] = nu_r;
    divisionS.a[5][0] = nu_s;

    while(1)
    {
        for (i = 0; i < p.grado + 1; i++)
        {
            divisionS.a[0][i+1] = p.c[i];
        }

        for ( i = 0; i < p.grado + 1; i++)
        {
            if(i + 1 > 1)
            {
                divisionS.a[1][i+1] = divisionS.a[1][0] * divisionS.a[3][i];
            }
            if(i + 1 > 2)
            {
                divisionS.a[2][i+1] = divisionS.a[2][0] * divisionS.a[3][i-1];
            }

            divisionS.a[3][i+1] = divisionS.a[0][i+1] + divisionS.a[1][i+1] + divisionS.a[2][i+1]; 
        }

        for ( i = 0; i < p.grado; i++)
        {
            if (i+1 > 1)
            {
                divisionS.a[4][i+1] = divisionS.a[4][0] * divisionS.a[6][i];
            }
            if (i+1 > 2)
            {
                divisionS.a[5][i+1] = divisionS.a[5][0] * divisionS.a[6][i-1];
            }

            divisionS.a[6][i+1] = divisionS.a[3][i+1] + divisionS.a[4][i+1] + divisionS.a[5][i+1];
        }

        mat_c.a[0][0] = divisionS.a[6][(p.grado + 1) - 2];
        mat_c.a[1][0] = divisionS.a[6][p.grado];
        mat_c.a[0][1] = divisionS.a[6][(p.grado + 1) - 3];
        mat_c.a[1][1] = divisionS.a[6][(p.grado + 1) - 2];

        mat_b.a[0][0] = -divisionS.a[3][p.grado];
        mat_b.a[1][0] = -divisionS.a[3][p.grado + 1];

        mat_inv = MatInv(mat_c, MatDet(mat_c));

        mat_prod = ProdMat(mat_inv, mat_b);

        DestruirMat(mat_inv);
        
        //ImpMat(mat_prod);

        err_rp = fabs((mat_prod.a[0][0])/(r)) * 100;
        err_sp = fabs((mat_prod.a[1][0])/(s)) * 100;

        k++;

        if(err_rp <= tolerancia && err_sp <= tolerancia) break;
        if(k > 100) break;

        nu_r = nu_r + mat_prod.a[0][0];
        nu_s = nu_s + mat_prod.a[1][0];

        DestruirMat(mat_prod);//temp
        
        divisionS.a[1][0] = nu_r;
        divisionS.a[2][0] = nu_s;
        divisionS.a[4][0] = nu_r;
        divisionS.a[5][0] = nu_s;

    }

    printf("r = %LF\n", nu_r);
    printf("s = %LF\n", nu_s);

    printf("Error porcentual de r = %lf\n", err_rp);
    printf("Error porcentual de s = %lf\n", err_sp);
    printf("Iteraciones = %d", k);
    

    DestruirMat(mat_prod);
    DestruirMat(mat_c);
    DestruirMat(mat_b);
    DestruirMat(divisionS);
}

int main()
{
    Polinomio p;
    long double r, s, yt;
    double tolerancia = 5.0;

    CrearPol(&p, 3);

    r = -0.5;
    s = 0.5;

    p.c[0] = 1;
    p.c[1] = -4;
    p.c[2] = 5.25;
    p.c[3] = -2.5;

    yt = MetodoBaristow(p, r, s, tolerancia);


    DestruirPol(p);

    return 0;
}
