
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
strcpy(debut,"23.11.2018");
strcpy(fin,"01.12.2018");


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
