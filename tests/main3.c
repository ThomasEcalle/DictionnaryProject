#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../gestbib.h"
#include "../gesttorth.h"


int main()
{
    List * test = getDifferentWords("thomas.txt","thomas.dico");

    Element * actual = test->first;

    List * dicoWords = getWordsFromFile("thomas.dico");

  /*  while (actual->next != NULL)
    {
        Element * e = researchWordList(dicoWords,"maiso",3);
        if (e->next != NULL)
        {
            printf("%s\n",e->chaine);
        }
        else
        {
            printf("\npas de correspondance\n");
        }

        actual = actual->next;
    }*/
     List *e = researchWordList(dicoWords,"maiso",3);
     int i = 0;
    while (i < e->length)
    {
        debugChar("",e->first->chaine);
        e->first = e->first->next;
        ++i;
    }
}




