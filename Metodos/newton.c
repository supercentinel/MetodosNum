#include <stdio.h>
#include <math.h>

long double f(long double x)
{
    return ((x/2)*(x/2)*(x/2)) + (3 * sinl(x - 2));
}

long double F(long double x)
{
    return ((3 * (x * x))/(8)) + (3 * cosl(2 - x));
}

long double metodoNewton()
{
    int k = 0, op2, ext = 0;
    long double x_k, x_kp1, fx, fdx, T, E_a, E_r, E_p;

    printf("x_0> ");
    scanf("%Lf", &x_k);
    printf("Tolerancia con respecto a:\n");
    printf("[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    do    
        scanf("%d", &op2);
    while(op2 < 1 || op2 > 3);
    printf("Tolerancia> ");
    scanf("%Lf", &T);

    printf("|%-4s|%-12s|%-12s|%-12s|%-14s|%-14s|%-16s|\n", "k", "x_k", "f(x_k)", "f'(x_k)","Error absoluto", "Error relativo", "Error porcentual");

    while (1)
    {
        //Evalua la funicion dependiendo de la opcion

        fx = f(x_k);
        fdx = F(x_k);
        
        x_kp1 = (x_k) - ((fx)/(fdx));

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
        if(k > 100)
        {
            printf("Algo salio mal, intenta en otros valores\n");
            printf("Devolviendo numero chistoso\n");
            return 42069;
        }
    }
    
    return x_k;
}

int main()
{
    long double raiz;

    raiz = metodoNewton();

    printf("Raiz en: %LF\n", raiz);
    
    return 0;
}
