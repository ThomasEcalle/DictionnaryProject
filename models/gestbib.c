#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dictionnary.h"
int compare(char *a, char *b)
{
    int len1 = strlen(a);
    int len2 = strlen(b);
    if (len1 > len2)
        return compare(b, a);
    return len2 - len1;
}
char *substr(char *src, int len)
{
    if (len > strlen(src))
        return NULL;
    char *res = malloc(sizeof (char) * (len + 1));
    int i = 0;
    for (; i < len; ++i)
    {
        res[i] = src[i];
    }
    res[i] = '\0';
    return res;
}
void debugChar(char *msg, char *var)
{
    printf("%s    ", msg);
    printf("%s\n", var);
}
void debugInt(char *msg, int var)
{
    printf("%s    ", msg);
    printf("%d\n", var);
}
void createDictionary(){
}

void generateDictionary(char * formatText, char * dictionaryName){
    putInDictionnary(formatText,dictionaryName);
}

void destroyDictionary(char * path){
    remove(path);
}

void insertWord(){
}

char *researchWord(List *List, char *word, int filter)
{
    char *closest = "";
    int len = strlen(word);
    int i;
    Element *Element = malloc(sizeof (Element));
    Element = List->first;
    for (i = 0; i < List->length; Element = Element->next)
    {
//        debugChar("Element", Element->chaine);
        if (len > Element->length)
        {
            ++i;
            continue;
        }

        char *tmp = substr(Element->chaine, len);

//        debugChar("word", word);
//        debugChar("TMP", tmp);
        if (strcmp(tmp, word) == 0)
        {
//            debugChar("Research word : on entre dans debut commun", Element->chaine);
            int diff = compare(Element->chaine,word);
//            debugChar(word, Element->chaine);
//            debugInt("DIFF : ", diff);
            if (diff == 0)
            {
                debugChar("RESULT :", Element->chaine);
                return Element->chaine;
            }
            else if (diff <= filter)
            {
                if ((strlen(closest) == 0 && diff <= filter) || diff < filter)
                {
                    filter = diff;
                    closest = Element->chaine;
                }

            }
        }
//        debugChar("CLOSEST :", closest);
        ++i;
    }
    debugChar("RESULT :", closest);
    return closest;

}

/*
*   Input : char * source - Path of the .txt file
*           char * destination - Path of the future dictionary
*   Return : -
*   Purpose : This function will read the source file, take all the words and
              finally put them in order (deleting the doubles one) in the destination file
*/
 void putInDictionnary(char * source, char * destination)
 {
     List * elements = NULL;
     elements = initialisationList();

     getWordsFromFile(source,elements);

     FILE * file = NULL;
     file = fopen(destination,"w");

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

/*
*   Input : char * path - Path of the .txt file
*           List * elementsList - Linked list that will get all the words
*   Return : -
*   Purpose : This function will read a file and get all the words
*/
void getWordsFromFile(char * path, List * elementsList)
{
    FILE * file = NULL;
    int count = 0;
    int lastWasALetter = 0;

    file = fopen(path,"r");
    if(file != NULL)
    {

        char c = fgetc(file);

        while (1)
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
                    int retour = -(count+1);
                    if (c == EOF) retour = -(count); // BECAUSE EOF = -1
                    if (c == '\n') retour = -(count+2);
                    fseek(file, retour, SEEK_CUR);  // WE GO BACK TO THE FIRST LETTER OF THE Element
                    char tmp = fgetc(file);
                    for (i = 0; i < count; i++)
                    {
                         if (tmp >= 65 && tmp <= 90) // IF C IS AN UPPERCASE LETTER
                        {
                            tmp += 32;
                        }
                        string[i] = tmp;


                        tmp = fgetc(file);
                    }
                    if (strlen(string) >= 2 || string[0] == 'a')
                    {
                        insertion(elementsList,string);
                    }

                    count = 0;
                    lastWasALetter = 0;

                }
            }
            if (c == EOF) break;
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
