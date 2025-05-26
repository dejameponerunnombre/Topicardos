#include "tp.h"
int main()
{
    Archivo a1,a2,a3[2]; // Cree dos variables Archivo y las fusione en a3, para probar el punto 10
    int ce1 = 1,ce2 = 1,ce3 = 0, cap3 = 2;
    mi_strcpy(a1.fecha, "2022-01-23");
    mi_strcpy(a1.Clasificador, "Capitulos");
    a1.Indice = 124.56;
    mi_strcpy(a1.Nivel,"Materiales");
    mi_strcpy(a2.fecha, "2023-01-23");
    mi_strcpy(a2.Clasificador, "Nivel General");
    a2.Indice = 184.5;
    mi_strcpy(a2.Nivel, "Materiales");

    FusionarArchivos(&a1,&a2,a3, &ce1, &ce2, &ce3);
    MostrarArch(a3, &ce3);
    return 0;
}