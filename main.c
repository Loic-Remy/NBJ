
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[3]={0};
char debut[11]={0};
char fin[11]={0};
char tampon[100]={0};
char **tabArguments=NULL;
size_t bufSize=50;

if (argc==1) {
	
	recupererLigneCmde(&tabArguments,bufSize);
	}
else {
	strcpy(canton,argv[1]);
	strcpy(debut,argv[2]);
	strcpy(fin,argv[3]);
}

char *fichierFeries=NULL;
struct datevent *tabFeries=NULL;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;

//printf("Canton: %s\tDebut: %s\tFin: %s",canton, debut, fin);

validerEtFormaterFeries(&fichierFeries,canton);

//printf("\nFichier a ouvrir: %s",fichierFeries);

tabFeries=chargerListeFeries(&fichierFeries,ptrTailleTab);

comparerDates(debut,fin,tabFeries,tailleTab);


return 0;
}
