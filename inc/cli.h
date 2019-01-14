

int CLI_Prompt(char buffer[],int option);

int CLI_Interpret(char *buffer, char ***tabPointer, size_t *nb);

int CLI_DisplayTabP(char **tabPointer, size_t nb);

int CLI_FreePP(char*** tabPointer, size_t nb);
