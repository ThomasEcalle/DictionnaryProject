#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gestbib.h"
int compare(char *a, char *b)
{
    int diff = 0;
    int len1 = strlen(a);
    int len2 = strlen(b);
    if (len1 > len2)
        return compare(b, a);
    int i = 0;
    for (; i < len1; ++i)
    {
        if (a[i] != b[i])
            ++diff;
    }
    return diff + (len2 - len1) ;
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
void createDictionary(char * path){
    FILE * file = NULL;
    file = fopen(path,"w");
    if (file != NULL)
    {
        fclose(file);
    }
}

void generateDictionary(char * formatText, char * dictionaryName){
    putInDictionnary(formatText,dictionaryName);
}

void destroyDictionary(char * path){
    fclose(path);
    remove(path);
}

void insertWord(char * path, char * word){
    List * list = getWordsFromFile(path);

    insertion(list,word,0,0);

    fromListToDico(list,path);
}

void researchWordInFIle(char * path, char * word, int filter)
{
    List * list = getWordsFromFile(path);
    researchWord(list,word,filter);
}

int propostitionResercheMot (char * wordToFind, char * dicoPath)
{
    int result = 0;
    List * wordsFromDico = getWordsFromFile(dicoPath);
    Element * word = wordsFromDico->first;
    while (word->next != NULL)
    {
        if (strcmp(word->chaine,wordToFind) == 0)
        {
            result = 1;
        }
        word = word->next;
    }
    return result;
}
char *research(List *List, char *word)
{
    return researchWord(List, word, 0);
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

       // char *tmp = substr(Element->chaine, len);

//        debugChar("word", word);
//        debugChar("TMP", tmp);

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
*   Purpose : This function will read the source file and then call the function needed to
              put a linked list into a dictionary
*/
 void putInDictionnary(char * source, char * destination)
 {
    List * elements = getWordsFromFile(source);

     fromListToDico(elements,destination);
 }



 /*
*   Input : List * elements - Linked list
*           char * destination - Path of the future dictionary
*   Return : -
*   Purpose : This function put all the words of a linked list into a dictionary in order
*/
void fromListToDico (List * elements, char * destination)
 {
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
List * getWordsFromFile(char * path)
{
    List * elementsList = NULL;
    elementsList = initialisationList();
    FILE * file = NULL;
    int count = 0;
    int lastWasALetter = 0;
    int line = 1;

    file = fopen(path,"r");
    if(file != NULL)
    {

        char c = fgetc(file);
        int numberOfCharThisLine = 0;
        while (1)
        {
            numberOfCharThisLine++;
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
                    int firstChar = numberOfCharThisLine - (count + 1);
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
                        insertion(elementsList,string,line,firstChar);
                    }

                    count = 0;
                    lastWasALetter = 0;

                }
            }
            if (c == '\n')
            {
                line++;
                numberOfCharThisLine = 0;
            }
            if (c == EOF) break;
            c = fgetc(file);
        }
        fclose(file);
        return elementsList;

    }
}

List * initialisationList()
{
    List *list = malloc(sizeof(*list));
    Element *element = malloc(sizeof(*element));


    element->next = NULL;

    list->first = element;
    list->length = 0;

    return list;
}

void insertion(List * list, char * stringToAdd, int line, int firstChar)
{
    // NEW Element CREATION
    Element *ElementToAdd = malloc(sizeof(*ElementToAdd));

    ElementToAdd->chaine = stringToAdd;
    ElementToAdd->length = strlen(stringToAdd);
    ElementToAdd->lineNumber = line;
    ElementToAdd->firstChar = firstChar;


    // INSERTION OF THE NEW Element AT FIRST POSITION
    ElementToAdd->next = list->first;

//    list->first->previous = ElementToAdd;
    list->first = ElementToAdd;
    list->length += 1;
}

void afficherListe(List * list)
{

    Element * actuel = list->first;

    while (actuel->next != NULL)
    {
        printf("%s (%d) commence au caractere %d et a une longueur de %d caracteres\n", actuel->chaine, actuel->lineNumber, actuel->firstChar, actuel->length);
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
