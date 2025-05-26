#include "tp.h"

void ReemplazoDeCaracter(char* strg, char charToFind, char charToReplace)
{
    while(*strg)
    {
        if(*strg==charToFind) // Busca en la cadena el caracter deseado
        {
            *strg=charToReplace; // Reemplaza el caracter buscado por el indicado den charToReplace
        }
        strg++;
    }
}

double mi_atod(const char *c)
{
    double num = 0;
    int signo = 1, i = 10;
    if(*c == '-') // Si es negativo lo multiplica al final de la funcion
    {
        signo  = -1;
        c++;
    }
    else if(*c == '+')
        c++;
    while(*c && *c != '.') // Mientras no termine y sea parte de los enteros
    {
        num = num*10 + (*c - '0');
        c++;
    }
    c++;
    while(*c) // Si no termino pero hay parte decimal
    {
        num += (float)(*c - '0')/i;
        c++;
        i*=10;
    }
    return num*signo;
}

int mi_strcmp(const char *s1,  const char *s2)
{
    while(*s1!='\0' && *s2!='\0' && *s1==*s2)
    {
        s1++;
        s2++;
    }
    return *s1-*s2;
}

char *mi_strcpy(char *s1, const char *s2) //cadenas igual tamaño
{
    char *aux=s1;
    while(*s2)
    {
        *s1=*s2;
        s1++;
        s2++;
    }
    *s1='\0';
    return aux;
}

char *mi_strchr(char *s, char *c)
{
    char *aux = NULL;
    while (*s && aux == NULL)
    {
        if(*s == *c)
            aux = s;
        s++;
    }
    return aux;
}

void FormatoFecha (char* fechaV, char *fechaN)// PUNTO 1 CAMBIAR FORMATO FECHA
{
    char dia[3], mes[3], anio[5];
    sscanf(fechaV,"%2s/%2s/%4s", dia, mes, anio); // Descompongo el string original
    sprintf(fechaN, "%s-%s-%s", anio, mes, dia); // Nuevo formato de fecha
}

double CambioFormatoIndice(char * indice)
{
    ReemplazoDeCaracter(indice, ',','.'); // Busco en indice todos las "," y las reemplazo por "."
    return mi_atod(indice); // retorna el indice como double
}

void desencriptadoNivelGralAperturasICC(char *texto)
{
    int pos = 0, aum = 0;
    while(*texto)
    {
        if(*texto <= 'z' && *texto >= 'a') // verifica que el char sea letra
        {
            pos++; // la posicion de la letra en la palabra
            if(pos%2 == 0) // si es par
                aum = 2;
            else // si es impar
                aum= 4;
            if((*texto + aum) < 'z') // si no termina el abecedario buscando la letra correcta
                *texto += aum;
            else // si si termina el abecedario
                *texto += 'a'-1 + aum - 'z';
        }
        else
            pos = 0; // reinicia el contador si el caracter no es letra, es decir, termino la palabra
        texto++;
    }
}

void normalizarNivelGral(char *texto)
{
    *texto = A_MAYUS(*texto); // Convierte a mayuscula la primer letra
    ReemplazoDeCaracter(texto, '_', ' '); // Busca todos los "_" en texto y los convierte en " "
    return;
}

void Clasificador(char *nivelGral,char *clasi)
{
    char pal[] = "Nivel general", opcion[] = "Capitulos"; // Declaracion de ambas posibilidades
    if(mi_strcmp(nivelGral, pal)) // Pregunto si el campo es igual a "Nivel general"
    {
        mi_strcpy(clasi, opcion); // En caso que no lo sea, en la variable disponible copio "Capitulos"
    }
    else
    {
        mi_strcpy(clasi, nivelGral); // En caso que si lo sea, en la variable disponible copio "Nivel general"
    }
}

void desencriptadoNivelGralAperturasObras(char*texto)
{
    char codigo1[] = "@8310$7|59",codigo2[] = "abeiostlmn", *car; // Declaro ambos codigos de encriptacion
    int pos;
    while(*texto)
    {
        car = mi_strchr(codigo1,texto); // Busco si la letra del texto a la que apunto se encuentra en el primer codigo
        if(car) // Pregunto si encontro algo
        {
            pos = (car-codigo1)/sizeof(codigo1[0]); // Copio la posicion del vector en la que se encuentra el caracter encontrado
            ReemplazoDeCaracter(texto, codigo1[pos], codigo2[pos]); // Reemplazo el caracter encontrado por su equivalente en el codigo2
        }
        texto++;
    }
}

void normalizarObras(char *texto)
{
    int cont = 1; // Inicializo el contador en 1 ya que un "_" tengo que borrar seguro
    char *aux = texto;
    while(*texto && *texto != '_') // Mientras que no termine el texto ni el caracter sea "_"
    {
        cont++; // Aumento el contador de caracteres a borrar
        texto++;
    }
    texto = aux; // Devuelvo el puntero de texto al inicio
    while(*texto)
    {
        *texto = *(texto+cont); // Reemplazo los caracteres del texto para que lo previo al primer "_" sea eliminado
        texto++;
    }
    *texto = '\0'; // Al final del texto agrego el nuevo \0
    texto = aux;
    normalizarNivelGral(texto); // Llamo a la funcion para cambiar los restantes "_" en " " y dejar en mayuscula la primer letra
}

void FusionarArchivos(Archivo* ICC, Archivo* Obras, Archivo* Fusion, int *ce1, int *ce2, int* ce3)
{
    int i = 0, j = 0;
    while(i < *ce1 || j < *ce2) //Si alguno de los dos archivos no llego al final debe seguir
    {
        if(i == *ce1) // Si llego al final el primero que inserte al segundo archivo
        {
            InsertarAlFinal(Fusion,Obras,ce3); // Inserta al final del struct final
            Obras++; // Incremento el archivo que inserte
            j++; // Incremento el contador del archivo que inserte
        }
        else if(j == *ce2)// Si llego al final el segundo que inserte al primer archivo
        {
            InsertarAlFinal(Fusion,ICC,ce3);
            ICC++;
            i++;
        }
        else{
            if(CompararArch(ICC,Obras) < 0) // si ambos tienen registros disponibles, que ingrese al menor
            {
                InsertarAlFinal(Fusion,ICC,ce3);
                ICC++;
                i++;
            }
            else
            {
                InsertarAlFinal(Fusion,Obras,ce3);
                Obras++;
                j++;
            }
        }
    }
}

void InsertarAlFinal(Archivo* a1, Archivo * a2, int *ce1) // Funcion para insertar un registro al final del vector
{
    /*if(*ce1 == CAP)
    {
        //Crear funcion de realloc
    }*/
    a1 += *ce1;
    mi_strcpy(a1->Clasificador, a2->Clasificador);
    mi_strcpy(a1->fecha, a2->fecha);
    a1->Indice = a2->Indice;
    mi_strcpy(a1->Nivel, a2->Nivel);
    *ce1 = *ce1 +1;
}

int CompararArch(Archivo *ICC,Archivo *Obras) // Compara ambos archivos, en este caso es solo una condicion, pero pueden ser mas
{
    return mi_strcmp(ICC->fecha, Obras->fecha);
}

void MostrarArch(Archivo *arch,int *ce) // Muestra al struct Archivo cuantos registros tenga
{
    int i;
    for(i = 0; i<*ce; i++)
    {
        printf("Fecha: %s \tNivel: %s \tIndice: %f \tClasificador: %s\n", arch->fecha, arch->Nivel, arch->Indice, arch->Clasificador);
        arch++;
    }
}
