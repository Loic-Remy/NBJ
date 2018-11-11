
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[2]="";
char debut[10]="";
char fin[10]="";

scanf("%s %s %s",&canton, &debut, &fin);
printf("%s %s %s",canton, debut, fin);

valideSaisie(canton,debut,fin);



printf("\n%s %s %s",canton, debut, fin);

return 0;
}
