
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[3]="VS";
char debut[11]="23.11.2018";
char fin[11]="01.12.2018";

struct datevent * tabFeries=NULL;

//scanf("%s %s %s",&canton, &debut, &fin);
printf("Valeur du scanf: %s %s %s",canton, debut, fin);

validerSaisie(canton,debut,fin);

chargerListeFeries(tabFeries,canton);

comparerDates(debut,fin,tabFeries);

return 0;
}
