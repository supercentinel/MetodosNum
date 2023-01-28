Matriz jacobi(Matriz a, Matriz b)
{
    int i = 0, j = 0, k = 0, maxK = 100;
    long double tol = 0.005;

    
    Matriz sol, solk, solT, ves, ve;
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
        
        ve = prodMat(a, sol)

        printf("s\n");
        ImpMat(sol);
        printf("\n");

        if(tolerancia(solT, tol) == 1) break;

        DestruirMat(ve);
        k++;
    }

    printf("\nIteraciones totales = %d\n", k);
    
    DestruirMat(solT);
    DestruirMat(solk);

    return sol;
}