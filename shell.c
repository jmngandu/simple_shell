#include "shell.h"
/**
 * main - entry point
 * @ac: the count of arguements supplied
 * @av: an array of null terminated characters
 * Return: 0 on success 1 on failurer
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_d)
			: "r" (file_d));
	if (ac == 2)
	{
		file_d = open(av[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Open error! ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_d;
	}
	env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
