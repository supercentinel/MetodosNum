#include <stdio.h>
#include <math.h>

long double f(long double x)
{
    return expl(x) - (4 * x * x);
}

long double secante()
{
    int k = 1, op, ext = 0;
    long double x_k, x_kmo, x_kpo, fx_k, fx_kmo, T, E_a, E_r, E_p;

    printf("x_k-1> ");
    scanf("%LF", &x_kmo);
    printf("x_k> ");
    scanf("%LF", &x_k);
    printf("Tolerancia con respecto a:\n");
    printf("[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    do    
        scanf("%d", &op);
    while(op < 1 || op > 3);
    printf("Tolerancia> ");
    scanf("%LF", &T);

    printf("|%-4s|%-12s|%-12s|%-12s|%-12s|%-12s|%-14s|%-14s|%-16s|\n", "k", "x_kmo", "x_k", "fx_kmo", "fx_k", "x_kpo", "E_a", "E_r", "E_p");

    while (1)
    {
        fx_k = f(x_k);
        fx_kmo = f(x_kmo);

        x_kpo = x_k - ((fx_k) * ((x_kmo - x_k)/(fx_kmo - fx_k)));

        E_a = fabsl(x_k - x_kmo);
        E_r = E_a/fabsl(x_k);
        E_p = E_r * 100;

        printf("|%-4d|%-12LF|%-12LF|%-12LF|%-12LF|%-12LF|%-14LF|%-14LF|%-16LF|\n", k, x_kmo, x_k, fx_kmo, fx_k, x_kpo, E_a, E_r, E_p);

        k++;

        switch (op)
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
        if(k > 100) return 420.69;

        x_kmo = x_k;
        x_k = x_kpo;
    }

    return x_kpo;
}

int main(int argc, char const *argv[])
{
    long double raiz;

    raiz = secante();
    
    return 0;
}
