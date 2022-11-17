#include <stdio.h>
#include <math.h>

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

//Funcion a encontrar raiz
long double f(long double x)
{
    return ((x/2) * (x/2) * (x/2)) + (3 * sinl(x - 2));
}

long double metodoBiseccion()
{
    int k = 0, op2, ext = 0;
    long double a, b, p = 0, p_Nm1 = 0, fa, fb, fp, T, E_a, E_r, E_p;

    printf("a> ");
    scanf("%Lf", &a);
    printf("b> ");
    scanf("%Lf", &b);
    printf("Tolerancia con respecto a:\n");
    printf("[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    do    
        scanf("%d", &op2);
    while(op2 < 1 || op2 > 3);
    printf("Tolerancia> ");
    scanf("%Lf", &T);

        fa = f(a);
        fb = f(b);
        fp = f(p);

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

        fa = f(a);
        fb = f(b);
        fp = f(p);

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
        if(k > 100)
        {
            printf("Algo salio mal, intenta en otros valores\n");
            printf("Devolviendo numero chistoso");
            return 42069;
        }
    }
    
    return p;
}

int main(int argc, char const *argv[])
{
    long double raiz;

    raiz = metodoBiseccion();

    return 0;
}
