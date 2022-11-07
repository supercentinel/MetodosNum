#include <stdio.h>
#include <stdlib.h>

 typedef struct 
{
  

    //de m renglones y n columnas
  int m, n;
   

long double **a;
 

} Matriz;

 
 
void 
CrearMat (Matriz * a, int n) 
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
 
void 


fillmatrix (Matriz * a) 
{
  
 
printf ("\n\n\t\tIngresa el dato para la posicion ");
  
 
for (int i = 0; i < a->m; i++)
    
 
    {
      
 
for (int j = 0; j < a->n; j++)
	
 
	{
	  
 
printf ("\n\t [%d,%d]  : ", i, j);
	  
 
scanf ("%Lf", &a->a[i][j]);

 
} 
} 
} 
 
void 


printmatrix (Matriz * a) 
{
printf ("\n\n");
for (int i = 0; i < a->m; i++)
    {
printf ("\n");
      
 
for (int j = 0; j < a->m; j++)
	
 
printf ("\t%Lf", a->a[i][j]);
      
 
printf ("\t");
    
 
} 
printf ("\n");

 
} 
 
 
void

chequeo (Matriz * a)
{
  
int op, fila, columna;
op=0;
while(op==0){
  printmatrix(a);
 
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


 
 
 
void 
ImpMat (Matriz m) 
{
  
 
int i, j;
  
 printf ("\n\n");
 
for (i = 0; i < m.m; i++)
    
 
    {
      
 
for (j = 0; j < m.n; j++)
	
 
	{
	  
 
printf ("\t%LF ", m.a[i][j]);
	
 
}
      
 
printf ("\n");
    
 
}

 
}


 
 
 
Matriz gauss (Matriz m) 
{
  
 
int i, j, k;
  
 
long double fm, r_1, r_2;
  
 
 
Matriz d;
  
 
 
if (m.m != m.n)
    
return d;
  
 
 
CrearMat (&d, m.n);
  
 
 
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

void solucion(){
    
}
 
 
 
int 
main (int argc, char const *argv[]) 
{
  
 
Matriz a, b;
  
 
long double det;
int dimension;

printf ("\n\n\n\t\t \t\tCALCULO DE SOLUCIONES PARA UN SISTEMA DE ECUACIONES NXN  :  ");
printf ("\n\n \t\tPROPOSITO:  ");
        printf ("\n\t\t\t Recibe una matriz nxn la cual representa un sistema de ecuaciones que se pretenda tenga\n\t\t\t solución única si el determinante es diferente de 0, para esto inicialmente\n\t\t\t te pedimos llenar una matriz de cuadrada de dimensión n. Revisamos que la escritura\n\t\t\t de la matriz haya sido correcta y calculamos el determinante y si es distinto\n\t\t\t a 0 te damos la solución a cada una de las incógnitas. ;)  ");


printf ("\n\n \t\tINTEGRANTES:  ");
printf ("\n \t\t\t ---  Ceron Chavez Alan ");
printf ("\n \t\t\t ---  Fernandez Castaxeda Alexia ");
printf ("\n \t\t\t ---  Tovar Salazar Karla Abigail ");

system("pause & cls");

printf ("\n\n\n \t\tIngresa la dimension de la matriz  :  ");
  
 
scanf ("%d", &dimension);
  
 
 
CrearMat (&a, dimension);
  
 
fillmatrix (&a);
system("cls");  
 
 printf("\n\n\t\t\t\t\tRevimemos que la matriz sea correcta \n");
chequeo (&a);
  
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
     solucion();
 }
 
 
DestruirMat (a);
  
 
DestruirMat (b);
  
 
 
 
return 0;

 
}
