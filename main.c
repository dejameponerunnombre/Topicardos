#include "funciones.h"

int ComparaFechaYClasiArchivo(void*v1, void*v2)
{
    if(((Archivo*)v1)->fecha.a == ((Archivo*)v2)->fecha.a && ((Archivo*)v1)->fecha.m == ((Archivo*)v2)->fecha.m &&((Archivo*)v1)->fecha.d == ((Archivo*)v2)->fecha.d) // si coinciden en mes y anio pero v1 es mas nuevo por dias
    {
        if(!mi_strcmp(((Archivo*)v2)->Clasificador,"Items"))
            return 1;
        else
            return -1;
    }
    if(((Archivo*)v1)->fecha.a > ((Archivo*)v2)->fecha.a)
        return -1;
    else if(((Archivo*)v1)->fecha.a < ((Archivo*)v2)->fecha.a)
        return 1;
    else if((((Archivo*)v1)->fecha.a == ((Archivo*)v2)->fecha.a) && (((Archivo*)v1)->fecha.m > ((Archivo*)v2)->fecha.m))
        return -1;
    else if((((Archivo*)v1)->fecha.a == ((Archivo*)v2)->fecha.a) && (((Archivo*)v1)->fecha.m < ((Archivo*)v2)->fecha.m))
        return 1;
    else if(((Archivo*)v1)->fecha.a == ((Archivo*)v2)->fecha.a && ((Archivo*)v1)->fecha.m == ((Archivo*)v2)->fecha.m &&((Archivo*)v1)->fecha.d > ((Archivo*)v2)->fecha.d) // si coinciden en mes y anio pero v1 es mas nuevo por dias
        return -1;

    return 1;

}
void MostrarArchivo(void *arch)
{
    printf("Fecha: %.4d-%.2d-%.2d \t Nivel: %s \t Indice: %f \t Clasificador: %s\n", ((Archivo*)arch)->fecha.a,
           ((Archivo*)arch)->fecha.m,((Archivo*)arch)->fecha.d,
           ((Archivo*)arch)->Nivel,((Archivo*)arch)->Indice,
           ((Archivo*)arch)->Clasificador);
}

int main()
{
    Vector a1,a2,a3;
    Archivo n1,n2;

    char hola[] = "09/08/2022";
    if(!CrearVector(&a1,sizeof(Archivo), 1))
        return 1;
    if(!CrearVector(&a2,sizeof(Archivo), 1))
        return 1;
    if(!CrearVector(&a3,sizeof(Archivo), 1))
        return 1;
    FormatoFecha(hola, &n1.fecha);
    mi_strcpy(n1.Nivel,"Materiales");
    n1.Indice = 124.56;
    mi_strcpy(n1.Clasificador, "Capitulos");
    vecInsElemFinal(&a1, (void*)&n1);

    n2.fecha.d = 10;
    n2.fecha.m = 8;
    n2.fecha.a = 2022;
    mi_strcpy(n2.Nivel,"Materiales");
    n2.Indice = 184.5;
    mi_strcpy(n2.Clasificador, "Items");
    vecInsElemFinal(&a2, (void*)&n2);
    printf("Vector 1\n\n");
    VectorMostrar(&a1,MostrarArchivo);
    printf("\n\nVector 2\n\n");
    VectorMostrar(&a2,MostrarArchivo);
    FusionarVectores(&a1,&a2,&a3,ComparaFechaYClasiArchivo);
    printf("\n\nVector Fusion   \n\n");
    VectorMostrar(&a3,MostrarArchivo);
    return 0;
}
