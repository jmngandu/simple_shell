#include "shell.h"
/**
 * main - my shell program
 *@ac: is the arguement count
 *@argv: an array of null terminated strings
 * Return: 0 on success
*/
int main(int ac, char **av, char **env)
{
	if(ac == 1)
		prompt(av, env);
	return (0);
}
