#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../gestbib.h"
#include "../gesttorth.h"


int main()
{
    List * list = getDifferentWords("thomas.txt", "thomas.dico");
    afficherListe(list);
}

