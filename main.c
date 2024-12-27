#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
* main - Entry point
* Description : Simple shell
* Return: Nothing (waiting to ctrl + c (abort))
*/

int main(void)
{
	/* declare & initialize variable */
	char *string = NULL;
	char *emoji = "( ・‿・) > ";
	size_t buffer_size = 0;
	ssize_t readed;
	pid_t child_pid;
	int index = 0;

	while (1)
	{
		/* Waiting for input */
		printf("%s",emoji);

		/* Read the input and check if succeed */
		readed = getline(&string, &buffer_size, stdin);

		if (readed == -1)
			{
				printf("\nヾ(• ֊ •) Good bye !\n");
				break;
			}

		/* fork current process and check if succeed */
		child_pid = fork();

		if (child_pid == -1)
		{
			printf("(╯°□°）╯︵ ┻━┻ (Error fork)\n");
			continue;
		}

		/* clean string (remove last \n char) */
		for(index=0; string[index] != '\0'; index++)
		{
			if(string[index] == '\n')
			{
				string[index] = '\0';
			}
		}

		/* setup argv[] for execve */
		char *argv[] = {string, NULL };

		/* execute child process */
		if (child_pid == 0)
		{
			/* Check and execute command if no error */
			if (execve(argv[0], argv, NULL) == -1)
			{
				printf("1: %s: not found\n",argv[0]);
				continue;
			}
		}

		/* waiting for child finish execution */
		else
		{
				wait(NULL);
				continue;
		}
	}
}


