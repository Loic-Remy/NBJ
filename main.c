
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{
size_t bufSize=50;
char buffer[50];
char *fichierFeries=NULL;
struct datevent *tabFeries=NULL;
struct tm debut={0}, fin={0};
struct tm *ptDebut=&debut, *ptFin=&fin;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;
int autoYear=0;

complYear(0,&autoYear);

do {

if (argc==1) {
	printf("\n(%d) $ ",autoYear+1900);
	fgets(buffer,bufSize,stdin);
	recupererLigneCmde(&argv,buffer,bufSize);
	}

/*DEBUT ZONE DE TEST
size_t i=0;
for (i=0; i<=argc; i++) {
	printf("\nArgument [%d] : %s",i, argv[i]);
	}

printf("\n");
system("PAUSE");
FIN ZONE DE TEST */

//printf("Cmde: %s\tCanton: %s\tDebut: %s\tFin: %s",argv[1], argv[2], argv[3], argv[4]);


if (strcmp(argv[1],"calc")==0) {
	
	validerEtFormaterFeries(&fichierFeries,argv[2]);
	tabFeries=chargerListeFeries(&fichierFeries,ptrTailleTab);	
	validerEtFormaterDate(ptDebut,argv[3],autoYear,0);
	validerEtFormaterDate(ptFin,argv[4],autoYear,0);	
	comparerDates(ptDebut,ptFin,tabFeries,tailleTab);
	argc=1;
	}
else if (strcmp(argv[1],"loc")==0) {
	
	argc=1;	
	}
else if (strcmp(argv[1],"edit")==0) {
	
	argc=1;	
	}
else if (strcmp(argv[1],"set")==0) {
	
	if (strcmp(argv[2],"year")==0) {
		
		complYear(atoi(argv[3]),&autoYear);	
		printf("\n\tParametre '%s' a ete modifie. Nouvelle valeur = %d.\n",argv[2],autoYear+1900);	
	}
	
	argc=1;	
	}
else if (strcmp(argv[1],"show")==0) {
	
	if (strcmp(argv[2],"year")==0) {
		printf("\n\tParametre '%s' = %d.\n",argv[2],autoYear+1900);	
	}	
		
	argc=1;
	}		
else if (strcmp(argv[1],"help")==0) {
		
	help();
	argc=1;
	}	
else if (strcmp(argv[1],"exit")==0) {
		
	exit(EXIT_SUCCESS);
	}		
else {
		
	printf("\nCommande inconnue. Tapez la commande 'help' pour obtenir de l'aide.\n");
	argc=1;
	}		

//printf("\n");
//system("PAUSE");

}
while (strcmp(argv[1],"exit")!=0);

return 0;
}
