#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_IT 100

//Funcion para comparar signos usada en biseccion
int diferenteS(long double a, long double b)
{
    if ((((a > 0)) && ((b < 0)))  || (((a < 0)) && ((b > 0))))
    {
        return 1;
    }else
    {
        return 0;
    }
}
//Funciones a evaluar
long double f_1(long double x)
{
    return ((x * x) * (cosl(x)))-(2 * x);
}

long double f_2(long double x)
{
    return ((6)-((2)/(x * x))) * ((exp2l(2+x))/(4)) + (1);
}

long double f_3(long double x)
{
    return (x * x * x) - (3 * sinl(x * x)) + (1);
}

long double f_4(long double x)
{
    return (x * x * x)+(6 * x * x)+(9.4 * x)+(2.5);
}
//Derivadas de las funciones
long double F_1(long double x)
{
    return ((x*x) * (-sinl(x)))+(2 * x * cosl(x)) - 2;
}

long double F_2(long double x)
{
    return ((exp2l(2+x)) * ((3 * x * x * x)-(x)+(2)))/(2 * x * x * x);
}

long double F_3(long double x)
{
    return (3 * x) * ((x)-(2 * cosl(x *x)));
}

long double F_4(long double x)
{
    return (3 * x * x)+(12 * x)+(9.4);
}
//Menus
int menu_metodos()
{
    int opcion;

    system("cls");
	
	printf("\n\t\t\t\tQue deseas hacer hoy?\n\n");
	
	printf("\t\t1. Metodo de Newton: costoso pero eficiente\n");
	printf("\t\t2. Metodo biseccion: tan sencillo y bonito \n");
	printf("\t\t3. Desde inversa a solucion de sistema de ecuacione \n");
	printf("\t\t4. Valores Propios: hasta parece magia \n");
    printf("\t\t\t\t5. Salir\n\n\n");

	printf("\t\t\t\tOpcion: ");
	scanf("%d", &opcion);
	
    return opcion;
}
int menu_funciones(char *s)
{
    int opcion;

    system("cls");

    printf("\n\n\t\t\t\tP1 Metodos: %s\n\n", s);
	
	printf("\t\t1. f(x) = x^2 cos(x) - 2x\n");
    printf("\t\t2. f(x) = (6 - 2/x^2)(e^2+x/4)+1\n");
    printf("\t\t3. f(x) = x^3 - 3sen(x^2) + 1\n");
    printf("\t\t4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n");
    printf("\t\t\t\t5. Salir\n");

    printf("\n\n\t\t\t\tOpcion:");
    scanf("%d", &opcion);

    return opcion;
}
//Metodos
long double metodoNewton(int opcion)
{
    int k = 0, op2, ext = 0;
    long double x_k, x_kp1, fx, fdx, T, E_a, E_r, E_p;

    printf("\n\n\t\tx_0> ");
    scanf("%Lf", &x_k);
    printf("\n\t\tTolerancia con respecto a:\n");
    printf("\n\t\t[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    printf("\n\t\t\t\t\t:");
    do    
        scanf("%d", &op2);
    while(op2 < 1 || op2 > 3);
    printf("\n\t\tTolerancia> ");
    scanf("%Lf", &T);

    printf("|%-4s|%-12s|%-12s|%-12s|%-14s|%-14s|%-16s|\n", "k", "x_k", "f(x_k)", "f'(x_k)","Error absoluto", "Error relativo", "Error porcentual");

    while (1)
    {
        //Evalua la funicion dependiendo de la opcion
        switch (opcion)
        {
        case 1:
            fx = f_1(x_k);
            fdx = F_1(x_k);
        break;
        case 2:
            fx = f_2(x_k);
            fdx = F_2(x_k);
        break;
        case 3:
            fx = f_3(x_k);
            fdx = F_3(x_k);
        break;
        case 4:
            fx = f_4(x_k);
            fdx = F_4(x_k);
        break;
        }
        
        x_kp1 = (x_k)-((fx)/(fdx));

        E_a = fabsl(x_kp1 - x_k);
        E_r = E_a/fabsl(x_kp1);
        E_p = E_r * 100;

        printf("|%-4d|%-12Lf|%-12Lf|%-12Lf|%-14Lf|%-14Lf|%-16Lf|\n", k, x_k, fx, fdx, E_a, E_r, E_p);    

        switch (op2)
        {
        case 1:
            if(E_a < T) ext = 1;
        break;
        case 2:
            if(E_r < T) ext = 1;
        break;
        case 3:
            if(E_p < T) ext = 1;
        break;
        default:
        break;
        }

        if(ext == 1) break;
        
        x_k = x_kp1;
        k++;
        if(k > MAX_IT)
        {
            printf("Algo salio mal, intenta en otros valores\n");
            printf("Devolviendo numero chistoso\n");
            return 42069;
        }
    }
    
    return x_k;
}
long double metodoBiseccion(int opcion)
{
    int k = 0, op2, ext = 0;
    long double a, b, p = 0, p_Nm1 = 0, fa, fb, fp, T, E_a, E_r, E_p;
    printf("\n\n\t\t\t\tIngeresa el valor inicial");
    printf("\n\n\t\ta> ");
    scanf("%Lf", &a);
    printf("\n\n\t\t\t\tIngeresa el valor final");
    printf("\n\t\tb> ");
    scanf("%Lf", &b);
    printf("\n\t\t\t\t\t\tTolerancia con respecto a:\n");
    printf("\n\t\t[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    printf("\n\t\t\t\t\t\t:");
    do    
        scanf("%d", &op2);
    while(op2 < 1 || op2 > 3);
    printf("\n\n\t\t\t\tTolerancia> ");
    scanf("%Lf", &T);

    switch (opcion)
        {
        case 1:
            fa = f_1(a);
            fb = f_1(b);
            fp = f_1(p);
        break;
        case 2:
            fa = f_2(a);
            fb = f_2(b);
            fp = f_2(p);
        break;
        case 3:
            fa = f_3(a);
            fb = f_3(b);
            fp = f_3(p);
        break;
        case 4:
            fa = f_4(a);
            fb = f_4(b);
            fp = f_4(p);
        break;
        }

    if(diferenteS(fa, fb) == 0)
    {
        printf("No hay una raiz en el intervalo seleccionado\n");
        printf("Devolviendo numero chistoso\n");
        return 42069;
    }

    printf("|%-4s|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|%-14s|%-14s|%-16s|\n", "k", "a", "b", "f(a)", "f(b)", "p", "f(p)","Error absoluto", "Error relativo", "Error porcentual");

    while (1)
    {
        p_Nm1 = p;
        p = (a+b)/2;
        //Evalua la funicion dependiendo de la opcion
        switch (opcion)
        {
        case 1:
            fa = f_1(a);
            fb = f_1(b);
            fp = f_1(p);
        break;
        case 2:
            fa = f_2(a);
            fb = f_2(b);
            fp = f_2(p);
        break;
        case 3:
            fa = f_3(a);
            fb = f_3(b);
            fp = f_3(p);
        break;
        case 4:
            fa = f_4(a);
            fb = f_4(b);
            fp = f_4(p);
        break;
        }

        E_a = fabsl(p -p_Nm1);
        E_r =  E_a/fabsl(p);
        E_p = E_r * 100;        

        printf("|%-4d|%-12Lf|%-12Lf|%-12Lf|%-12Lf|%-12Lf|%-12Lf|%-14Lf|%-14Lf|%-16Lf|\n", k, a, b, fa, fb, p, fp, E_a, E_r, E_p);
        
        switch (op2)
        {
            case 1:
                if(E_a < T) ext = 1;
            break;
            case 2:
                if(E_r < T) ext = 1;
            break;
            case 3:
                if(E_p < T) ext = 1;
            break;
        }

        if(ext == 1) break;

        if(diferenteS(fa, fp) == 1)
        {
            b = p;
        }else
        {
            a = p;
        }

        k++;
        if(k > MAX_IT)
        {
            printf("Algo salio mal, intenta en otros valores\n");
            printf("Devolviendo numero chistoso");
            return 42069;
        }
    }
    
    return p;
}

//////////matrices 3 y 4
 typedef struct 
{   //de m renglones y n columnas
  int m, n;
long double **a;
} Matriz;

void 
aCrearVec (Matriz * a, int n) 
{
int i;
a->m = 1;
a->n = n;
a->a = (long double **) calloc (n, sizeof (long double *));
for (i = 0; i < n; i++)
    {
a->a[i] = (long double *) calloc (n, sizeof (long double));
} 
} 


void CrearMat(Matriz *a,int m ,int n);
void aCrearMat (Matriz * a, int n) 
{
int i;
a->m = n;
a->n = n;
a->a = (long double **) calloc (n, sizeof (long double *));
for (i = 0; i < n; i++)
    {
      
 
a->a[i] = (long double *) calloc (n, sizeof (long double));
} 
} 
 
 
void afillmatrix (Matriz * a) 
{
printf ("\n\n\t\t\t\tIngresa el dato para la posicion ");
for (int i = 0; i < a->m; i++)
    {
for (int j = 0; j < a->n; j++)
	{
printf ("\n\t \t\t[%d,%d]  : ", i, j);
scanf ("%Lf", &a->a[i][j]);

} 
} 
} 

Matriz afillnew(Matriz a){
    
    Matriz c;
    aCrearMat(&c,a.m);
	for (int i = 0; i < a.m; i++)
    {
		for (int j = 0; j < a.n; j++)
	{
		if (i==j){
			c.a[i][j]=0;
		}else{
				c.a[i][j]=a.a[i][j]/a.a[i][i];
		}

		} 
	} 
	return c;	
}
 

void 
aprintmatrix (Matriz * a) 
{
printf ("\n\n");
for (int i = 0; i < a->n; i++)
    {
printf ("\n");

for (int j = 0; j < a->m; j++)
	
printf ("\t%Lf", a->a[j][i]);
printf ("\t");

} 
printf ("\n");

 
} 
 
void
achequeo (Matriz * a)
{
  
int op, fila, columna;
op=0;
while(op==0){
  aprintmatrix(a);
 
printf ("\n\n\t\tSon todos los datos correctos? ");
  
printf ("\n\n\tPresiona 1 si son correctos ");
  
printf ("\n\n\tPresiona 0 si son incorrectos ");
  
printf ("\n\n\t\t\t :  ");
  
scanf ("%d", &op);
  
 
if (op == 0)
    {
      
printf ("\n\n\tIngresa la fila en la que se encuentra  : ");
      
scanf ("%d", &fila);
      
printf ("\n\n\tIngresa la columna que esta mal  : ");
      
scanf ("%d", &columna);
      
printf ("\n\n\tIngresa el dato para [%d,%d]  :  ", fila, columna);
      
scanf ("%Lf", &a->a[fila][columna]);
    }    
}

}

void 
DestruirMat (Matriz a) 
{
  
 
int i, j;
  
 
 
for (i = 0; i < a.m; i++)
    
 
    {
      
 
a.a[i] = NULL;
      
 
free (a.a[i]);
    
 
}
  
 
a.a = NULL;
  
 
free (a.a);

 
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

void ImpMat(Matriz M);

Matriz gauss (Matriz m) 
{
int i, j, k;
long double fm, r_1, r_2;
Matriz d;
  
 
 
if (m.m != m.n)
    
return d;
  
 
 
aCrearMat (&d, m.n);
  
 
 
for (i = 0; i < m.n; i++)
    
 
    {
      
 
for (j = 0; j < m.m; j++)
	
 
	{
	  
 
d.a[i][j] = m.a[i][j];
	
 
}
    
 
}
  
 
 
for (k = 0; k < d.n - 1; k++)
    
 
    {
      
 
for (i = k + 1; i < d.n; i++)
	
 
	{
fm = -((d.a[i][k]) / (d.a[k][k]));
for (j = k; j < d.m; j++)
	    {

r_1 = (d.a[k][j]);
r_2 = (d.a[i][j]);
d.a[i][j] = ((fm) * (r_1)) + (r_2);
}
}
}
return d;
}

long double 
detGauss (Matriz m) 
{
long double det = 1;
int i;
for (i = 0; i < m.n; i++)
    {
    det = det * m.a[i][i];
    }
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
void solucion(Matriz a){
    Matriz vec;
    Matriz c;
    float tolerancia;
    int iteraciones=0;
    int e=0;
    printf("\n\n\t\tResulta que tiene condiciones para tener soluciones unicas :) \n");
    printf("\n\n\t\tRevisamos que sea EDD .........\n");
    
    e=esEDD(a);
    if (e==0){
        printf("\n\n\t\tSi es EDD, vamos al siguente paso \n");
       printf("\n\n\t\tVamos a llenar el vector que llevara los puntos dados \n");
    aCrearVec(&vec,a.n);
    afillmatrix(&vec);

     printf("\n\n\t\t\t\t\tRevimemos que el vector sea correcto \n");
achequeo (&vec);
 printf("\n\n\t\t Finalmente tu vector es : \n");

aprintmatrix (&a);

 printf("\n\n\t\t Ingresa la tolerancia de la solucion : \n");
 scanf("%f",&tolerancia);
 printf("\n\n\t\t Ingresa el maximo de iteraciones a realizar : \n");
 scanf("%d",&iteraciones);
system("pause & cls"); 
    aCrearMat(&c,a.m);
    c=afillnew(a);
    ImpMat(c);
    DestruirMat(vec);
     
    }
    else{
        printf("\n\n\t\t Lo sentimos no es EDD \n");
    }
        
}

void opmatriz(){
    Matriz a, b;
long double det;
int dimension;

printf ("\n\n\n\t\t \t\tCALCULO DE SOLUCIONES PARA UN SISTEMA DE ECUACIONES NXN  :  ");
printf ("\n\n \t\tPROPOSITO:  ");
        printf ("\n\t\t\t Recibe una matriz nxn la cual representa un sistema de ecuaciones que se pretenda tenga\n\t\t\t solución única si el determinante es diferente de 0, para esto inicialmente\n\t\t\t te pedimos llenar una matriz de cuadrada de dimensión n. Revisamos que la escritura\n\t\t\t de la matriz haya sido correcta y calculamos el determinante y si es distinto\n\t\t\t a 0 te damos la solución a cada una de las incógnitas. ;)  ");

printf ("\n\n\n \t\tIngresa la dimension de la matriz  :  ");
  
scanf ("%d", &dimension);
aCrearMat (&a, dimension);
afillmatrix (&a);
system("cls");  
 printf("\n\n\t\t\t\t\tRevimemos que la matriz sea correcta \n");
achequeo (&a);
 printf("\n\n\t\t Finalmente tu matriz es : \n");

ImpMat (a);
system("pause & cls"); 
 
printf ("\n\n\n");
b = gauss (a);
printf ("\n\n\n");
printf ("\n\n\n\t\t\t\tHemos calculado la matriz triangular \n\n");
ImpMat (b);
det = detGauss (b);
printf ("El determinante de nuestra matriz es  : %LF", det);
  
 if (det!=0){
     solucion(a);
 }
DestruirMat (a);
DestruirMat (b);
}



//ejercicio 4


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


void Valores(){
	
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

    printf("\n\t\tsi es 0 = %d, es EDD", esEDD(a));
    printf("\n\t\tDeterminante es: %LF\n", detGauss(a));
    
    ImpMat(b);

    printf("\n\t\t\t\tLa solucion es\n");

    s = jacobi(a, b);

    ImpMat(s);

    DestruirMat(s);
    DestruirMat(b);
    DestruirMat(a);
}


////Ejercicio 5


void CrearMat(Matriz *a,int m ,int n);
void DestruirMat(Matriz a);
void ImpMat(Matriz m);

Matriz ProdMat(Matriz a, Matriz b);
Matriz ProdEs(Matriz a, long double b);
Matriz MatT(Matriz m);

long double maxElmt(Matriz a);

typedef struct 
{
    long double c;
    long double r;
}Circulo;

Circulo* CirculosDeGerschgorin(Matriz a)
{
    Circulo *circulos;
    int i, j, sum = 0;

    if((circulos = (Circulo *)calloc(a.n, sizeof(Circulo))) == NULL) return NULL;
    
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
        printf("\t\tlambda  = %LF error = %LF k = %d\n\n", lamda, err, k);
        xkp1 = ProdEs(axk, 1/lamda);

        for (i = 0; i < xk.m; i++)
        {
            xk.a[i][0] = xkp1.a[i][0];
        }
        printf("\n\t\t\tAx^k:\n");
        ImpMat(axk);
        printf("\n\t\t\tx^k+1:\n");
        ImpMat(xkp1);

        DestruirMat(xkp1);
        DestruirMat(axk);
        k++;
    }
    
    DestruirMat(xk);

    return lamda;
}


int potencia()
{
    Matriz a;
    
    Circulo *circulos;
    int n,i, it;
    long double lambdaMax;
    float e;
    
    printf("\n\n\t\tIngresa la dimension de la matriz: ");
    scanf("%d",&n );

    CrearMat(&a, n, n);
    
    afillmatrix(&a);
    aprintmatrix(&a);

   
    circulos = CirculosDeGerschgorin(a);

    for (i = 0; i < a.n; i++)
    {
        printf("\n\t\t\tCirculo [i]: c = %LF r = %LF\n", circulos[i].c, circulos[i].r);
    }
    
    printf("\n\n\t\t\tNumero de iteraciones maximas:  ");
    scanf("%d", &it);
    
    printf("\n\n\t\t\tMargen de error:  ");
    scanf("%f", &e);
    
    lambdaMax = MPotencias(a, e, it);

    printf("\nEl valor propio maximo es %LF\n", lambdaMax);

    free(circulos);
    DestruirMat(a);
    system ("pause");
    return 0;
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



 
int main(int argc, char const *argv[])
{
    
	printf("\n \n************************************************************************************\n");
	printf("\n \t \t  Universidad Nacional Autonoma de Mexico\n");
	printf("\n \t \t \t Matematicas Aplicadas y Computacion\n");
	printf("\n \t \t \t\t Metodos Numericos    \n");
	printf("\n \t \t \t\t Profesor:  \n");
	printf("\n \t \t \t Carrillo Teresa\n\n");
	printf("\n \t \t \t \t\tPROYECTO FINAL    \n");
	printf ("\n\n \t\tINTEGRANTES:  ");
	printf ("\n \t\t\t ---  Ceron Chavez Alan \n");
	printf ("\n \t\t\t ---  Fernandez Castaxeda Alexia \n");
	printf ("\n \t\t\t ---  Tovar Salazar Karla Abigail\n\n\n ");
	printf("\n ************************************************************************************\n");


system("pause & cls");
    int opcion, opcion2;
    long double raiz;

    do
    {
        opcion = menu_metodos();
        switch (opcion)
        {
        case 1:
            do
            {
                opcion2 = menu_funciones("Metodo Newton");

                switch (opcion2)
                {
                case 1:
                    raiz = metodoNewton(1);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 2:
                    raiz = metodoNewton(2);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 3:
                    raiz = metodoNewton(3);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 4:
                   raiz = metodoNewton(4);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");
                break;
                
                
                default:
                break;    
                }
            } while (opcion2 != 5);
        break;
        case 2:
            do
            {
                opcion2 = menu_funciones("Metodo Biseccion");

                switch (opcion2)
                {
                case 1:
                    raiz = metodoBiseccion(1);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 2:
                    raiz = metodoBiseccion(2);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 3:
                    raiz = metodoBiseccion(3);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                case 4:
                    raiz = metodoBiseccion(4);
                    printf("Raiz aproximada en: %Lf\n", raiz);
                    system("pause");  
                break;
                default:
                break;   
               }
            } while (opcion2 != 5);
        break;
        case 3:
        opmatriz();
        break;
        
        case 4:
        potencia();
        break;
        
        default:
            printf("Adios");
        break;
        }
    }while(opcion != 5);


    return 0;
}




