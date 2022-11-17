#include <stdio.h>
#include <math.h>

long double f(long double x)
{
    return ((x/2) * (x/2) * (x/2)) + (3 * sinl(x - 2));
}

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

long double pfalsa()
{
    int op, ext, k = 1;
    long double x_k, x_kmo, x_kpo, fx_k, fx_kmo, fx_kpo, T, E_a, E_r, E_p;;

    printf("x_0> ");
    scanf("%Lf", &x_kmo);
    printf("x_1> ");
    scanf("%Lf", &x_k);
    printf("Tolerancia con respecto a:\n");
    printf("[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    do    
        scanf("%d", &op);
    while(op < 1 || op > 3);
    printf("Tolerancia> ");
    scanf("%Lf", &T);

        fx_k = f(x_k);
        fx_kmo = f(x_kmo);

    if(diferenteS(fx_k, fx_kmo) == 0)
    {
        printf("No hay una raiz en el intervalo seleccionado\n");
        printf("Devolviendo numero chistoso\n");
        return 42069;
    }

    printf("|%-4s|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|%-14s|%-14s|%-16s|\n", "k", "x_k-1", "x_k", "f(x_k-1)", "f(x_k)", "x_k+1", "f(x_k+1)","Error absoluto", "Error relativo", "Error porcentual");
    
    while (1)
    {
        x_kpo = x_k - ((fx_k) * ((x_kmo - x_k)/(fx_kmo - fx_k)));
        fx_kpo = f(x_kpo);

        E_a = fabsl(x_kpo - x_k);
        E_r = E_a/fabsl(x_kpo);
        E_p = E_r * 100;

        printf("|%-4d|%-12LF|%-12LF|%-12LF|%-12LF|%-12LF|%-12LF|%-14LF|%-14LF|%-16LF|\n", k, x_kmo, x_k, fx_kmo, fx_k, x_kpo, fx_kpo, E_a, E_r, E_p);

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
        }

        if(ext == 1) break;
        if (k > 100) break;

        if(diferenteS(fx_kpo, fx_kmo) == 1)
        {
            x_k = x_kpo;
        }else
        {
            x_kmo = x_kpo;
        }

        fx_k = f(x_k);
        fx_kmo = f(x_kmo);

        k++;
    }
    
    return x_kpo;
}

int main()
{
    long double raiz;

    raiz = pfalsa();
    return 0;
}
