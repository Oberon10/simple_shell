#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#define END_OF_FILE -2
#define EXIT_ -3

/* This is a global Environment */
extern char **environ;

/* The Global program */
char *name;

/* This is the global history counter */
int hist;

/**
* struct builtin_s - struct type defining builtin commands
* @name: this maps to the name of the alias builtin.
* @f:  function pointer that points to the builtin command's function
*/
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv,char **front);
} builtin_t;

/**
* struct list_s - This struct type define a linked list.
* @dir: This is a directory path.
* @next: This is a pointer to struct list_s.
*/
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


/**
* struct alias_s - this is a new struct defining aliases_s
* @name: name of the alias
* @value: value of the alias
* @next: pointer to the next struct alias_s
*/
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *next;
} alias_t;

/* This is global aliases linked-list */
alias_t *aliases;

/* This is the main helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
/*char **_strtok(char *cmd);*/
char *get_loc(char *cmd);
list_t *get_dir_path(char *path);
int exec(char **args, char **front);
void list_free(list_t *head);
char *_itoa(int num);

/* This is the input  helpers */
int args_handler(int *exe_ret);
int args_checker(char **args);
void args_free(char **args, char **front);
char **aliases_replace(char **args);
void line_handler(char **line, ssize_t read);
void var_replacement(char **args, int *exe_ret);
char *args_getter(char *line, int *exe_ret);
int args_caller(char **args, char **front, int *exe_ret);
int args_runner(char **args, char **front, int *exe_ret);

/* String function */
char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char **_strtok(char *line, char *delim);

/* The Builtin helpers */
void env_free(void);
char **envcopy(void);
char **_getenv(const char *var);

/* The shell Builtin Functions */
int (*get_builtin(char *cmd))(char **args, char **ahead);
int shell_exit(char **args, char **ahead);
int shell_env(char **args, char __attribute__((__unused__)) **ahead);
int shell_setenv(char **args, char __attribute__((__unused__)) **ahead);
int shell_unsetenv(char **args, char __attribute__((__unused__))**ahead);
int shell_cd(char **args, char __attribute__((__unused__)) **ahead);
int shell_alias(char **args, char __attribute__((__unused__)) **ahead);
int shell_help(char **args, char __attribute__((__unused__)) **ahead);

/* The Linkedlist helpers */
void alias_list_free(alias_t *head);
alias_t *alias_add_end(alias_t **head, char *name, char *value);
list_t *add_node_end(list_t **head, char *dir);
void list_free(list_t *head);

/*error handling */
char *err_2_cd(char **args);
char *err_2_syntax(char **args);
char *err_126(char **args);
char *err_127(char **args);
int create_err(char **args, int error);
char *env_error(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);

/* Other prototypes */
void all_help(void);
void alias_help(void);
void help_help(void);
void exit_help(void);
void cd_help(void);
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void help_hist(void);
int proc_file_cmd(char *file_path, int *exe_ret);

#endif /* SHELL_H */
