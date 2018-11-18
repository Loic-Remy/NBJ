
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"

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
	double timeDifference=0;
	char tamponSaisie[4]={0};
	struct tm debut;
	struct tm fin;	
	time_t timeStart=0;
	time_t timeEnd=0;
	
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
			debut.tm_year=atoi(tamponSaisie)-1900;
			memset(tamponSaisie,0,4);
			debut.tm_hour=0;
			debut.tm_min=0;
			debut.tm_sec=0;
			debut.tm_isdst=0;
		}
		else
		{
			printf("ERREUR: Format de date de debut incorrect");
		}	
	}

	timeStart=mktime(&debut);  	/* DONE (#1#): à l'exécution de cette ligne, debut.tm_mday subit -1 */
	
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
			fin.tm_year=atoi(tamponSaisie)-1900;
			memset(tamponSaisie,0,9);
			fin.tm_hour=0;
			fin.tm_min=0;
			fin.tm_sec=0;
			fin.tm_isdst=0;
		}
		else
		{
			printf("ERREUR: Format de date de fin incorrect");
		}	
	}

	
	timeEnd=mktime(&fin);
			

//printf("\njour, mois, annee: %d %d %d",debut.tm_mday, debut.tm_mon, debut.tm_year);
//printf("\njour, mois, annee: %d %d %d",fin.tm_mday, fin.tm_mon, fin.tm_year);	

timeDifference=difftime(timeEnd,timeStart);

printf("\nnbjours %f",timeDifference/(60*60*24));

return timeDifference/(60*60*24);
	
}


int chargerListeFeries(struct datevent tabFeries[])
{
	
	struct tm date={0};
	char tampon[30]={0};
	int compteurLigne=1;
	char c=0;
	int iCar=0;
	int iTamp=0;
	FILE *fichier=NULL;
	
	fichier=fopen("VS.txt","r");
	
	if(fichier=!NULL) {
			
	
	while(c!=EOF)
	{
		fgetc(fichier);
		
	
		if (iCar==2){
			date.tm_mday=atoi(tampon);
			memset(tampon,0,30);
			iTamp=0;
			iCar++;
		}	
		else if (iCar==4){
			date.tm_mon=atoi(tampon);
			memset(tampon,0,30);
			iTamp=0;
			iCar++;
		}	
		else if (iCar==10){
			date.tm_year=atoi(tampon);
			memset(tampon,0,30);
			iTamp=0;
			iCar++;				
		}
		else if (c=='\n') {
			strcpy(tabFeries[compteurLigne].event,tampon);
			compteurLigne++;
			iTamp=0;
			iCar++;
		}	
		else {
			tampon[iTamp]=c;
			iCar++;	
		}
			
		
	}

	
	
	fclose(fichier);
	}
	else {
		printf("Le fichier VS n'a pas pu etre ouvert");
	}
	
}





void aide(void)
{
	printf("\nRepertoir des commandes disponibles\n\n");
	printf("help : affiche l'ensemble des commandes disponibles et leurs arguments \n\n");
	printf("calc : calcul le nombre de jours ouvres entre deux dates");
}
