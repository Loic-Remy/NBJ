
#ifndef H_CLI_H
#define H_CLI_H


typedef int CLI_ErrorCode;

enum CLI_ErrorCode {
	CLI_SUCCESS,
	CLI_MEMORYERROR,
	CLI_FILEERROR,
	CLI_MISSENDQUOTE,
	CLI_ALREADYFREE,
	CLI_NOCOMMAND
};

CLI_ErrorCode CLI_Prompt(const char *str, char *buffer, FILE *stream);
CLI_ErrorCode CLI_Interpret(char *buffer, char ***tabPointer, size_t *nb);
int CLI_DisplayArg(char **tabPointer, size_t nb);
CLI_ErrorCode CLI_FreeArg(char** tabPointer, size_t *nbArg);
void CLI_DisplayError(CLI_ErrorCode error);

size_t CLI_shapeCmdLine(char *cmdLine);
char **CLI_parseCmdLine(char *cmdLine, size_t nbArg);


#endif

