#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

    system("cls");
	
	printf("\n\t\tP1 Metodos\n\n");
	
	printf("1. Metodo de Newton\n");
	printf("2. Metodo biseccion\n");
    printf("3. Salir\n");

	printf("Opcion: ");
	scanf("%d", &opcion);
	
    return opcion;
}
int menu_funciones(char *s)
{
    int opcion;

    system("cls");

    printf("\n\t\tP1 Metodos: %s\n\n", s);
	
	printf("1. f(x) = x^2 cos(x) - 2x\n");
    printf("2. f(x) = (6 - 2/x^2)(e^2+x/4)+1\n");
    printf("3. f(x) = x^3 - 3sen(x^2) + 1\n");
    printf("4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n");
    printf("5. Salir\n");

    printf("Opcion:");
    scanf("%d", &opcion);

    return opcion;
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
    do    
        scanf("%d", &op2);
    while(op2 < 1 || op2 > 3);
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
    }
    
    return x_k;
}
long double metodoBiseccion(int opcion)
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
    }
    
    return p;
}

int main(int argc, char const *argv[])
{
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
        default:
            printf("Adios");
        break;
        }
    }while(opcion != 3);


    return 0;
}


