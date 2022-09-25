#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//....................................................
//Definiciones
#define MAXITERACIONES 100
#define ERROR 0.001

//....................................................
//Encabezados
void XnInicial(float* xN);
void evaluarEnFuncion(unsigned short int opcion, float xN, float* FxN);
void evaluarEnDerivadas(unsigned short int opcion, float xN, float* DFxN);
long double f_1(float xN);
long double f_2(float xN);
long double f_3(float xN);
long double f_4(float xN);
long double F_1(float xN);
long double F_2(float xN);
long double F_3(float xN);
long double F_4(float xN);
int menu_metodos();
int menu_Funciones();
void desplegarFunciones();
long double metodoNewton();
long double metodoBiseccion();
//....................................................
//Función Principal
int main(){

    //Variables
    unsigned short int opcion = 0;

    opcion = menu_metodos();

    if (opcion == 1)
    {
        metodoNewton();
    }else if (opcion == 2)
    {
        metodoBiseccion();
    }else
    {
        printf("\nERROR EN EL CODIGO\n");
    }
    
}

//....................................................
//Funciones a evaluar
void evaluarConFuncion(unsigned short int opcion, float xN, float* FxN)
{
    switch (opcion)
    {
    case 1:
        *FxN = f_1(xN);
        break;
    case 2:
        *FxN = f_2(xN);
        break;
    case 3:
        *FxN = f_3(xN);
        break;
    case 4:
        *FxN = f_3(xN);
        break;

    default:
        printf("\nERROR EN EL CODIGO\n");
        break;
    }

return;
}

long double f_1(float xN)
{
    return (((pow(xN, 2)) * (cos(xN))) - 2*xN);
}

long double f_2(float xN)
{
    return ((6-2/(pow(xN, 2))) * exp(xN+2))/(4+1);
}

long double f_3(float xN)
{
    return pow(xN,3) - (3*sin(pow(xN, 2))) + 1;
}

long double f_4(float xN)
{
    return pow(xN, 3) + (6*pow(xN,2)) + 9.4*xN + 2.5;
}

void CalcularXm(float xN, float FxN, float DFxN, float* xNmasUno){

    *xNmasUno = xN - (FxN/(DFxN));

}
//....................................................
//Derivadas de las funciones
void evaluarConDerivada(unsigned short int opcion, float xN, float* DFxN)
{
    switch (opcion)
    {
    case 1:
        *DFxN = F_1(xN);
        break;
    case 2:
        *DFxN = F_2(xN);
        break;
    case 3:
        *DFxN = F_3(xN);
        break;
    case 4:
        *DFxN = F_3(xN);
        break;

    default:
        printf("\nERROR EN EL CODIGO\n");
        break;
    }

return;
}

long double F_1(float xN)
{
    return (-pow(xN, 2)*sin(xN) + 2*xN*cos(xN) - 2);
}

long double F_2(float xN)
{
    return ( (4*(xN-2)*exp(xN+2))/(5*pow(xN, 3)) );
}

long double F_3(float xN)
{
    return (-3*xN * (2*cos(pow(xN, 2)) - xN));
}

long double F_4(float xN)
{
    return (3*pow(xN, 2) + 12*xN + 47/5);
}
//....................................................
//Menus
int menu_metodos()
{
    //Variables
    unsigned short int opcion;
    char c;

    printf("Seleccionar el método a utilizar: ");
    printf("\n[1] Método de Newton");
    printf("\n[2] Método de Biseccion");
    printf("\n--> ");

    while(!(scanf("%hu%c", &opcion, &c) == 2 && c == '\n') || (opcion < 1 || opcion > 2)){
        printf("Ingrese una opción valida.\n");
        fflush(stdin);
    }
    return opcion;
}

int menu_Funciones(){

    //Variables
    unsigned short int opcion;
    char c;

    desplegarFunciones();

    while(!(scanf("%hu%c", &opcion, &c) == 2 && c == '\n') || (opcion < 1 || opcion > 4)){
        printf("Ingrese una opción valida.\n");
        fflush(stdin);
    }
    return opcion;
}

void desplegarFunciones(){
    printf("\nSelecciona la función a evaluar: ");
    printf("\nPONER LAS FUNCIONES");
    printf("\n--> ");
}
//....................................................
//Valor Inicial
void XnInicial(float* xN){

    char c;

    printf("\nIngrese un valor x cercano a la raíz: ");
    while(!(scanf("%f%c", xN, &c) == 2 && c == '\n')){
        printf("Ingrese valores validos.\n");
        fflush(stdin);
    }

}
//....................................................
//Metodos
long double metodoNewton()
{

    //Variables
    float xN = 0, xNmasUno = 0, FxN = 0, DFxN = 0, errorRe = 1, errorAbs=1;
    int iteracion = 0;
    unsigned short int opcion = 0;

    opcion = menu_Funciones();

    do{
        XnInicial(&xN);
        evaluarConFuncion(opcion, xN, &FxN);
        printf("xN = %f, FxN = %f", xN, FxN);
    }while(FxN > 20 || FxN < -20);

    printf("\nIteración\t\txi\t\tf(xi)\t\tf'(xi)\t\tError rel\tError abs\n");

    do{
        //Paso 3
        evaluarConFuncion(opcion, xN, &FxN);
        evaluarConDerivada(opcion, xN, &DFxN);
        CalcularXm(xN, FxN, DFxN, &xNmasUno);

        //Paso 4
        if(iteracion >= 1){
            errorRe = fabs(xNmasUno - xN)/fabs(DFxN);
            errorAbs = fabs(xNmasUno - xN);
        }

        xN = xNmasUno;

        printf("%d\t\t\t%f\t%f\t%f\t%f\t%f\n", iteracion+1, xN, FxN, DFxN, errorRe, errorAbs);

        iteracion++;

    }while((errorAbs > ERROR && iteracion <= MAXITERACIONES)||(errorAbs > ERROR && iteracion <= MAXITERACIONES));

    if(errorAbs < ERROR && iteracion < MAXITERACIONES){
        printf("\n\nSe encontró la raíz xi = %f\n", xNmasUno);
    }else if(errorAbs > ERROR && iteracion < MAXITERACIONES){
        printf("\n\nHubo un error en el sistema");
    }else if(iteracion > MAXITERACIONES){
        printf("\n\nSe alcanzó el maximo número de iteraciones sin encotrar la raíz con el error tolerado.\n");
    }else{
        printf("\n\nHubo un error en el sistema.\n");
    }
}

long double metodoBiseccion()
{

}

