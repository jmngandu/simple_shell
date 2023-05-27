#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read and wrtite buffers sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for converting a number functon */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: number off ields
 * @str: a string
 * @next: pointer to the to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains aarguements to pass to a function
 *@arg: a string from getline
 *@argv: an array of strings generated from arg
 *@line_count:  count
 *@err_num: error code
 *@linecount_flag: on count  line of input
 *@fname: program filename
 *@env: local copy of environ
 *@environ: custom copy of environ 
 *@history: history node
 *@alias: alias node
 *@env_changed: on, environ was changed
 *@status: return status of  prev exec command
 *@cmd_buf: address of pointer to cmd_buf
 *@cmd_buf_type: CMD_type
 *@readfd: the file_d from which to read line input
 *@histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin strings
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int get_builtin(info_t *);
void get_cmd(info_t *);
void _fork(info_t *);

/* parser.c */
int check_cmd(info_t *, char *);
char *cpy_chars(char *, int, int);
char *get_location(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *str_cpy(char *, char *, int);
char *str_cat(char *, char *, int);
char *str_chr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **str_tow(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void sfree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int my_free(void **);

/* _atoi.c */
int is_interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int err_atoi(char *);
void print_err(info_t *, char *);
int print_dec(int, int);
char *convert_num(long int, int, int);
void change_comments(char *);

/* builtin.c */
int _myexit(info_t *);
int _cd(info_t *);
int _help(info_t *);

/* builtin1.c */
int _history(info_t *);
int _alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandle(int);

/* getinfo.c */
void init_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int env_list(info_t *);

/* getenv.c */
char **find_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *find_history(info_t *info);
int create_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int number_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *ins_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void freeLists(list_t **);

/* lists1.c */
size_t lists_len(const list_t *);
char **list_of_strings(list_t *);
size_t printList(const list_t *);
list_t *node_starts_(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

