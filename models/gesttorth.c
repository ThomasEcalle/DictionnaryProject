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
        printf("%s\n",actual->chaine);
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


void putCorrectWordsInFIle (char * file, char * dico)
{
//    List * differents = getDifferentWords(file,dico);
//
//    Element * actual = differents->first;


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




