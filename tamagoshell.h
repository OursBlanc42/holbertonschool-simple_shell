#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

extern char **environ;

char *remove_newline(char *string);

int execute(char *string, char *av);

#endif
