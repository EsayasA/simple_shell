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
#define HF	".simple_shell_hist"
extern char **environ;
/**
 * struct liststr - struct
 * @num:number
 * @str:string
 * @next:next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - struct function
 *@arg:string argument
 *@argv:vector array
 *@path:command to path
 *@argc:size argument
 *@count:count
 *@ernum:error
 *@flag:controller
 *@name:file name
 *@env:environ
 *@environ:value
 *@hist:past code in linked struct
 *@alias:alias
 *@newf:check if env is changer
 *@status:check for status
 *@cmd_buf:command buffer
 *@cmd_buf_type:command types for ||, &&, ;
 *@fd:fd
 *@histcount:counts
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count;
	int ernum;
	int flag;
	char *name;
	list_t *env;
	list_t *hist;
	list_t *alias;
	char **environ;
	int newf;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int fd;
	int histcount;
} adrs_t;

#define ADRS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - struct with function
 *@type:flag
 *@func:function
 */
typedef struct builtin
{
	char *type;
	int (*func)(adrs_t *);
} builtin_table;

int chain_che(adrs_t *, char *, size_t *);
void checker(adrs_t *, char *, size_t *, size_t, size_t);
int token_replace(adrs_t *);
int token_var(adrs_t *);
int strpl(char **, char *);

int hsh(adrs_t *, char **);
int search_builtin(adrs_t *);
void search_command(adrs_t *);
void split_fork(adrs_t *);

int _command(adrs_t *, char *);
char *_duplicate(char *, int, int);
char *_search(adrs_t *, char *, char *);

int loophsh(char **);

void print_input(char *);
int put_char(char);
int write_char(char c, int fd);
int print_char(char *str, int fd);

int str_len(char *);
int str_cmp(char *, char *);
char *be_gin(const char *, const char *);
char *str_cat(char *, char *);

char *str_cpy(char *, char *);
char *str_dup(const char *);
void _put(char *);
int _putchar(char);

char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_ch(char *, char);

char **split_str(char *, char *);
char **split_str2(char *, char);

char *my_memset(char *, char, unsigned int);
void _free(char **);
void *re_alloc(void *, unsigned int, unsigned int);

int buffer_free(void **);
int _active(adrs_t *);
int _delimeter(char, char *);
int _alphabet(int);
int at_oi(char *);

int error_atoi(char *);
void display_error(adrs_t *, char *);
int display_decimal(int, int);
char *conv_num(long int, int, int);
void rem_comm(char *);

int my_exit(adrs_t *);
int my_cd(adrs_t *);
int my_help(adrs_t *);

int my_hist(adrs_t *);
int my_alias(adrs_t *);

ssize_t _getinput(adrs_t *);
int get_line(adrs_t *, char **, size_t *);
void handle(int);

void delete_adrs(adrs_t *);
void intialization_adrs(adrs_t *, char **);
void free_adrs(adrs_t *, int);

char *get_env(adrs_t *, const char *);
int my_env(adrs_t *);
int my_setenv(adrs_t *);
int my_unsetenv(adrs_t *);
int fill_list(adrs_t *);

char **get_environ(adrs_t *);
int env_unset(adrs_t *, char *);
int env_set(adrs_t *, char *, char *);

char *print_history(adrs_t *info);
int create_hist(adrs_t *info);
int display_hist(adrs_t *info);
int his_list(adrs_t *adrs, char *buf, int linecount);
int renew_hist(adrs_t *adrs);

list_t *rah_esu(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);
size_t display_str(const list_t *);
int del_indx(list_t **, unsigned int);
void _listf(list_t **);

size_t list_len(const list_t *);
char **display_for_str(list_t *);
size_t ptr_ls(const list_t *);
list_t *start_indx(list_t *, char *, char);
ssize_t get_indx(list_t *, list_t *);

#endif
