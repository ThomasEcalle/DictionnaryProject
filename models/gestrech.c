#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gestbib.h"

List *researchWordList(List *list, char *word, int filter)
{
  //  debugInt("len", list->length);
    Element *closest = malloc(sizeof (Element));
    List *head = malloc(sizeof (List));
    head->first = closest;
    head->length = 0;
    int len = strlen(word);
    int i;
    Element *Element = malloc(sizeof (Element));
    Element = list->first;
    for (i = 0; i < list->length; Element = Element->next)
    {
 //debugChar("", "AVANT diff");
            int diff = compare(Element->chaine,word);

     //   debugChar("", "apres diff");
            if (diff <= filter)
            {

                    filter = diff;
               //     debugChar("mot qui entre dans la liste: ",Element->chaine );
                    closest->chaine = Element->chaine;
                    head->length += 1;
                    if (i < list->length -1)
                    {
                        closest->next = malloc(sizeof (Element));
                        closest = closest->next;
                    }
                    else
                    {
                        closest->next = NULL;
                    }

            }

//        debugChar("CLOSEST :", closest);
        ++i;
    }

    return head;

}
