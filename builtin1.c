#include "shell.h"

/**
 * _myhistory - helps display the hist list, command by line, preceded
 * with line numbs, start at 0.
 * @info: Structure contains potential args. used to maintain
 * constant functn prot.
 * Return: always return 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - set alias to str
 * @info: parametre struct
 * @str: the str alias
 *
 * Return: always return 0 on sucss, eror on 1
 */
int unset_alias(info_t *info, char *str)
{
	char *p, a;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = a;
	return (ret);
}

/**
 * set_alias - this set alias to str
 * @info: parametre struct
 * @str: str alias
 *
 * Return: always return 0 on sucss, error on 1
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - this prints alias str
 * @node: alias nod
 *
 * Return: always 0 on succss, error 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - this resembles alias builtin
 * @info: struct contain potential args. Use to maintai
 *          constant functn prototype.
 *  Return: always return 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
