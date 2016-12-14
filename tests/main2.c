//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "../constantes.h"
//#include "../gestbib.h"
//#include "../gestrech.h"
//
//
//int main(void)
//{
//    List *dico = malloc(sizeof (List));
//    dico->first = malloc(sizeof (Element));
//    dico->first->chaine = "dictionaire";
//    dico->first->length = strlen("dictionaire");
//
//    dico->first->next = malloc(sizeof (Element));
//    dico->first->next->chaine = "dicti";
//    dico->first->next->length = strlen("dicti");
//
//    dico->first->next->next = malloc(sizeof (Element));
//    dico->first->next->next->chaine = "dic";
//    dico->first->next->next->length = strlen("dic");
//
//    dico->first->next->next->next = malloc(sizeof (Element));
//    dico->first->next->next->next->chaine = "adi";
//    dico->first->next->next->next->length = strlen("adi");
//
//    dico->first->next->next->next->next = malloc(sizeof (Element));
//    dico->first->next->next->next->next->chaine = "di";
//    dico->first->next->next->next->next->length = strlen("di");
//    dico->length = 5;
//    List *list = researchWordList(dico, "da", 3);
//    Element *elem = list->first;
//    int i = 0;
//    while (i < list->length)
//    {
//        debugChar("",elem->chaine);
//        elem = elem->next;
//        ++i;
//    }
//}
