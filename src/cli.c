#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/cli.h"

#define BUF_SIZE 100


/*--------------------- F U N C ------------------------------*/

int 
CLI_Prompt(char *buffer,FILE *stream, int option) {
	
	size_t bufLen=0;
	
	switch(option) {
		case 1:
			printf("\n$ ");
			break;
		default:
			break;
	}

	fgets(buffer,BUF_SIZE,stream);

	
	return 0;
}

/*--------------------- F U N C ------------------------------*/

int 
CLI_Interpret(char *buffer, char ***tabPointer, size_t *nb) 
{
	char *pCursor=buffer;
	size_t i=0, arg=2;
	size_t bufLen=strlen(buffer);
	int gui=1;
	
	for(i=0; i<=bufLen; i++) {
		if (buffer[i]==34) {
			gui*=(-1);
		}
		else if (buffer[i]==32 && gui==1) {
			arg++;
		} 
	}
	
	*tabPointer=malloc(arg*sizeof(char*));
	(*tabPointer)[0]=NULL;
	(*tabPointer)[1]=pCursor;
	
	for (i=0, arg=1; i<=bufLen; i++) {
		if (*pCursor==34) {
			if (gui==1) {
				(*tabPointer)[arg]=pCursor+1;
			}
			else {
				*pCursor='\0';
			}
			gui*=(-1);
			pCursor++;
		}
	else if (*pCursor==32 && gui==1) {
			*pCursor='\0';
			pCursor++;
			arg++;
			(*tabPointer)[arg]=pCursor;
		}
		else if (*pCursor=='\n') {
			*pCursor='\0';
		}
		else {
			pCursor++;
		}

	}
	
	*nb=arg;
	
return 0;
}

/*--------------------- F U N C ------------------------------*/

int 
CLI_DisplayArg(char **tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
	printf("\nElement [%lu]: %s",i,tabPointer[i]);
	}
return 0;
}

/*--------------------- F U N C ------------------------------*/

int 
CLI_FreePP(char*** tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
		free((*tabPointer)[i]);
		
	}
	free(*tabPointer);
	*tabPointer=NULL;
	
	return 0;
}
