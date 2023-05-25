#include "shell.h"
/**
 * prompt - displays a prompt
 * @av: an array of null terminated strings
 * @env: an array of environment variables
 * Return: void
*/
void prompt(char **av, char **env)
{
	char *user_input = NULL;
	int i;
	size_t n = 0;
	char *prompt = "cisfun$ ";
	ssize_t num_char_read = 0;
	char *argv[] = {NULL, NULL};
	pid_t pid;
	(void)av;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 8);
		num_char_read = getline(&user_input, &n, stdin);
		if (num_char_read == -1)
		{
			free(user_input);
			exit(EXIT_FAILURE);
		}
		for (i = 0; user_input[i]; i++)
		{
			if (user_input[i] == '\n')
				user_input[i] = 0;
		}
		argv[0] = user_input;
		pid = fork();
		if (pid == -1)
		{
			free(user_input);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				perror("./shell");
		}
		else
			wait(NULL);
	}
}
