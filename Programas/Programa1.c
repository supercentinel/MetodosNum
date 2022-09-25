#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Funciones a evaluar
long double f_1(long double x)
{
    return ((x * x) * (cosl(x)))-(2 * x);
}

long double f_2(long double x)
{
    
}

long double f_3()
{
    
}

long double f_4()
{
    
}
//Derivadas de las funciones
long double F_1(long double x)
{
    return ((x*x) * (-sinl(x)))+(2 * x * cosl(x)) - 2;
}

long double F_2()
{
    
}

long double F_3()
{
    
}

long double F_4()
{
    
}
//Menus
int menu_metodos()
{
    int opcion;



}
int menu_funciones()
{

}
//Metodos
long double metodoNewton(int opcion)
{
    int k = 0, op2, ext = 0;
    long double x_k, x_kp1, fx, fdx, T, E_a, E_r, E_p;

    printf("x_0> ");
    scanf("%Lf", &x_k);
    printf("Tolerancia con respecto a:\n");
    printf("[1]Error absoluto [2]Error relativo [3]Error porcentual\n");
    scanf("%d", &op2);
    printf("Tolerancia> ");
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
        //printf("\nAqui si\n");
        
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

        x_k = x_kp1;
        k++;
        if(ext == 1) break;
    }
    
}
long double metodoBiseccion()
{

}

int main(int argc, char const *argv[])
{
    metodoNewton(1);


    return 0;
}


