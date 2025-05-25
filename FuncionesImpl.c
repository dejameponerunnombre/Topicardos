#include "FuncionesServ.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatDate(char* date)
{
    char* p = date;
    char* end = date;
//    char* aux ="0";
    goToEndOfString(end);
    char *year = date;
    char *month = date;
    char *day = date;
    int ce = my_strlength(date);

    stringToReplace(p,'/','-',ce);

}

//void myStrRplce(char * strgToReplace,char toFind, char toReplace)
//{
//    char *p = strgToReplace;
//    while(*p!='\0')
//    {
//        if(*p=='/')
//        {
//            *p='-';
//        }
//        p++;
//    }
//}

int my_strlength(char *strg)
{
    char*p=strg;
    int length=0;
    while(*p!='\0')
    {
        p++;
        length++;
    };
    return length;
};

void goToEndOfString(char *p)
{
    while(*p != '\0')
    {
        p++;
    }
}

void desencriptar (char* strg)
{
    int ce = my_strlength(strg);
    char* p = strg;
    for(int i=0; i < ce; i++)
    {
        if( (*p > 'a' && *p < 'z') || (*p > 'A' && *p < 'Z') )
        {
            if( (int) *p % 2 == 0 )
            {
                *p+=4;
                if(*p > 'z')
                {
                    *p=*p-('z'-'a'+1);
                }
                if(*p > 'Z' && *p < 'a' )
                {
                    *p=*p-('Z'-'A'+1);
                }
            }
            else
            {
                *p+=2;
                if(*p > 'z')
                {
                    *p=*p-('z'-'a'+1);
                }
                if(*p > 'Z' && *p < 'a')
                {
                    *p=*p-('Z'-'A'+1);
                }
            }
        }
        p++;
    }
}

void normalizarTexto(char* strg)
{

    int ce = my_strlength(strg);
    char* p = strg;
    *p= *p -('a'-'A');

    stringToReplace(strg,'_',' ', ce);
}

void stringToReplace(char* strg, char charToFind, char charToReplace,int ce)
{
    char* p = strg;
    for(int i =0; i<ce;i++){
        if(*p==charToFind)
        {
            *p=charToReplace;
        }
        p++;
    }
}
