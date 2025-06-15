#include "funciones.h"
int main()
{
    FILE *ICC, *Obras, *Final;
    Archivo lectura;
    Vector vICC, vObras, vFusion;
    char linea[90];
    //Creacion de vectores con concepto TDA Vector
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
    //Apertura de archivos
    ICC = fopen("indices_icc_general_capitulos.csv", "r");
    if(!ICC)
    {
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        DestruirVector(&vFusion);
        printf("Error al abrir el archivo");
        return 1;
    }
    Obras = fopen("Indices_items_obra.csv", "r");
    if(!Obras)
    {
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        DestruirVector(&vFusion);
        fclose(ICC);
        printf("Error al abrir el archivo");
        return 1;
    }
    Final = fopen("Final.dat", "wb");
    if(!Final)
    {
        DestruirVector(&vICC);
        DestruirVector(&vObras);
        DestruirVector(&vFusion);
        fclose(ICC);
        fclose(Obras);
        printf("Error al abrir el archivo");
        return 1;
    }
    //Carga de los vectores en base a los archivos dados
    fgets(linea,sizeof(linea),ICC); //Primera linea de los nombres de las columnas
    fgets(linea,sizeof(linea),ICC);
    while(!feof(ICC))
    {
        NormalizarLinea(&lectura, linea, INDICE);
        if(vecInsElemFinal(&vICC,(void*)(&lectura))  == TODO_MAL)
        {
            printf("Error cargando el vector");
            return 1;
        }
        fgets(linea,sizeof(linea),ICC);
    }
    fclose(ICC); //Al no utilizarlo más lo cierro

    fgets(linea,sizeof(linea),Obras); //Primera linea de los nombres de las columnas
    fgets(linea,sizeof(linea),Obras);
    while(!feof(Obras))
    {

        NormalizarLinea(&lectura, linea, OBRAS);
        if(vecInsElemFinal(&vObras,(void*)(&lectura))  == TODO_MAL)
        {
            printf("Error cargando el vector");
            return 1;
        }
        fgets(linea,sizeof(linea),Obras);
    }
    fclose(Obras); //Al no utilizarlo más lo cierro

    if(FusionarVectores(&vICC,&vObras,&vFusion,ComparaFechaYClasiArchivo) == TODO_MAL) //Fusion de ambos vectores en uno ordenado
    {
        printf("Error al fusionar los archivos");
        return 1;
    }
    VectorModificar(&vFusion, InsertarVarMensEInter); // Intentando mantener lo generico en todas las funciones de TDA Vector, agrega Var. Mensual e Interanual
    VectorCrearArchivo(&vFusion,Final,CargarBinario); // Intentando mantener lo generico en todas las funciones de TDA Vector, carga del archivo binario final
    fclose(Final);
    //VectorMostrar(&vFusion,MostrarArchivo); // Muestra la fusion de ambos archivos de texto
    MostrarBinario(); // Muestra el archivo binario final
    return 0;
}