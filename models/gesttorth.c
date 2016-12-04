#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestbib.h"
#include "../gesttorth.h"
void getDifferentWords(char * file, char * dico)
{
    List * fileWords = NULL;
    fileWords = initialisationList();
    getWordsFromFile(file,fileWords);

    List * dicoWords = NULL;
    dicoWords = initialisationList();
    getWordsFromFile(dico,dicoWords);


    List * newList = compareList(fileWords,dicoWords);

    afficherListe(newList);

}

List * compareList(List * first, List * second)
{
    int i, j;
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
            insertion(newList,word1->chaine,word1->lineNumber);
        }
        found = 0;

        word1 = word1->next;
    }
    return newList;

}
