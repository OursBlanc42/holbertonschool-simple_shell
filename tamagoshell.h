#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

extern char **environ;

char *remove_newline(char *string);

int execute(char *string, char *av);

char **separate_arg(char *string);

void free_darray(char **darray);

#endif