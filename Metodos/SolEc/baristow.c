#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct 
{
    long double r;
    long double i;
}Complejo;


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
Complejo raiz(long double r, long double s, int op)
{
    Complejo q;
    long double d = (r * r) - ( 4 * s);
    printf("%LF\n", d);
    if(op == 1)
    {
        if (d > 0)
        {
            q.r = -((r + sqrtl(d))/(2));
            q.i = 0;
        }
        else
        {
            q.r = -r/2;
            q.i = sqrtl(-d)/2;
        }
    }else
    {
        if (d > 0)
        {
            q.r = -((r - sqrtl(d))/(2));
            q.i = 0;
        }
        else
        {
            q.r = -r/2;
            q.i = -(sqrtl(-d)/2);
        }
    }

    return q;
}


Complejo * MetodoBaristow(Polinomio p, long double r, long double s, double tolerancia)
{
    int i, k = 0;   
    double err_rp, err_sp;
    long double nu_r = r, nu_s = s;
    //Complejo rz_1, rz_2, rz_3, rz_4;
    Complejo * raices;

    raices = calloc(p.grado, sizeof(Complejo));
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

        printf("\n");
        ImpMat(divisionS);
        printf("\n");

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
        err_rp = fabs((mat_prod.a[0][0])/(nu_r)) * 100;
        err_sp = fabs((mat_prod.a[1][0])/(nu_s)) * 100;

        k++;
        
        if(err_rp <= tolerancia && err_sp <= tolerancia) break;
        if(k > 100) break;
        
        nu_r = nu_r + mat_prod.a[0][0];
        nu_s = nu_s + mat_prod.a[1][0];

        printf("r = %LF\n", nu_r);
        printf("s = %LF\n", nu_s);
        
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
    printf("Iteraciones = %d\n", k);

    //ImpMat(divisionS);

    printf("\nasd = %LF\n", divisionS.a[3][3]);

    raices[0] = raiz(-nu_r, -nu_s, 1);
    raices[1] = raiz(-nu_r, -nu_s, 0);

    raices[2] = raiz(divisionS.a[3][2], divisionS.a[3][3], 1);
    raices[3] = raiz(divisionS.a[3][2], divisionS.a[3][3], 0);

    /*
    printf("\nRaiz en: %LF %LFi\n", rz_1.r, rz_1.i);
    printf("\nRaiz en: %LF %LFi\n", rz_2.r, rz_2.i);
    printf("\nRaiz en: %LF %LFi\n", rz_3.r, rz_3.i);
    printf("\nRaiz en: %LF %LFi\n", rz_4.r, rz_4.i);
    //printf("\nRaiz en: %LF %LFi\n", rz_3.r, rz_3.i);
    */
    //printf("\nRaiz en: %LF", );
    /*
    for ( i = 0; i < p.grado/2; i++)
    {
        if (i%2 == 0)
        {
            raices[i] = raiz(nu_r, nu_s);
            raices[i+1].r = raices[i].r;
            raices[i+1].i = -raices[i].i;
        }else
        {
            raices[i] = raiz(-divisionS.a[3][2], -divisionS.a[3][3]);
            raices[i+2].r = raices[i+1].r;
            raices[i+2].i = -raices[i+1].i;
        }
        
    }
    */
    
    printf("\nRaiz en: %LF %LFi\n", raices[0].r, raices[0].i);
    printf("\nRaiz en: %LF %LFi\n", raices[1].r, raices[1].i);
    printf("\nRaiz en: %LF %LFi\n", raices[2].r, raices[2].i);
    printf("\nRaiz en: %LF %LFi\n", raices[3].r, raices[3].i);

    DestruirMat(mat_prod);
    DestruirMat(mat_c);
    DestruirMat(mat_b);
    DestruirMat(divisionS);

    return raices;
}

int main()
{
    Complejo *ls;
    Polinomio p;
    long double r, s;
    double tolerancia = 0.00008;

    CrearPol(&p, 4);

    r = -1;
    s = 2;

    p.c[0] = 1;
    p.c[1] = 4.5;
    p.c[2] = 2;
    p.c[3] = -4.5;
    p.c[4] = -18;

    MetodoBaristow(p, r, s, tolerancia);



    DestruirPol(p);
    free(ls);
    return 0;
}
