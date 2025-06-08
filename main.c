#include "funciones.h"

int main()
{
    FILE *ICC, *Obras;
    Archivo lectura;
    Vector vICC, vObras, vFusion;
    char linea[90];

    if(!CrearVector(&vICC, sizeof(Archivo), CAP))
    {
        printf("Falta de memoria");
        return 1;
    }
    if(!CrearVector(&vObras, sizeof(Archivo), CAP))
    {
        printf("Falta de memoria");
        DestruirVector(&vICC);
        return 1;
    }
    if(!CrearVector(&vFusion,sizeof(Archivo), CAP))
    {
        printf("Falta de memoria");
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        return 1;
    }
    ICC = fopen("indices_icc_general_capitulos.csv", "rt");
    if(!ICC)
    {
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        DestruirVector(&vFusion);
        printf("Error al abrir el archivo");
        return 1;
    }
    Obras = fopen("Indices_items_obra.csv", "rt");
    if(!Obras)
    {
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        DestruirVector(&vFusion);
        fclose(ICC);
        printf("Error al abrir el archivo");
        return 1;
    }

    fgets(linea,sizeof(linea),ICC);
    fgets(linea,sizeof(linea),ICC);
    while(!feof(ICC))
    {
        NormalizarLinea(&lectura, linea, INDICE);
        vecInsElemFinal(&vICC,(void*)(&lectura));
        fgets(linea,sizeof(linea),ICC);
    }

    fgets(linea,sizeof(linea),Obras);
    fgets(linea,sizeof(linea),Obras);
    while(!feof(Obras))
    {

        NormalizarLinea(&lectura, linea, OBRAS);
        vecInsElemFinal(&vObras,(void*)(&lectura));
        fgets(linea,sizeof(linea),Obras);
    }
    FusionarVectores(&vICC,&vObras,&vFusion,ComparaFechaYClasiArchivo);
    VectorModificar(&vFusion, InsertarVarMensEInter);
    VectorMostrar(&vFusion, MostrarArchivo);
    return 0;
}