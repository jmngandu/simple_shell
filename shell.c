#include "shell.h"
/**
 * main - my shell program
 *@ac: is the arguement count
 *@argv: an array of null terminated strings
 * Return: 0 on success
*/
int main(int ac, char **argv)
{
	char *token, *prompt = "cisfun$ ";
	char *userInput = NULL, *userInput_copy = NULL;
	size_t n = 0;
	const char *delim = " \n";
	int numtokens = 0;
	int i;
	pid_t pid;
	(void)ac;
	while (1)
	{
		write(STDOUT_FILENO, prompt, 8);
		if (getline(&userInput, &n, stdin) == -1)
		{
			free(userInput);
			exit(EXIT_FAILURE);
		}
		userInput_copy = malloc(sizeof(char) * n);
		if (userInput_copy == NULL)
		{
			perror("memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcpy(userInput_copy, userInput);
		token = strtok(userInput, delim);
		while (token)
		{
			numtokens++;
			token = strtok(NULL, delim);
		}
		numtokens++;
		argv = malloc(sizeof(char *) * numtokens);
		token = strtok(userInput_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			free(userInput);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			exec(argv);
		else
			wait(NULL);
	}
	free(userInput_copy);
	free(userInput);
	return (0);
}
