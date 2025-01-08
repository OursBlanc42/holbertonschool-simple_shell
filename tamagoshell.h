#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

extern char **environ;

char *remove_newline(char *string);

int execute(char *string, char *av);

char **separate_arg(char *string);

void free_darray(char **darray);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void free_memory(char *command, char **child_argv);

char *duplicate_string(const char *string);

#endif
