#include "shell.h"

/**
 * is_cmd - this determines if file is exeutable cmd
 * @info: the info struct
 * @path: the path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - this helps duplicate characters
 * @pathstr: this is the PATH string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: points to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[k++] = pathstr[a];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - this finds commd in the PATH str
 * @info: the info struct
 * @pathstr: the PATH str
 * @cmd: the cmd to search
 *
 * Return: the path of cmd if found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
