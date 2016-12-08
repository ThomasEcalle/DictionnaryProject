#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gestbib.h"

Element *researchWordList(List *List, char *word, int filter)
{
    Element *closest = malloc(sizeof (Element));
    Element *head = closest;
    int len = strlen(word);
    int i;
    Element *Element = malloc(sizeof (Element));
    Element = List->first;
    for (i = 0; i < List->length; Element = Element->next)
    {
 //debugChar("", "AVANT diff");
            int diff = compare(Element->chaine,word);

     //   debugChar("", "apres diff");
            if (diff <= filter)
            {

                    filter = diff;
               //     debugChar("mot qui entre dans la liste: ",Element->chaine );
                    closest->chaine = Element->chaine;
                    if (i < List->length -1)
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
