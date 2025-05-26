#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED
#define A_MAYUS(X) X >= 'a' && X <='z'? (X + 'A' - 'a') : X
#include <stdio.h>
#include <stdlib.h>

typedef struct{
char fecha[21];
char Nivel[30];
double Indice;
char Clasificador[14];
}Archivo;
void FormatoFecha (char* fechaV, char* fechaN); // PUNTO 1 CAMBIAR FORMATO FECHA
double CambioFormatoIndice(char * indice); //PUNTO 2 CONVIERTE INDICE A DOUBLE
void desencriptadoNivelGralAperturasICC(char *texto); // PUNTO 3 Desencripta nivel_general_aperturas de ICC
void normalizarNivelGral(char *texto); // PUNTO 4 ELIMINA "_" Y HACE MAYUSUCULA LA PRIMER LETRA
void Clasificador(char *nivelGral, char *clasi); //PUNTO 5 DEVUELVE "NIVEL GENERAL" O "CAPÍTULOS" DEPENDIENDO EL VALOR DE NIVEL GENERAL
void desencriptadoNivelGralAperturasObras(char*texto); // PUNTO 7 Desencripta nivel_general_aperturas de Obras
void normalizarObras(char* texto); // PUNTO 8 NORMALIZA SACANDO LO ANTERIOR AL PRIMER "_", ELIMINA EL RESTO Y HACE MAYUSCULA LA PRIMER LETRA
void FusionarArchivos(Archivo* ICC, Archivo* Obras, Archivo* Fusion, int *ce1, int *ce2, int* ce3); // PUNTO 10 FUSIONA AMBOS ARCHIVOS DE FORMA ORDENADA

void ReemplazoDeCaracter(char* strg, char charToFind, char charToReplace); // REEMPLAZA EL CARACTER DESEADO POR EL INDICADO EN EL STRING
double mi_atod(const char *c); // CONVIERTE UN CHAR EN UN DOUBLE
int mi_strcmp(const char *,  const char *); // Compara dos string y devuelve 0 si son iguales, >1 si el primero es mas grande y visceversa
char *mi_strcpy(char *s1, const char *s2);
char *mi_strchr(char *s, char *c);
void InsertarAlFinal(Archivo* a1, Archivo * a2, int *ce1); // INSERTA UN ELEMENTO (a1) EN EL OTRO, QUE ES VECTOR (a1)
int CompararArch(Archivo *ICC,Archivo *Obras);
void MostrarArch(Archivo *arch,int *ce);
#endif // TP_H_INCLUDED