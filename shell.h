#ifndef _SHELL_H_
#define _SHELL_H_
#include<fnctl.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>

#define End_of_file -2
#define EXIT -3

/* Global Environmnt*/
extern char **environ;
/* Global program */
char *name;
/* Global history counter */
int histy;

/***
* struct list_s This struct type define a linked list.
*@dir: This is a directory path.
*@next: This is a pointer to struct list_s.
*/

typef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
* struct builtin_s - struct type defining builtin commands
*@name - this maps to the name of the alias.
*@ -  A function pointer to the builtin command's functions
*/
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv,char **front);
}
builtin_t;

/**
*
struct alias_s this is a struct definning aliases_s.
*/
typedef struct alias_s
{
	char 8name;
	char *value;
	struct alias_s *next;
}
alias_t;
/* Global aliases linkedd list */
alias_t *aliases;
/*main helper*/
ssize_t _getline(char **linptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *command);
char *get_locaion(char * command);
list_t *get_pat_dir(char ** ffront):
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);
/*input  helpers*/
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char ** args, char **front, int *exe_ret);
int run_args(char **args, char **front, int, int *exe_ret);
int handle_args(int *exe_ret);
int check_ arg(char **args);
void free_args(char **args, char **front);
char ** replace_aliases(char **args);

/* String function */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *srn, size_t n);
char *_strcpy(char *dest, const char *srn);
char _strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char 8s1, char *s2);
int _strncmp(const char *s1, const char 8s2, size_t n);


/*Builtins*/
int (*get_builtin(char * command))(char **args, char **front);
int shellby_exit(char **args, char ** front);
int shellby_env(char **args, char _attribute_((_unused_)) **front);
int shellby_setenv(char **args, char _attribute_((_unused)) **front);
int shellby_unsetenv(char **args, char _attribute_((_unused))**front);
int shellby_cd(char **args, char _attribute_((_unused)) **front);
int shellby_alias(char **args, char _attribute_((_unused)) **front);
int shellby_help(char ** args, char _attribute_((_unused)) **front);

/*Builtin helpers*/
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);


/*error handling */
int create_error(char **args, int err);
char * error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char ** args);
char *error_127(char **args);

/*Linkedlist helper*/
alias_t *add_alias_end(alias_t **head, char *name, char *values);
void freee_alias_list(alias_t *head);
list_t *add-node_end(list_t **head, char 8dir);
void free_list(list_t *head);

void help_all(void)
void help_alias(void);
void help_cd(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);
int proc_file_commands(char *file_path, int *exe_ret);
