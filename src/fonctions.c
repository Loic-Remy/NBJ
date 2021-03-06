
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\inc\fonctions.h"


/*
D�finir l'ann�e � utiliser pour l'autocompl�tion de l'ann�e
lorsque l'utilisateur ne l'a pas d�finie dans la fonction 'calc'
	userChoice = re�oit le choix de l'utilisateur (soit une ann�e soit '0' pour auto)
	varOption = re�oit la variable � modifier une fois l'ann�e d�termin�e
*/

int 
complYear(int userChoice, struct settings *settings)
{
	time_t currDate = 0;
	struct tm date = {0};
	
	
	if (userChoice==0) {
		time(&currDate);
		date=*localtime(&currDate);
		settings->autoYear=date.tm_year;
	}
	else if (userChoice>=1970 && userChoice<=2069) {
		settings->autoYear=userChoice-1900;
	}
	else {
		printf("\n\tL'argument saisie n'est pas valide");
	}
	
	return 0;
}

/*--------------------------------------------------------------------------------------------*/
/*
DESCRIPTION
	The function formats the str input from user and return a pointer to this string as a path
	to the directory containing the holiday's files.
	
INPUTS
	userChoice	= string with the path to the directory containing the file with holidays

OUTPUT
	The functions return a pointer to char to the path to holidays directory
*/

char* 
setPath(char* userChoice)
{
	char *path=NULL;
	char *lastChar=NULL;
	size_t pathLen=0;
	
	lastChar=&userChoice[strlen(userChoice)];
	
	pathLen=strlen(userChoice)+2;
	path=calloc(pathLen,sizeof(char));
	
	if(*lastChar!='\\') {
		snprintf(path,pathLen,"%s\\",userChoice);
	}
	else {
		snprintf(path,pathLen,"%s",userChoice);
	}
		
	return path;
}

/*--------------------------------------------------------------------------------------------*/
/*
DESCRIPTION

	
INPUTS


OUTPUT

*/

char*
setParam(char* userChoice) 
{
	char* param=NULL;
	size_t len=strlen(userChoice)+1;
	
	param=calloc(len,sizeof(char));
	strncpy(param,userChoice,len);
	return param;
}

/*--------------------------------------------------------------------------------------------*/

int 
initSettings(struct settings *settings)
{
	settings->pathToLang=setPath("data\\lang");
	settings->lang=setParam("fr");
	settings->pathToHoliday=setPath("data\\holiday");
	settings->defaultHoliday=setParam("CH");	
	settings->dateType=setParam("eu");
	complYear(0,settings);

	return 0;
}

/*--------------------------------------------------------------------------------------------*/

int
showSettings(struct settings *settings)
{
	printf("\tlang\t\t: %s\n",settings->lang);
	printf("\tpathToLang\t: %s\n", settings->pathToLang);
	printf("\tpathToHoliday\t: %s\n", settings->pathToHoliday);
	printf("\tdefaultHoliday\t: %s\n",settings->defaultHoliday);
	printf("\tdateType\t: %s\n",settings->dateType);
	printf("\tautoYear\t: %d\n",settings->autoYear+1900);

return 0;
}




/*--------------------------------------------------------------------------------------------*/

/*
DESCRIPTION
	Valider l'argument "Feries" saisi par l'utilisateur et le formater pour permettre l'ouverture
	du fichier dans autre fonction
	
INPUTS
	listeFeries	= indique le pointeur qui recevra la liste de date � exclure
	canton		= liste de feries � utilis�e, saisi par l'utilisateur
	
OUPUT


*/

int 
validerEtFormaterFeries(char **listeFeries, struct settings *settings, char *canton)
{
	size_t len=strlen(settings->pathToHoliday)+strlen(canton)+5;
	FILE *fichier=NULL;
	
	*listeFeries=malloc(len*sizeof(char));
	snprintf(*listeFeries,len,"%s%s.txt",settings->pathToHoliday, canton);
	(*listeFeries)[len-1]='\0';
	
	fichier=fopen(*listeFeries,"r");
	
	if(fichier==NULL)
		{
		strcpy(*listeFeries,"CH.txt");
		printf("\n\tERREUR : Argument [canton] non valide\n Calcul effectue avec la liste par defaut CH");
		}
	fclose(fichier);
	return 0;
}

/*--------------------------------------------------------------------------------------------*/

/*
Valider argument "Date" saisi par l'utilisateur
et le formater pour permettre utilisation dans une autre fonction
-recuperer le string (saisie),
-v�rifier son format (nombre de s�parateurs et taille),
- copier les caract�res dans une structure (struct tm)
*/

int 
validerEtFormaterDate(struct tm *date, char *saisie, struct settings *settings)
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
			printf("\n\tFormat de date non valide. Format requis : jj.mm.aaaa ou j.m.aa");
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
		date->tm_year=settings->autoYear;
	}


return 0;	
}

/*--------------------------------------------------------------------------------------------*/

/*
Re�oit les dates debut et fin ainsi que la liste des feries et la taille de ce tab.
Elle convertie en time_t les struct tm re�ues puis teste chaque date afin de voir
si ce n'est pas : un f�ri�, un samedi, un dimanche.
Elle affiche ensuite le r�sultat (printf).
*/

int 
comparerDates(struct tm *debut, struct tm *fin, struct datevent *tabFeries, int tailleTabFeries)
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

printf("\n\tSamedi [%d]\tDimanche [%d]\tFeries [%d]\tOuvres [%d]\n",(int)nbSam,(int)nbDim,(int)nbFeries,(int)nbOuvres);
	
return 0;
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
				tabFeries[n].event[strlen(tamponSaisie)-1]='\0';
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


size_t
showHoliday(struct settings *settings, struct datevent *arHoliday, int arrSize, char *yearChoice) 
{
	size_t i=0, j=0;
	int year=0;
	char date[12]={0};
	struct tm structDate;
	struct tm *pStructDate=&structDate;
	
	if (yearChoice==NULL) {
		year=settings->autoYear;
	}
	else {
		year=atoi(yearChoice)-1900;
	}


	for (i=0; i<arrSize; i++) {
			pStructDate=localtime(&arHoliday[i].date);
			
			if(pStructDate->tm_year==year) {
				strftime(date,12,"%d.%m.%Y",pStructDate);
				printf("\n\t%s : %s", date, arHoliday[i].event);
				j++;			
			}
		}
	printf("\n");
	if(j==0)
		printf("\tNo holiday registred for this year.\n");

	
	return j;
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
