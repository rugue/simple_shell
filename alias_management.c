#include "ishell.h"

/**
 * print_alias - display, add or delete aliases
 * @data: struct for the program's data
 * @alias: name of the alias to printed
 * Return: 0 if success, or other number if its declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int a, b, name_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		name_length = str_length(alias);
		for (a = 0; data->alias_list[a]; a++)
		{
			if (!alias || (str_compare(data->alias_list[a], alias, name_length)
				&&	data->alias_list[a][name_length] == '='))
			{
				for (b = 0; data->alias_list[a][b]; b++)
				{
					buffer[b] = data->alias_list[a][b];
					if (data->alias_list[a][b] == '=')
						break;
				}
				buffer[b + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[a] + b + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - Retrieve the value of an alias
 * @data: Program's data structure
 * @name: Name of the requested alias
 * Return: The value of the alias, or NULL if not found
 */
char *get_alias(data_of_program *data, char *name)
{
	int j, alias_size;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_size = str_length(name);

	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(name, data->alias_list[j], alias_size) &&
			data->alias_list[j][alias_size] == '=')
		{
			return (data->alias_list[j] + alias_size + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - create or update an alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: 0 if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int k, l;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (k = 0; alias_string[k]; k++)
		if (alias_string[k] != '=')
			buffer[k] = alias_string[k];
		else
		{
			temp = get_alias(data, alias_string + k + 1);
			break;
		}

	for (l = 0; data->alias_list[l]; l++)
		if (str_compare(buffer, data->alias_list[l], k) &&
			data->alias_list[l][k] == '=')
		{
			free(data->alias_list[l]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[l] = str_duplicate(buffer);
	}
	else
		data->alias_list[l] = str_duplicate(alias_string);
	return (0);
}
