#include "shell.h"
/**
 *exec - executes the command user types
 *@argv: an array of null terminated strings
 *return: 0 on success
*/
void exec(char **argv)
{
	char *cmd = NULL;

	if (argv)
	{
		cmd = argv[0];
		/*execute the command, checking whether its a success or not*/
		if (execve(cmd, argv, NULL) == -1)
		{
			perror("./shell");
		}
	}
}
