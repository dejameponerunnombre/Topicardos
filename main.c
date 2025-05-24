#include <stdio.h>
#include <stdlib.h>
#include "FuncionesServ.h"

int main()
{
//    char date[]="9/11/1997";
//    formatDate(date);
//    printf(date);
        char texto[] = "jgrch_ecjcnyh";
        printf("%s\n", texto);
        desencriptar(texto);
        normalizarTexto(texto);
        printf("%s",texto);
//    char letra = 'a';
//    if((int)letra < 40){
//        printf("hola");
//    }else {
//        letra +=1;
//        printf("chau");
//    }

    return 0;
}
