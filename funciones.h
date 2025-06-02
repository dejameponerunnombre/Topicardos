#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define A_MAYUS(X) X >= 'a' && X <='z'? (X + 'A' - 'a') : X
#define TODO_MAL 0
#define SIN_MEM 2
#define TODO_OK 1
#define INCREMENTO 2

typedef struct{
int d;
int m;
int a;
}Fecha;

typedef struct{
Fecha fecha;
char Nivel[30];
double Indice;
char Clasificador[14];
}Archivo;

typedef struct{
void * vec;
int ce;
size_t cap;
size_t tamElem;
}Vector;

typedef int (*Cmp)(void*, void*);
typedef void (*Accion)(void*);


//TDA Vector

bool CrearVector(Vector *v, size_t tamElem, size_t cap);
void DestruirVector(Vector *v);
bool Redimensionar(Vector *v, size_t ncap);
bool vecInsElemFinal(Vector *v, void *elem);
void VectorMostrar(Vector *v, Accion accion);



//Ejercicios del Trabajo
void FormatoFecha (char* fechaV, Fecha* fechaN); // PUNTO 1 CAMBIAR FORMATO FECHA
double CambioFormatoIndice(char * indice); //PUNTO 2 CONVIERTE INDICE A DOUBLE
void desencriptadoNivelGralAperturasICC(char *texto); // PUNTO 3 Desencripta nivel_general_aperturas de ICC
void normalizarNivelGral(char *texto); // PUNTO 4 ELIMINA "_" Y HACE MAYUSUCULA LA PRIMER LETRA
void Clasificador(char *nivelGral, char *clasi); //PUNTO 5 DEVUELVE "NIVEL GENERAL" O "CAPÍTULOS" DEPENDIENDO EL VALOR DE NIVEL GENERAL
void desencriptadoNivelGralAperturasObras(char*texto); // PUNTO 7 Desencripta nivel_general_aperturas de Obras
void normalizarObras(char* texto); // PUNTO 8 NORMALIZA SACANDO LO ANTERIOR AL PRIMER "_", ELIMINA EL RESTO Y HACE MAYUSCULA LA PRIMER LETRA
bool FusionarVectores(Vector *v1, Vector *v2, Vector *vFusion, Cmp cmp); // PUNTO 10 FUSIONA AMBOS ARCHIVOS DE FORMA ORDENADA CON FUNCION GENERICA, PRIMERO ICC Y LUEGO OBRAS



//Funciones utilizadas
void ReemplazoDeCaracter(char* strg, char charToFind, char charToReplace); // REEMPLAZA EL CARACTER DESEADO POR EL INDICADO EN EL STRING
double mi_atod(const char *c); // CONVIERTE UN CHAR EN UN DOUBLE
int mi_strcmp(const char *,  const char *); // Compara dos string y devuelve 0 si son iguales, >1 si el primero es mas grande y visceversa
char *mi_strcpy(char *s1, const char *s2); // COPIA EN S1 LA CADENA DE S2
char *mi_strchr(char *s, char *c); // ENCUENTRA LA POSICION DEL CHAR C EN LA CADENA S Y DEVUELVE SU POSICION, O NULL SI NO ENCONTRO
int mi_atoi(const char *c); // CONVIERTE UN STRING EN ENTERO
#endif // TP_H_INCLUDED