
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void valideSaisie(char canton[2], char debut[10],char fin [10])
{
	int i=0;
	for(i=0; i<=1; i++) {
		canton[i]=tolower(canton[i]);
	}
	if(strcmp(canton,"vs")!=0 || sizeof(canton)==2)
		{
		printf("\nERREUR : Argument [canton] non valide");
		}	
}






void aide(void)
{
	printf("\nRepertoir des commandes disponibles\n\n");
	printf("help : affiche l'ensemble des commandes disponibles et leurs arguments \n\n");
	printf("calc : calcul le nombre de jours ouvres entre deux dates");
}
