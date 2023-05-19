#include "shell.h"

/**
 * _myenv - this prints currnt envirnment
 * @info: struct contains potential args. For maintaining
 *          const functn prototyp.
 * Return: always return 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - this helps to get value of an environ variable
 * @info: Structu contains potent args. for maintaining
 * @name: envi varia name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - helps Initialize new env var,
 *             or modify existing 1
 * @info: struct contains potent args. Used for maintain
 *        constant function prototype.
 *  Return: always ret 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect numb of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - this remove env var
 * @info: struct contains potential args which use maintain
 *        const functn prototype
 * Return: always ret zero0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - this populate env linked-list
 * @info: Struct contains potent args for maintaining
 *          const functn prototype
 * Return: always return zero0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
