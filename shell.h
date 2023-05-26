#ifndef SHELL_H
#define SHELL_H
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
void prompt(char **av, char **env);
void exec(char **argv);
#endif
