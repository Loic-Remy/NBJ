
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[2]="VS";
char debut[11]="23.11.1988";
char fin[11]="24.11.1988";

struct datevent * tabFeries=NULL;

//scanf("%s %s %s",&canton, &debut, &fin);
printf("Valeur du scanf: %s %s %s",canton, debut, fin);

validerSaisie(canton,debut,fin);

comparerDates(debut,fin);

//printf("\nValeur: canton, debut, fin: %s %s %s",canton, debut, fin);

chargerListeFeries(tabFeries);

return 0;
}
