#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

extern char **environ;

/**
 * struct built_in - structure for the function built-in
 *
 *@name_func: command use by users
 *@function_built: function call by command
 */
typedef struct built_in
{
	char *name_func;
	void (*function_built)(void);
} search_built;


char *remove_newline(char *string);

int execute(char *string, char *av);

char **separate_arg(char *string);

void free_darray(char **darray);

void display_env(void);

void built_exit(void);

void *search_built_in(char *search);

#endif
