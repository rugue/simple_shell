#include "ishell.h"

/**
 * builtin_env - displays the environment variables of the shell
 * @data: struct for the program's data
 * Return: 0 if sucess, or other number if its declared in arguments
 */
int builtin_env(data_of_program *data)
{
	int j;
	char name_copy[50] = {'\0'};
	char *value_copy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (j = 0; data->tokens[1][j]; j++)
		{
			if (data->tokens[1][j] == '=')
			{
				value_copy = str_duplicate(env_get_key(name_copy, data));
				if (value_copy != NULL)
					env_set_key(name_copy, data->tokens[1] + j + 1, data);

				print_environ(data);
				if (env_get_key(name_copy, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(name_copy, value_copy, data);
					free(value_copy);
				}
				return (0);
			}
			name_copy[j] = data->tokens[1][j];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - Set a new environment variable or modify an existing 1
 * @data: struct for the program's data
 * Return: 0 if sucess, or other number if its declared in the arguments
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - Remove an existing environment variable
 * @data: struct for the program's data
 * Return: 0 if successful, or another number if specified in the arguments
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
