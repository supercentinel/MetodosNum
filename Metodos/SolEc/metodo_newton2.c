#include <stdio.h>
#include <math.h>

double F(double x)
{
  return ((50+((37.49)/(x*x)))*((x)-(0.197))) - 28.5657075;
}

double Fdx(double x)
{
  return ((50*((x*x*x)-(0.7498 * x)+(0.295421)))/(x*x*x));
}


int main(void) 
{
  int k;
  double x_k, fx, fdx, E, E_a, E_r, Ep;

  printf("x_0> ");
  scanf("%lf", &x_k);
  printf("E> ");
  scanf("%lf", &E);

  printf("|%-4s|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "k","x_k", "f(x_k)", "f'(x_k)", "E_a", "E_r", "E_%");

  while(1)
  {
    printf("|%-4d", k);
    printf("|%-12lf", x_k);
    fx = F(x_k);
    printf("|%-12lf", fx);
    fdx = Fdx(x_k);
    printf("|%-12lf", fdx);
    E_a = fabs(E - fx);
    printf("|%-12lf", E_a);
    E_r = (E_a)/(fabs(fx));
    printf("|%-12lf|\n", E_r);
    if(fabs(fx) < E)
      break;
    x_k = (x_k) - ((fx)/(fdx));
    k++;
  }
  printf("Raiz aproximada> %lf\n", x_k);
  printf("Numero de iteraciones> %d\n", k);
  return 0;
}