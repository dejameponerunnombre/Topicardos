#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char dia[3];
    char mes[3];
    char anio[5];
}Tfecha;

typedef struct
{
    Tfecha fecha; //fecha ordenada punto 1
    char fechac [11]; //la fecha como se leerá del archivo
    char nivel[50];
    char indicec[50]; //el indice como se leerpa del archivo
    float indice; //como se termina almacenando el indice  para el punto 2
}estructura;

float MIatof(const char *str) {
    float resultado = 0;
    float fraccion = 0;
    int signo = 1;
    float divisor = 10;

    // espacios en blanco
    while (*str == ' ' || *str == '\t') {
        str++;
    }

    // signo
    if (*str == '-') {
        signo = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // entera
    while (*str >= '0' && *str <= '9') {
        resultado = resultado * 10 + (*str - '0');
        str++;
    }

    // decimal
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            fraccion += (*str - '0') / divisor;
            divisor *= 10;
            str++;
        }
    }

    return signo * (resultado + fraccion);
}

void MIstrncpy(char *dest, const char *org, size_t n) {
    size_t i = 0;

    while (i < n && org[i] != '\0')
    {
        dest[i] = org[i];
        i++;
    }

    while (i < n)
    {
        dest[i] = '\0'; // Rellenar con '\0'
        i++;
    }
}

void InvertirFecha(estructura *v) //PUNTO 1
{
void InvertirFechas(estructura *v, size_t ce) {
    estructura *fin = v + ce;

    while (v < fin) {
        // día
        MIstrncpy(v->fecha.dia, v->fechac, 2);
        v->fecha.dia[2] = '\0';

        //  mes
        MIstrncpy(v->fecha.mes, v->fechac + 3, 2);
        v->fecha.mes[2] = '\0';

        // año
        MIstrncpy(v->fecha.anio, v->fechac + 6, 4);
        v->fecha.anio[4] = '\0';

        v++;  //  siguiente
    }
}
}

void comapunto(estructura *v) //PUNTO 2
{
    estructura *fin = v + ce;
    while (v < fin)
        {
            v->indice=MIatof(v->indicec);
            v++;
        }
}


int main()
{
    estructura v[50];
}
