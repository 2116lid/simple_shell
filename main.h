#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

#define BUF_SIZE_R 1024
#define BUF_SIZE_W 1024
#define BUF_FLUSH -1
#define _TOUPPER	1
#define _TOSIGNED	2
#define NEW_FILE_HIST	".shell_history"
#define NEW_FILE_HIST_MAX	4096
#define COM_OM		0
#define COM_OR		1
#define COM_AND		2
#define COM_CHIN	3
#define R_FLINE 0

extern char **environ;

/**
 * struct listsig - a struct for single linked list.
 * @num: the number field.
 * @str: a string.
 * @next: points to the next node.
 */
typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct newaddres - a struct for different functions.
 * @arg: a string generated from getline.
 * @argv:an array of strings generated from arg.
 * @path: is string path for the current command.
 * @argc: the argument count.
 * @er_count: the error count.
 * @error_cod: the error code for exit.
 * @ercount_flag: if on count this line of input.
 * @fname: the program filename.
 * @env: linked list local copy of environ.
 * @environ: modified copy of environ from Linked List env.
 * @newhi: a node for history.
 * @alias: the alias node.
 * @chd_env: on if environ was changed.
 * @sta: the return status of final command.
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_bufType: CMD_type ||, &&, ; .
 * @readfd: the fd from which to read line input.
 * @line_hist_num: the history line number count
 */
typedef struct newaddres
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int er_count;
	int error_cod;
	int ercount_flag;
	char *fname;
	list_t *env;
	list_t *newhi;
	list_t *alias;
	char **environ;
	int chd_env;
	int sta;
	char **cmd_buf;
	int cmd_bufType;
	int readfd;
	int line_hist_num;
} addres_t;

#define ADDRES_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct build - struct for builtin functions.
 * @type: the command flag.
 * @func: the Differnt functions.
 */
typedef struct build
{
	char *type;
	int (*func)(addres_t *);
} build_custom;


void cust_puts(char *);
int cust_putchar(char);
int wr_ch(char c, int fd);
int in_str(char *str, int fd);
int hsh(addres_t *, char **);
int built_search(addres_t *);
void com_path(addres_t *);
void _comfork(addres_t *);
int _strlen(char *);
int _strcmp(char *, char *);
char *see_string(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **new_strtow(char *, char);
int det_executable(addres_t *, char *);
char *ch_duplicate(char *, int, int);
char *_searchpath(addres_t *, char *, char *);
char *cust_memset(char *, char, unsigned int);
void _strfree(char **);
void *_cust_reallo(void *, unsigned int, unsigned int);
int new_exit(addres_t *);
int com_nd(addres_t *);
int new_help(addres_t *);
int interact(addres_t *);
int _delimeter(char, char *);
int alpha(int);
int _atoi(char *);
ssize_t get_nline(addres_t *);
int _getline(addres_t *, char **, size_t *);
void blo_ctrl(int);
char *get_file(addres_t *addres);
int hist_write(addres_t *addres);
int _histR(addres_t *addres);
int hist_list(addres_t *addres, char *buf, int linecount);
int _histnum(addres_t *addres);
int che_chadeli(addres_t *, char *, size_t *);
void _ifcont(addres_t *, char *, size_t *, size_t, size_t);
int replace_alias(addres_t *);
int var_toke(addres_t *);
int str_change(char **, char *);
list_t *add_node(list_t **, const char *, int);
list_t *add_endnode(list_t **, const char *, int);
size_t str_only(const list_t *);
int delete_node(list_t **, unsigned int);
void all_free(list_t **);
char **cpy_environ(addres_t *);
int _unsetenv(addres_t *, char *);
int _setenv(addres_t *, char *, char *);
char *new_getenv(addres_t *, const char *);
int new_env(addres_t *);
int new_setenv(addres_t *);
int new_unsetenv(addres_t *);
int _env_list(addres_t *);
void ad_new(addres_t *);
void ad_set(addres_t *, char **);
void ad_free(addres_t *, int);
size_t list_len(const list_t *);
char **_to_string(list_t *);
size_t _listall(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t get_indexnode(list_t *, list_t *);
int new_history(addres_t *);
int new_alias(addres_t *);
int _newatoi(char *);
void err_msg(addres_t *, char *);
int deci_out(int, int);
char *num_converter(long int, int, int);
void comm_replace(char *);
int dir_null(addres_t *addres);
void env_uptodate(addres_t *addres, char buffer[1024]);
void err_chdir(addres_t *addres);
int handle_dash(addres_t *addres, char *s);
int free_ptr(void **);

#endif
