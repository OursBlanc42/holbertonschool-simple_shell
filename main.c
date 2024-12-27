#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
* main - Entry point of the simple shell
* Description :
*	Display a prompt
*	Read user input
*	Clean string (remove \n character )
*	Fork current process to child process and execute the command
*	Waiting child execution and display a prompt again
* Return: Always 0 (waiting abort (ctrl+c) or EOF (ctrl+d)
*/

int main(void)
{
	char *string = NULL;
	size_t buffer_size = 0;
	ssize_t readed;
	pid_t child_pid;
	int index = 0;
	char *argv[2];
	argv[1] = NULL;

	while (1)
	{
		/* Waiting for input */
		printf("( ・‿・) > ");

		/* Read the input and check if succeed */
		readed = getline(&string, &buffer_size, stdin);
		if (readed == -1)
		{
			printf("\nヾ(• ֊ •) Good bye !\n");
			break;
		}

		/* clean string (remove last \n char) */
		for (index = 0; string[index] != '\0'; index++)
		{
			if (string[index] == '\n')
				string[index] = '\0';
		}

		/* fork current process and check if succeed */
		child_pid = fork();
		if (child_pid == -1)
		{
			printf("(╯°□°）╯︵ ┻━┻ (Error fork)\n");
			continue;
		}

		/* Execute the command in child process */
		if (child_pid == 0)
		{
			argv[0] = string;
			if (execve(argv[0], argv, NULL) == -1)
			{
				printf("1: %s: not found\n", argv[0]);
				continue;
			}
		}

		/* waiting for child finish execution */
		else
			wait(NULL);
	}

	return (0);
}


