#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

#include <sys/types.h>

extern char **environ;

/**
 * struct list_s - singly linked list
 * @string: string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
char *string;
struct list_s *next;
} list_t;
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

int execute(char *string, char *av, int line_number);

char **separate_arg(char *string);

void free_darray(char **darray);

void display_env(void);

void built_exit(void);

void (*search_built_in(char *search))(void);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

char *_getenv(const char *search);

list_t *add_node_end(list_t **head, const char *str);

list_t *chopper(char *string, char *separator);

void free_list(list_t *head);

char *_which(char *target_program);

char *concat_path(const char *base, const char *addendum);

void cleanup_error(char *exec_path, char **child_argv, char *argv);

int check_built_in(char *string);

void prompt_user(void);

int end_file(ssize_t readed);

#endif
