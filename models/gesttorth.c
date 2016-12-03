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

    List * newList = NULL;
    newList = initialisationList();
    compareList(fileWords,dicoWords, newList);

    afficherListe(newList);

}

List * compareList(List * first, List * second, List * newList)
{
    int i, j;
    Element * word1 = first->first;
    Element * word2 = second->first;
    int found = 0;
    while (word1->next != NULL)
    {
        while(word2->next != NULL)
        {
            if (strcmp(word1->chaine,word2->chaine) == 0)
            {
                found++;
            }
            word2 = word2->next;
        }
        if (found == 0)
        {
            insertion(newList,word1->chaine);
            found = 0;
        }
        word1 = word1->next;
    }

}
