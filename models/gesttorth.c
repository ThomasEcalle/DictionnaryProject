#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestbib.h"
#include "../gesttorth.h"

/*
*   Input : char * file- Path of the .txt file
*           char * dico - Path of the dictionnary
*   Return : -
*   Purpose : This function will read the source file and then return a List of the words
 that are not in the dictionary.
*/
List * getDifferentWords(char * file, char * dico)
{
    List * fileWords = getWordsFromFile(file);

    List * dicoWords = getWordsFromFile(dico);

    List * newList = compareList(fileWords,dicoWords);

    return newList;

}

void printDifferentsWords (char * file, char * dico)
{
    List * list = getDifferentWords(file,dico);
    Element * actual = list->first;
    while (actual->next != NULL)
    {
        printf("%s (line %d)\n",actual->chaine,actual->lineNumber);
        actual = actual->next;
    }

}


/*
*   Input : char * file- Path of the .txt file
*           char * dico - Path of the dictionnary
*   Return : -
*   Purpose : This function will read the source file and then return a List of the words
 that are not in the dictionary with a list of words (inside the dictionary) that could be a good correction.
*/
void printCloseList (char * file, char * dico)
{
    List * test = getDifferentWords(file,dico);
    List * dicoWords = getWordsFromFile(dico);

    Element * actual = test->first;
    while (actual->next != NULL)
    {
        printf("%s (line %d)\n",actual->chaine,actual->lineNumber);
        List *e = researchWordList(dicoWords,actual->chaine,2);
        int i = 0;
        if (e->length > 0)
        {
            while (i < e->length)
            {
                printf("  Close word : %s\n",e->first->chaine);
                e->first = e->first->next;
                ++i;
            }
        }
        else
        {
            printf("  No close word found\n");
        }

        actual = actual->next;
    }
}

/*
*   Input : char * filePath - Path of the .txt file
*           char * dico - Path of the dictionnary
*   Return : -
*   Purpose : This function will get the differences between both files and find out the possible corrections
                to the words that are not in dictionary's file
            then, it will replace all the words which have good corrections by the new words and print it
*/
void putCorrectWordsInFIle (char * filePath, char * dico)
{
    List * differents = getDifferentWords(filePath,dico);

    List * newone = putInOrderList(getNewWords(differents,dico));

    List * test = putInOrderList(getEverythingFromFile(filePath));


    FILE * file = NULL;
    file = fopen(filePath,"w");

    if(file != NULL)
    {
        Element * actual = test->first;
        Element * e = newone->first;
        while (actual->next != NULL && e->next != NULL)
        {
            if ((actual->firstChar == e->firstChar) &&
                (actual->lineNumber == e->lineNumber))
            {
              if (e->chaine != NULL)
              {
                  strcpy(actual->chaine,e->chaine);actual->chaine = e->chaine;
              }
              e = e->next;
            }

            fprintf(file, "%s", actual->chaine);
            actual = actual->next;
        }
         while (actual->next != NULL)
         {
            fprintf(file, "%s", actual->chaine);
            actual = actual->next;
         }
        fclose(file);
    }


}


List * getEverythingFromFile(char * path)
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
                    insertion(elementsList,string,line,firstChar);


                    count = 0;
                    lastWasALetter = 0;
                }
                char * test = calloc(2,sizeof(char));
                test[0] = c;
                if (c != EOF) insertion(elementsList,test,0,0);
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



List * getNewWords (List * list, char * dico)
{
    List * dicoWords = getWordsFromFile(dico);
    Element * actual = list->first;
    List * newone = initialisationList();
    while (actual->next != NULL)
    {
        List * e = researchWordList(dicoWords,actual->chaine,2);
        Element * tmp = malloc(sizeof(Element));

//        printf("%s",e->first->chaine);

        tmp->chaine = e->first->chaine;
        tmp->firstChar = actual->firstChar;
        tmp->lineNumber = actual->lineNumber;
        tmp->length = actual->length;


        tmp->next = newone->first;
        newone->first = tmp;
        actual = actual->next;
    }
    return newone;
}



List * putInOrderList(List * list)
{
    Element * actual = list->first;
    List * newone = initialisationList();
    while (actual->next != NULL)
    {
        Element * tmp = malloc(sizeof(Element));
        tmp->chaine = actual->chaine;
        tmp->lineNumber = actual->lineNumber;
        tmp->firstChar = actual->firstChar;
        tmp->length = actual->length;


        tmp->next = newone->first;;
        newone->first = tmp;
        actual = actual->next;
    }

    return newone;
}


List * compareList(List * first, List * second)
{
    List * newList = NULL;
    newList = initialisationList();


    int found = 0;
    Element * word1 = first->first;
    while (word1->next != NULL)
    {
        Element * word2 = second->first;
        while(word2->next != NULL)
        {
            if (strcmp(word1->chaine,word2->chaine) != 0)
            {
                found++;
            }
            word2 = word2->next;
        }
        if (found >= second->length)
        {
            insertion(newList,word1->chaine,word1->lineNumber,word1->firstChar);

        }
        found = 0;

        word1 = word1->next;
    }
    return newList;

}




