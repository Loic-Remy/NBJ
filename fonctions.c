
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void validerSaisie(char canton[2], char debut[10],char fin [10])
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

int comparerDates(char premierJour[10], char dernierJour [10])
{
	double nbjours=0;
	char tamponSaisie[4]={0};
	struct tm debut;
	struct tm fin;
	struct tm *ptrdebut=&debut;
	struct tm *ptrfin=&fin;
	
	
	time_t start;
	time_t end;
	
	
	int i=0;
	
	for (i=0; i<=10; i++) {
		if (i<2) {
			tamponSaisie[i]=premierJour[i];
		}
		else if (i==2) {
			debut.tm_mday=atoi(tamponSaisie);
			memset(tamponSaisie,0,4);
		}
		else if (i<5 && i>2) {
			tamponSaisie[i-3]=premierJour[i];
		}
		else if (i==5) {
			debut.tm_mon=atoi(tamponSaisie);
			memset(tamponSaisie,0,4);
		}
		else if (i<10 && i>5) {
			tamponSaisie[i-6]=premierJour[i];
		}
		else if (i==10) {
			debut.tm_year=atoi(tamponSaisie);
			memset(tamponSaisie,0,4);
		}
		else
		{
			printf("ERREUR: Format de date de debut incorrect");
		}	
	}
	debut.tm_hour=0;
	debut.tm_min=0;
	debut.tm_sec=0;
	
	start=mktime(ptrdebut);
		
	i=0;
	
	for (i=0; i<=10; i++) {
		if (i<2) {
			tamponSaisie[i]=dernierJour[i];
		}
		else if (i==2) {
			fin.tm_mday=atoi(tamponSaisie);
			memset(tamponSaisie,0,4);
		}
		else if (i<5 && i>2) {
			tamponSaisie[i-3]=dernierJour[i];
		}
		else if (i==5) {
			fin.tm_mon=atoi(tamponSaisie);
			memset(tamponSaisie,0,4);
		}
		else if (i<10 && i>5) {
			tamponSaisie[i-6]=dernierJour[i];
		}
		else if (i==10) {
			fin.tm_year=atoi(tamponSaisie);
			memset(tamponSaisie,0,9);
		}
		else
		{
			printf("ERREUR: Format de date de fin incorrect");
		}	
	}

fin.tm_hour=0;
fin.tm_min=0;
fin.tm_sec=0;

end=mktime(ptrfin);
	
nbjours=difftime(end,start);
	
printf("\njour, mois, annee: %d %d %d",debut.tm_mday, debut.tm_mon, debut.tm_year);
printf("\njour, mois, annee: %d %d %d",fin.tm_mday, fin.tm_mon, fin.tm_year);	
printf("\nnbjours %f",nbjours);

	
}




void aide(void)
{
	printf("\nRepertoir des commandes disponibles\n\n");
	printf("help : affiche l'ensemble des commandes disponibles et leurs arguments \n\n");
	printf("calc : calcul le nombre de jours ouvres entre deux dates");
}
