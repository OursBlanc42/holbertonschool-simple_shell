#ifndef TAMAGOSHELL_H
#define TAMAGOSHELL_H

extern char **environ;

char *remove_newline(char *string);

int execute(char *string, char *av);

char **separate_arg(char *string);

void free_darray(char **darray);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

char *_getenv(const char *search);

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

list_t *add_node_end(list_t **head, const char *str);

list_t *chopper(char *string, char *separator);

void free_list(list_t *head);

char *_which(char *target_program);

char *concat_path(const char *base, const char *addendum);

#endif
