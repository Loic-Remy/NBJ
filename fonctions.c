
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"

void validerSaisie(char canton[3], char debut[11],char fin [11])
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

/*--------------------------------------------------------------------------------------------*/


int comparerDates(char premierJour[11], char dernierJour [11], struct datevent * tabFeries, int tailleTabFeries)
{
	double timeDifference=0;
	char tamponSaisie[4]={0};
	struct tm debut={0};
	struct tm fin={0};
	struct tm check={0};
		
	time_t timeStart=0;
	time_t timeEnd=0;
	time_t timeCheck=0;
	
	int nbOuvres=0;
	int nbSam=0;
	int nbDim=0;
	int nbFeries=0;
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
			debut.tm_mon=atoi(tamponSaisie)-1;
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

	timeStart=mktime(&debut);
	
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
			fin.tm_mon=atoi(tamponSaisie)-1;
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

timeCheck=timeStart;			
while (timeCheck<=timeEnd) {
	
	check=*localtime(&timeCheck);
	
	
	
	
	if (check.tm_wday==6) {
		nbSam++;
	}		
	else if (check.tm_wday==0){
		nbDim++;
	}	
	else {
	/*	for (i=0;i<=tailleTabFeries;i++) {
			
			if (timeCheck==tabFeries[i].date)
				nbFeries++;
		}*/

	}


	timeCheck=timeCheck+(60*60*24);
}

printf("\n\nSamedi [%d]\tDimanche [%d]\tFeries [%d]\tOuvres [%d]",nbSam,nbDim,nbFeries,nbOuvres);
	
}

/*--------------------------------------------------------------------------------------------*/


struct datevent *chargerListeFeries(struct datevent tabFeries[], char canton[3], int *ptrTailleTab)
{
	
	struct tm date={0};
	time_t dateSec=0;
	char tamponLigne[40]={0};
	char tamponSaisie[30]={0};
	int compteurLigne=1;
	char c=0;
	int i=0;
	int n=0;
	FILE *fichier=NULL;
	
	fichier=fopen("VS.txt","r");
	

	if(fichier==NULL) {
		printf("Le fichier VS n'a pas pu etre ouvert");
	}
	else {
		//Lire le fichier pour compter le nombre de ligne et creer un tableau en fonction
		while (c!=EOF) {
			c=fgetc(fichier);
			if (c=='\n') {
				compteurLigne++;
			}
		}
		tabFeries=calloc(compteurLigne,sizeof(struct datevent));
		if(tabFeries==NULL) {
			exit(0);
		}
		(*ptrTailleTab)=compteurLigne;
		compteurLigne=1;
		rewind(fichier);
							
		while(fgets(tamponLigne,40,fichier)!=NULL) {
			
		for (i=0; i<=39; i++) {
		if (i<2) {
			tamponSaisie[i]=tamponLigne[i];
		}
		else if (i==2) {
			date.tm_mday=atoi(tamponSaisie);
			memset(tamponSaisie,0,30);
		}
		else if (i>2 &&i<5) {
			tamponSaisie[i-3]=tamponLigne[i];
		}
		else if (i==5) {
			date.tm_mon=atoi(tamponSaisie);
			memset(tamponSaisie,0,30);
		}
		else if (i>5 && i<10) {
			tamponSaisie[i-6]=tamponLigne[i];
		}
		else if (i==10) {
			date.tm_year=atoi(tamponSaisie)-1900;
			memset(tamponSaisie,0,30);
			date.tm_hour=0;
			date.tm_min=0;
			date.tm_sec=0;
			date.tm_isdst=0;
			dateSec=mktime(&date);
			tabFeries[n].date=dateSec;
		}
		else if (i>10 && i<39) {
			tamponSaisie[i-11]=tamponLigne[i];
		}
		else if (i==39){
			strncpy(tabFeries[n].event,tamponSaisie,strlen(tamponSaisie));
			memset(tamponSaisie,0,30);
			n++;
			
		
		}
		}
		}
	}	
	
fclose(fichier);
return tabFeries;
}



/*--------------------------------------------------------------------------------------------*/

void aide(void)
{
	printf("\nRepertoir des commandes disponibles\n\n");
	printf("help : affiche l'ensemble des commandes disponibles et leurs arguments \n\n");
	printf("calc : calcul le nombre de jours ouvres entre deux dates");
}
