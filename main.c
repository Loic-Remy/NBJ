
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[3]={0};
char debut[11]={0};
char fin[11]={0};

strcpy(canton,"VS");
strcpy(debut,"02.01.1970");
strcpy(fin,"31.12.2017");


struct datevent *tabFeries=NULL;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;

//scanf("%s %s %s",&canton, &debut, &fin);
printf("Valeur du scanf: %s %s %s",canton, debut, fin);

validerSaisie(canton,debut,fin);

tabFeries=chargerListeFeries(tabFeries,canton,ptrTailleTab);

comparerDates(debut,fin,tabFeries,tailleTab);

return 0;
}
