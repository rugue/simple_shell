#include "ishell.h"

/**
 * builtin_exit - Terminate the program with a status
 * @data: Struct for the program’s data
 * 
 * Return: 0 if successful, or another number if specified in the arguments
 */
int builtin_exit(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - Switch to a different directory
 * @data: Struct for the program’s data
 * 
 * Return: 0 if successful, or another number if specified in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *home_dir = env_get_key("HOME", data), *prev_dir = NULL;
	char buffer[128] = {0};
	int status = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			prev_dir = env_get_key("OLDPWD", data);
			if (prev_dir)
				status = set_work_directory(data, prev_dir);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (status);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(buffer, 128);

		return (set_work_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_work_directory - Update the working directory
 * @data: Struct for the program’s data
 * @new_dir: Path to be used as the working directory
 * 
 * Return: 0 if successful, or another number if specified in the arguments
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char buffer[128] = {0};
	int err_code = 0;
	
	if (getcwd(buffer, 128) == NULL) {
		perror("getcwd");
		return 3;
	}

	if (!str_compare(buffer, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", buffer, data);
	return (0);
}

/**
 * builtin_help - Display the help information for the shell
 * @data: Struct for the program’s data
 * 
 * Return: 0 if successful, or another number if specified in the arguments
 */
int builtin_help(data_of_program *data)
{
	int i, len = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (i = 0; messages[i]; i++)
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], messages[i], len))
		{
			_print(messages[i] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - Manage aliases for commands
 * @data: Struct for the program’s data
 * 
 * Return: 0 if successful, or another number if specified in the arguments
 */
int builtin_alias(data_of_program *data)
{
	int j = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++j])
	{
		if (count_characters(data->tokens[j], "="))
			set_alias(data->tokens[j], data);
		else
			print_alias(data, data->tokens[j]);
	}

	return (0);
}
