#include "shell.h"


/**
* get_args: This retrieve a command from input.
* @line: This is a buffer that stores command.
* @exe_ret: This returns the value of the last command
* Return: if any error occurs return NULL or a pointer to store command.
*
*/
char *args_getter(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize read;
	char *prompt = "$";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}
	line[read -1] = '\0';
	variable_replacement (&line, exe_ret);
	handle_line(&line, read);

	return(line);
}

/**
* call_args - partitions operators from commands and calls them.
*@fronts - An array of arguments.
*@ args - A double pointer to the beginning of args.
*@exe_ret:  The return value of the parent process last executed command.
*return: Value of the last executed command.
*/ 

int args_caller(char **args, char **front, int *exe_ret)
{
	int ret,index;

	if(!args[0])
		return *exe_ret;
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret ! = 0)
			{
				arg = &args[++index];
				index = 0;
			}
			else
			{
				for (index++;args[index]; index++)
					free(args[index]);
				return ret;
		}
		}
		else if(_strncmp(args[index], "&&", 2)==0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front,exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{	for (index++; args[index]; index++)
					free(args[index]);
				return(ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}
/**
*run_args - calls the execution of a command.
*@args an array of arguments.
*@front: a double pointer to the beginning of args.
*@exe_ret : the return value of the parent process last executed command
*
*/
int args_runner(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char, **front);

	bulitin = get_builtin(arg[0]);

	if(builtin)
	{
	
	ret = builtin(args +1, front);
	if (ret!= EXIT)
		*exe_ret = ret;
	}	
	histt++;

	for(i=0; args[i]; i++)
		free(args[i]);

	return (ret);
}
/**
* handles_args : gets call and runs the execcution of commands
*@exe_ret - This return the value of the parent of thr process last command executed.
*return - when end-of-file is read - END_OF_FILE (-2).
*if the input cannot be tokenized  --1
* 0/w - the exit value of the last executed command.
*/

int args_handler(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;
	
	line = get_args(line, exe_ret);
	if(!line)
		return (END_OF_FILE);
	
	args = _strtok(line, " ");
	free(line);
	if(!args)
		return (ret);
	if (check_args(args) ! = 0)
	{
		*exe_ret = 2;
		free_args(args,args);
		return(*exe_ret);
	}
	front = args;
	
	for = (index =0;args[index]; index++)
	{	
		if (_strncmp(args[index], ";",1) ==0)
	{
		free(args[index]);
		args[index] = NULL;
		ret = call_args(args,front,exe_ret);
		args = &args[++index];
		index = 0;
	}
		}
	if (args)
		ret =call_args(args, front, exe_ret);
		
	free(front);
	return (ret);
}
/**
*check_args - checks if there are any leading ";",";;","&&" or "||"
*@args: 2D pointer to tokenized commands and arguments.
*return : if a ";", "&&", or "||" is palced  at an invalid position - 2.
* Otherwise - 0.
*/
int args_checker(char **args)
{	
	size_t i;
	char *cur, *nex;

	for(i = 0; args[i];i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] =='&' || cur[0] =='|')
	{
		if (i==0 || cur[1] ==';')
			if(i ==0 || cur[1] == ';')
	return (create_error(args[i],2));
		nex = args[i + 1];
		if (nex &&(nex[0] ==';' ||nex [0] == '&' || nex[0] =='|'))
			return (create_error(&args[i+1], 2));
	
		}
	}
		return (0);
}
