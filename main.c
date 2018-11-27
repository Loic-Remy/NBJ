
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

strcpy(canton,argv[1]);
strcpy(debut,argv[2]);
strcpy(fin,argv[3]);

struct datevent *tabFeries=NULL;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;

//scanf("%s %s %s",&canton, &debut, &fin);
printf("Canton: %s\tDebut: %s\tFin: %s",canton, debut, fin);

validerSaisie(canton,debut,fin);

tabFeries=chargerListeFeries(tabFeries,canton,ptrTailleTab);

comparerDates(debut,fin,tabFeries,tailleTab);

return 0;
}
