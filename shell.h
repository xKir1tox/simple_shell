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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for _ex_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_line_fetcher 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* my prototype for_shloop.c */
int in_hsh(info_t *, char **);
int in_find_builtin(info_t *);
void vo_find_cmd(info_t *);
void vo_fork_cmd(info_t *);

/* my prototype for_parser.c */
int in_cmd(info_t *, char *);
char *dual_chars(char *, int, int);
char *get_prs_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* my prototype for_errors.c */
void _showstr(char *);
int _showchr(char);
int _showfd(char c, int fd);
int _showsfd(char *str, int fd);

/* my prototype for_string.c */
int _lenthofstr(char *);
int _comparstr(char *, char *);
char *begain_with(const char *, const char *);
char *_cantostr(char *, char *);

/* my prototype for_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* my prototype for_exits.c */
char *_clones_str(char *, char *, int);
char *_contas_str(char *, char *, int);
char *_chars_str(char *, char);

/* my prototype for_tokenizer.c */
char **side_str(char *, char *);
char **side_str2(char *, char);

/* my prototype for_realoc_str.c */
char *_set_memory(char *, char, unsigned int);
void _str_free_array(char **);
void *_realoc_str(void *, unsigned int, unsigned int);

/* my prototype for_memory.c */
int bfree(void **);

/* my prototype for_slicer.c */
int _interact_mode(info_t *);
int _is_delmed(char, char *);
int _is_alphed(int);
int _slicer(char *);

/* my prototype for_errors1.c */
int _erratoi(char *);
void _show_error(info_t *, char *);
int _show_d(int, int);
char *_ex_num(long int, int, int);
void del_comm(char *);

/* my prototype for_builtin.c */
int the_exit(info_t *);
int the_cd(info_t *);
int the_help(info_t *);

/* my prototype for_builtin1.c */
int _the_history(info_t *);
int _the_alias(info_t *);

/*my prototype for_line_fetcher.c */
ssize_t input_fetcher(info_t *);
int _line_fetcher(info_t *, char **, size_t *);
void sigin_dealer(int);

/* my prototype for_getinfo.c */
void info_remover(info_t *);
void info_setter(info_t *, char **);
void info_set_free(info_t *, int);

/* my prototype for_environ.c */
char *env_fetcher(info_t *, const char *);
int _the_env(info_t *);
int _the_env_setter(info_t *);
int _the_env_declear(info_t *);
int _the_env_list_oop(info_t *);

/* my prototype forenv_fetcher.c */
char **environ_getter(info_t *);
int environ_declear(info_t *, char *);
int environ_setter(info_t *, char *, char *);

/* my prototype for_history.c */
char *history_file_catcher(info_t *info);
int history_file_writer(info_t *info);
int history_file_reader(info_t *info);
int history_list_builder(info_t *info, char *buf, int linecount);
int history_numb_changer(info_t *info);

/* my prototype for_lists.c */
list_t *incrs_noods(list_t **, const char *, int);
list_t *incrs_end_noods(list_t **, const char *, int);
size_t string_list_printer(const list_t *);
int index_noods_deleter(list_t **, unsigned int);
void lists_are_free(list_t **);

/* my prototype for_lists1.c */
size_t lists_length(const list_t *);
char **lists_are_strings(list_t *);
size_t lists_printer(const list_t *);
list_t *what_noods_start(list_t *, char *, char);
ssize_t index_noods_fetcher(list_t *, list_t *);

/* my prototype for_vars.c */
int chain_it_is(info_t *, char *, size_t *);
void chain_checker(info_t *, char *, size_t *, size_t, size_t);
int rep_my_alias(info_t *);
int rep_my_vars(info_t *);
int rep_my_string(char **, char *);

/* my prototype for ma_getLine.c */
ssize_t input_fetcher(info_t *info);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
void sigin_dealer(__attribute__((unused))int sig_num);
int _line_fetcher(info_t *info, char **ptr, size_t *length);

#endif

