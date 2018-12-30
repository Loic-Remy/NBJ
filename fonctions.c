
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


/*
Recuperer la saisie utilisateur
en ligne de commande et stocker 
les arguments dans des variables
*/

int 
recupererLigneCmde(char ***ptrTabArguments, size_t tailleTampon)
{
	char c=0;
	char *tampon=calloc(tailleTampon,sizeof(int));
	char *tampArg=calloc(tailleTampon,sizeof(int));
	size_t i=0, longTampon=0, nbArguments=1, arg=1, nbCar=0; 
	char **tabArguments=NULL;
	
	printf("\n$ ");
	fgets(tampon,tailleTampon,stdin);
	
	longTampon=strlen(tampon);
	
	for(i=0; i<=longTampon; i++) {
		if (tampon[i]==' ') {
			nbArguments++;
		}
	}	
	
	tabArguments=calloc(nbArguments,sizeof(char*));
	*ptrTabArguments=tabArguments;
	
	for(i=0; i<=longTampon; i++) {
		if (tampon[i]==' ' || tampon[i]=='\n') {
			tampArg[i]='\0';
			tabArguments[arg]=calloc(strlen(tampArg)+1,sizeof(char));
			strcpy(tabArguments[arg],tampArg);
			nbCar=nbCar+strlen(tampArg)+1;
			memset(tampArg,0,strlen(tampArg));
			if (arg<nbArguments) {
				arg++;
			}
		}		
		else {		
			tampArg[i-nbCar]=tampon[i];
		}
	}	
	free(tampon);
	
	/* DEBUT ZONE DE TEST
	for (i=0; i<=nbArguments; i++) {
		printf("\nArgument [%d] : %s",i, tabArguments[i]);
	}
	FIN ZONE DE TEST*/
return 0;
}

/*--------------------------------------------------------------------------------------------*/

/*
Définir l'année à utiliser pour l'autocomplétion de l'année
lorsque l'utilisateur ne l'a pas définie dans la fonction 'calc'
	userChoice = reçoit le choix de l'utilisateur (soit une année soit '0' pour auto)
	varOption = reçoit la variable à modifier une fois l'année déterminée
*/

int 
complYear(int userChoice, int *varOption)
{
	time_t currDate = 0;
	struct tm date = {0};
	
	
	if (userChoice==0) {
		time(&currDate);
		date=*localtime(&currDate);
		*varOption=date.tm_year;
	}
	else if (userChoice>=1970 && userChoice<=2069) {
		*varOption=userChoice-1900;
	}
	else {
		printf("\n\tL'argument saisie n'est pas valide");
	}
	
	return 0;
}

/*--------------------------------------------------------------------------------------------*/

/*
Valider l'argument "Feries" saisi par l'utilisateur
et le formater pour permettre ouverture du fichier dans autre fonction
	listeFeries = indique le pointeur qui recevra la liste de date à exclure
	canton = liste de feries à utilisée, saisi par l'utilisateur
*/

int 
validerEtFormaterFeries(char **listeFeries, char *canton)
{
	FILE *fichier=NULL;
	*listeFeries=calloc(7,sizeof(char));
	snprintf(*listeFeries,6,"%s.txt",canton);
	fichier=fopen(*listeFeries,"r");
	
	if(fichier==NULL)
		{
		strcpy(*listeFeries,"CH.txt");
		printf("\nERREUR : Argument [canton] non valide\nCalcul effectue avec la liste par defaut CH");
		}
	fclose(fichier);
	return 0;
}

/*--------------------------------------------------------------------------------------------*/

/*
Valider argument "Date" saisi par l'utilisateur
et le formater pour permettre utilisation dans une autre fonction
-recuperer le string (saisie),
-vérifier son format (nombre de séparateurs et taille),
- copier les caractères dans une structure (struct tm)
*/

int 
validerEtFormaterDate(struct tm *date, char *saisie, int autoYear, int formatEntree)
{
	int interval[4]={0,0,0,0};
	char c=0;
	char tampon[4];
	size_t i=0, nbInterval=0, longueur=0;
	
	for (i=0; i<=strlen(saisie); i++) {
		c=saisie[i];
		longueur++;
		if (c<48 || c>57) {
			interval[nbInterval]=(longueur-1);
			nbInterval++;
			longueur=0;
		}
		else if (nbInterval==3) {
			printf("\nFormat de date non valide. Format requis : jj.mm.aaaa ou j.m.aa");
			return 0;
		}
	}
	longueur=0;
	nbInterval=0;
	for (i=0; i<=strlen(saisie); i++) {
		tampon[i-longueur]=saisie[i];
		if (strlen(tampon)==interval[nbInterval]) {
			if (nbInterval==0) {
				date->tm_mday=atoi(tampon);
			}
			else if (nbInterval==1) {
				date->tm_mon=atoi(tampon)-1;
			}
			else if (nbInterval==2) {
				if (interval[nbInterval]==2) {
					if (atoi(tampon)<70) {
						date->tm_year=atoi(tampon)+100;
					}
					else {
						date->tm_year=atoi(tampon);
					}
				}
				else if (interval[nbInterval]==4) {
					date->tm_year=atoi(tampon)-1900;
				}
			}
		memset(tampon,0,4);
		nbInterval++;
		i++;
		longueur=i+1;
		}
	}
	if (interval[2]==0) {
		date->tm_year=autoYear;
	}


return 0;	
}

/*--------------------------------------------------------------------------------------------*/

/*
Reçoit les dates debut et fin ainsi que la liste des feries et la taille de ce tab.
Elle convertie en time_t les struct tm reçues puis teste chaque date afin de voir
si ce n'est pas : un férié, un samedi, un dimanche.
Elle affiche ensuite le résultat (printf).
*/

int 
comparerDates(struct tm *debut, struct tm *fin, struct datevent * tabFeries, int tailleTabFeries)
{
	time_t timeStart=0;
	time_t timeEnd=0;
	time_t timeCheck=0;
	struct tm check={0};
	
	size_t nbOuvres=0, nbSam=0, nbDim=0, nbFeries=0;
	size_t i=0;
	
	timeStart=mktime(debut);
	timeEnd=mktime(fin);
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
			nbOuvres++;
				for (i=0;i<tailleTabFeries;i++) {
					if (timeCheck==tabFeries[i].date) {
						nbFeries++;
						nbOuvres--;
			}
		}
	}
	timeCheck=timeCheck+(60*60*24);
}

printf("\nSamedi [%d]\tDimanche [%d]\tFeries [%d]\tOuvres [%d]\n",nbSam,nbDim,nbFeries,nbOuvres);
	
}

/*--------------------------------------------------------------------------------------------*/


struct 
datevent *chargerListeFeries(char **fichierFeries, int *ptrTailleTab)
{
	
	struct tm date={0};
	time_t dateSec=0;
	char tamponLigne[40]={0};
	char tamponSaisie[30]={0};
	int compteurLigne=1;
	char c=0;
	int i=0;
	int n=0;
	struct datevent *tabFeries=NULL;
	FILE *fichier=NULL;
	fichier=fopen(*fichierFeries,"r");
	
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
			date.tm_mon=atoi(tamponSaisie)-1;
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

free(*fichierFeries);
fclose(fichier);
return tabFeries;
}



/*--------------------------------------------------------------------------------------------*/

void 
help(void) {
	printf("\nRepertoir des commandes disponibles\n");
	printf("\ncalc\t: calcule le nombre de jours ouvres entre deux dates");
	printf("\nloc\t: effectue les operations de calcul sur la base de donnees externes");
	printf("\nedit\t: modifie les listes de feries");
	printf("\nset\t: modifie certains parametres");
	printf("\nshow\t: affiche les variables et certaines valeurs");
	printf("\nhelp\t: affiche l'ensemble des commandes disponibles et leurs arguments");
	printf("\nexit\t: quitte le programme");
	printf("\n");

}
