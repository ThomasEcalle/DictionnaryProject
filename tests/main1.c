#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../gestbib.h"


int main()
{
   generateDictionary("thomas.txt","thomas.dico");

//   Element * word = malloc(sizeof(word));
//   word->chaine = "pocebleu";
//   insertWord("thomas.dico", word);

//destroyDictionary("thomas.txt");
//destroyDictionary("thomas.dico");
//destroyDictionary("raph.dico");
    char * mot = malloc(sizeof(char)*20);
    mot = researchWordInFIle("thomas.dico","socia",2);
    printf("%s",mot);
}

