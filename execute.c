#include "ishell.h"
/**
 * run - runs a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucesssful returns zero, otherwise, return -1.
 */
int run(data_of_program *data)
{
	int the_retval = 0, status;
	pid_t pidd;

	the_retval = builtins_list(data);
	if (the_retval != -1)
		return (the_retval);

	the_retval = find_program(data);
	if (the_retval)
	{
		return (the_retval);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			the_retval = execve(data->tokens[0], data->tokens, data->env);
			if (the_retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
