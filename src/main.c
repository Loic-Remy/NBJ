
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"
#include "cli.h"

#define BUF_SIZE 100


int main(int argc, char *argv[]) 
{
char buffer[BUF_SIZE];
char *fichierFeries=NULL;
char **tabArg=NULL;
size_t nbArg=1;
struct datevent *tabFeries=NULL;
struct tm debut={0}, fin={0};
struct tm *ptDebut=&debut, *ptFin=&fin;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;
int autoYear=0;
char *path=NULL;

setPath("data/",&path);
complYear(0,&autoYear);

do {

if (argc==1 && nbArg==1) {
	printf("\n(%d) $ ",autoYear+1900);
	CLI_Prompt(buffer,0);
	CLI_Interpret(buffer,&tabArg,&nbArg);
	}
else {
	tabArg=argv;
	argv=NULL;
	nbArg=argc;
	argc=0;
}

//	CLI_DisplayTabP(tabArg,nbArg);


if (strcmp(tabArg[1],"calc")==0) {
	
	validerEtFormaterFeries(&fichierFeries,tabArg[2]);
	tabFeries=chargerListeFeries(&fichierFeries,ptrTailleTab);	
	validerEtFormaterDate(ptDebut,tabArg[3],autoYear,0);
	validerEtFormaterDate(ptFin,tabArg[4],autoYear,0);	
	comparerDates(ptDebut,ptFin,tabFeries,tailleTab);
	

	nbArg=1;
	}
else if (strcmp(tabArg[1],"loc")==0) {
	

	nbArg=1;	
	}
else if (strcmp(tabArg[1],"edit")==0) {
	

	nbArg=1;	
	}
else if (strcmp(tabArg[1],"set")==0) {
	
	if (strcmp(tabArg[2],"year")==0) {
		
		complYear(atoi(tabArg[3]),&autoYear);	
		printf("\n\tParametre '%s' a ete modifie. Nouvelle valeur = %d.\n",tabArg[2],autoYear+1900);	
	}
	

	nbArg=1;	
	}
else if (strcmp(tabArg[1],"show")==0) {
	
	if (strcmp(tabArg[2],"year")==0) {
		printf("\n\tParametre '%s' = %d.\n",tabArg[2],autoYear+1900);	
	}	

	
	nbArg=1;
	}		
else if (strcmp(tabArg[1],"help")==0) {
		
	help();
	

	nbArg=1;
	}	
else if (strcmp(tabArg[1],"exit")==0) {
		
	exit(EXIT_SUCCESS);
	}		
else {
		
	printf("\nCommande inconnue. Tapez la commande 'help' pour obtenir de l'aide.\n");
	
	
	nbArg=1;
	}		

//printf("\n");
//system("PAUSE");

}
while (strcmp(tabArg[1],"exit")!=0);

return 0;
}
