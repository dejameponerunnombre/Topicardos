#include "funciones.h"

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

int mi_strlen(const char *c)
{
    int sum = 0;
    while(*c != '\0')
    {
        sum++;
        c++;
    }
    return sum;
}

double mi_atod(const char *c)
{
    double num = 0, signo = 1;
    int i = 10;
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

int mi_atoi(const char *c)
{
    int num = 0, signo = 1;

    if(*c == '-')
    {
        signo  = -1;
        c++;
    }
    else if(*c == '+')
        c++;
    while(*c)
    {
        num = num*10 + (*c - '0');
        c++;
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
    char * aux = s1;
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

void FormatoFecha (char* fechaV, Fecha *fechaN)// PUNTO 1 CAMBIAR FORMATO FECHA
{
    sscanf(fechaV,"%d/%d/%d", &fechaN->d, &fechaN->m, &fechaN->a);

     // Descompongo el string original
}

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
    printf("Fecha: %.4d-%.2d-%.2d\tNivel: %s\tIndice: %f\tClasificador: %s\tVar. Mensual: %f\tVar Interanual: %f\n", ((Archivo*)arch)->fecha.a,
           ((Archivo*)arch)->fecha.m,((Archivo*)arch)->fecha.d,
           ((Archivo*)arch)->Nivel,((Archivo*)arch)->Indice,
           ((Archivo*)arch)->Clasificador, ((Archivo*)arch)->varM,((Archivo*)arch)->varI);
}

double CambioFormatoIndice(char * indice)
{
    char busc = ',';
    double num;
    if(mi_strchr(indice, &busc))
        ReemplazoDeCaracter(indice, ',','.'); // Busco en indice todos las "," y las reemplazo por "."
    num = mi_atod(indice);
    return num; // retorna el indice como double
}

void desencriptadoNivelGralAperturasICC(char *texto)
{
    int pos = 0, aum = 0;
    while(*texto)
    {
        pos++;
        if(*texto <= 'z' && *texto >= 'a') // verifica que el char sea letra
        {
            if(pos%2 == 0) // si es par
                aum = 2;
            else // si es impar
                aum= 4;
            if((*texto + aum) < 'z') // si no termina el abecedario buscando la letra correcta
                *texto += aum;
            else // si si termina el abecedario
                *texto += 'a'-1 + aum - 'z';
        }
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

bool CrearVector(Vector *v, size_t tamElem, size_t cap)
{
    v->vec = (void*)malloc(tamElem*cap);
    if(!v->vec)
    {
        return false;
    }
    v->ce = 0;
    v->cap = cap;
    v->tamElem = tamElem;
    return true;
}

void DestruirVector(Vector *v) // libero la memoria del tipo de dato Vector
{
    free(v->vec);
}

bool Redimensionar(Vector *v, size_t ncap) // Redimensiono el vector de v, segun sea necesario
{
    void *nvec;
    nvec = realloc(v->vec, v->tamElem*ncap);
    if(!nvec)
        return false;
    v->vec = nvec;
    v->cap = ncap;
    return true;
}

bool vecInsElemFinal(Vector *v, void *elem) // Inserto en tipo de dato vector un elemento al final
{
    if(v->ce == v->cap)
    {
        if(!Redimensionar(v, v->cap*INCREMENTO))
            return TODO_MAL;
    }
    void * posIns = v->vec + v->ce*v->tamElem;
    memcpy(posIns,elem,v->tamElem);
    v->ce++;
    return TODO_OK;
}

bool FusionarVectores(Vector *v1, Vector *v2, Vector *vFusion, Cmp cmp)
{
    int i = 0, j = 0; // Establezco los limites de ambos vectores
    while(v1->ce > i || v2->ce > j) //Si alguno de los dos vectores no llegó a su fin
    {
        if(i == v1->ce) // Si llego al final el primero que inserte elementos del segundo vector
        {
            if(vecInsElemFinal(vFusion,v2->vec)) // Inserta al final del vector Fusion
                {
                    v2->vec+=v2->tamElem;// Incremento el archivo que inserte
                    j++;
                }
            else
                return TODO_MAL;
        }
        else if(j == v2->ce)// Si llego al final el segundo que inserte elementos del primer vector
        {
            if(vecInsElemFinal(vFusion,v1->vec))
            {
                v1->vec+=v1->tamElem;
                i++;
            }
            else
                return TODO_MAL;
        }
        else{
            if(cmp(v1->vec,v2->vec) < 0) // si ambos tienen elementos disponibles, que ingrese al menor
            {
                if(vecInsElemFinal(vFusion,v2->vec)) // Inserta al final del vector Fusion
                {
                    v2->vec+=v2->tamElem;// Incremento el archivo que inserte
                    j++;
                }
                else
                    return TODO_MAL;
            }
            else
            {
                if(vecInsElemFinal(vFusion,v1->vec))
                {
                    v1->vec+=v1->tamElem;
                    i++;
                }
                else
                    return TODO_MAL;
            }
        }
    }
    return TODO_OK;
}

void VectorMostrar(Vector *v, Accion accion)
{
   void *i,* ult = v->vec + (v->ce-1)*v->tamElem;
   for(i = v->vec; i <= ult; i+=v->tamElem)
   {
       accion(i);
   }
}

void ElimComillas(char*linea)
{
    char *aux;
    while(*linea)
    {
        if(*linea == '"')
        {
            aux = linea;
            while(*aux)
            {
                *aux = *(aux+1);
                aux++;
            }
        }
        linea++;
    }
}

void NormalizarLinea(Archivo *lec,char *linea, int val)
{
    int cont = 0;
    ElimComillas(linea);
    char *fin = linea + mi_strlen(linea)-1;
    *fin= '\0';
    while(fin >= linea)
    {
        if(*fin == ';' || fin == linea)
        {
            if(cont == 0)
            {
                lec->Indice = CambioFormatoIndice(fin+1);
            }
            else if(cont == 1)
            {
                if(val == INDICE)
                {
                    desencriptadoNivelGralAperturasICC(fin+1);
                    normalizarNivelGral(fin+1);
                }
                else if(val == OBRAS)
                {
                    desencriptadoNivelGralAperturasObras(fin+1);
                    normalizarObras(fin+1);
                }
                mi_strcpy(lec->Nivel,fin+1);
            }
            else
            {
                FormatoFecha(fin,&lec->fecha);
            }
            *fin = '\0';
            cont++;
        }
        fin --;
    }
    if(val == INDICE)
        Clasificador(lec->Nivel, lec->Clasificador);
    else if(val == OBRAS)
        mi_strcpy(lec->Clasificador, "Items");
}

float buscarIndiceM(Fecha* f, char *nivel, void *v)
{
    while(mi_strcmp(nivel, ((Archivo*)v)->Nivel) || f->a != ((Archivo*)v)->fecha.a || f->m != ((Archivo*)v)->fecha.m)
    {
        if(f->m == 1 && f->a == ((Archivo*)v)->fecha.a + 1 && ((Archivo*)v)->fecha.m == 12 && !mi_strcmp(nivel, ((Archivo*)v)->Nivel))
        {
            return ((Archivo*)v)->Indice;
        }
        else if(f->a == ((Archivo*)v)->fecha.a && f->m == ((Archivo*)v)->fecha.m + 1 && !mi_strcmp(nivel, ((Archivo*)v)->Nivel))
        {
            return ((Archivo*)v)->Indice;
        }
        v += sizeof(Archivo);
    }
    return 0;
}

float buscarIndiceI(Fecha* f, char *nivel, void *v)
{
    while(mi_strcmp(nivel, ((Archivo*)v)->Nivel) || f->a != ((Archivo*)v)->fecha.a || f->m != ((Archivo*)v)->fecha.m)
    {
        if(f->a == ((Archivo*)v)->fecha.a + 1 && !mi_strcmp(nivel, ((Archivo*)v)->Nivel))
        {
            return ((Archivo*)v)->Indice;
        }
        v += sizeof(Archivo);
    }
    return 0;
}

void InsertarVarMensEInter(void*v, void*linea)
{
    Fecha f = ((Archivo*)linea)->fecha;
    char nivel[40];
    mi_strcpy(nivel, ((Archivo*)linea)->Nivel);
    float valor;
    valor = buscarIndiceM(&f, nivel, v);
    if(valor)
    {
        valor = ((((Archivo*)linea)->Indice/valor) - 1)*100;
    }
    else
    {
        valor = 0;
    }
    ((Archivo*)linea)->varM = valor;
    valor = buscarIndiceI(&f, nivel, v);
    if(valor)
    {
        valor = ((((Archivo*)linea)->Indice/valor) - 1)*100;
    }
    else
    {
        valor = 0;
    }
    ((Archivo*)linea)->varI = valor;
}

void VectorModificar(Vector *v, Modificacion Modi)
{
    void * ult = v->vec+(v->tamElem*v->ce-1);
    void *ini = v->vec;
    void *actual = v->vec;
    while(actual <= ult)
    {
        Modi(ini, actual);
        actual += v->tamElem;
    }
}

