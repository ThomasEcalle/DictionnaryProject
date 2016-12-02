#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/dictionnary.h"





 void putInDictionnary(List * elements, char * path)
 {
     FILE * file = NULL;
     file = fopen(path,"w");

     List * newList = NULL;
     newList = initialisationList();

     int size = elements->length;
     int count = 0;



     if (file != NULL)
     {
        while (count < size)
         {

            char * min = calloc(100,sizeof(char));
            min = "zz";

            Element * actuel = elements->first;

            while (actuel->next != NULL)
            {
                if (strcmp(min,actuel->chaine) > 0)
                {
                    min =  calloc(100,sizeof(char));
                    strcpy(min,actuel->chaine);
                    printf("*************** %s",min);
                }

                actuel = actuel->next;
            }
            if (strcmp(min,"zz") != 0)
            {
                fprintf(file, "%s\n", min);
            }
            while (removeElement(elements, min) == 1)
            {
                removeElement(elements, min);
            }
            count++;
         }

     }
     else
     {
         printf("ouverture fichier impossible");
     }

     fclose(file);

 }

void getWordsFromFile(char * path, List * elementsList)
{
    FILE * file = NULL;
    int count = 0;
    int lastWasALetter = 0;

    file = fopen(path,"r");
    if(file != NULL)
    {

        char c = fgetc(file);

        while (c != EOF)
        {

            if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) // IF C IS A LETTER
            {
                count++;
                lastWasALetter = 1;
            }
            else
            {
                if (lastWasALetter)
                {
                    char * string = calloc(100,sizeof(char));
                    int i = 0;
                    fseek(file, -(count+1), SEEK_CUR);  // WE GO BACK TO THE FIRST LETTER OF THE Element
                    char tmp = fgetc(file);
                    for (i = 0; i < count; i++)
                    {
                         if (tmp >= 65 && tmp <= 90) // IF C IS AN UPPERCASE LETTER
                        {
                            tmp += 32;
                        }
                        if(count >= 2)
                        {
                            string[i] = tmp;
                        }

                        tmp = fgetc(file);
                    }
                    if (strlen(string) >= 2)
                    {
                        insertion(elementsList,string);

                    }

                    count = 0;
                    lastWasALetter = 0;
                }
            }
            c = fgetc(file);

        }


        fclose(file);

    }
}

List * initialisationList()
{
    List *list = malloc(sizeof(*list));
    Element *element = malloc(sizeof(*element));


    element = NULL;

    list->first = element;
    list->length = 0;

    return list;
}


void insertion(List * list, char * stringToAdd)
{
    // NEW Element CREATION
    Element *ElementToAdd = malloc(sizeof(*ElementToAdd));

    ElementToAdd->chaine = stringToAdd;
    ElementToAdd->length = strlen(stringToAdd);


    // INSERTION OF THE NEW Element AT FIRST POSITION
    ElementToAdd->next = list->first;

//    list->first->previous = ElementToAdd;
    list->first = ElementToAdd;
    list->length += 1;
}

void afficherListe(List * list)
{

    Element * actuel = list->first;

    while (actuel != NULL)
    {
        printf("%s -> ", actuel->chaine);
        actuel = actuel->next;
    }
}




int removeElement(List * list, char * value)
{
   Element * prev = list->first;
   Element * current = prev->next;

   if (strcmp(prev->chaine,value)==0)
   {
       list->first = current;
       free(prev);
       return 1;
   }

   while (current != NULL)
   {
       if (strcmp(current->chaine,value)==0) break;
       else
       {
           prev = current;
           current = current->next;
       }
   }

   if (current == NULL)
   {
       return 0;
   }

   else
   {
       prev->next = current->next;
       free(current);
       return 1;
   }
}