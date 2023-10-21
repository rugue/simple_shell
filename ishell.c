#include "ishell.h"
/**
 * main - Entry point for the shell program
 * @argc: Number of arguments from the command line
 * @argv: Array of command line arguments
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}



/**
 * handle_ctrl_c - this function prints a new line and the prompt
 * when the program receives a SIGINT signal (ctrl + c)
 * @UNUSED: option of prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}


/**
 * initialize_data - set up struct with the program information
 * @data: pointer to data structure
 * @argv: array of arguments passed to program execution
 * @env: environment variables passed to program execution
 * @argc: number of values received from command line
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int j = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[j]; j++)
		{
			data->env[j] = str_duplicate(env[j]);
		}
	}
	data->env[j] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
	{
		data->alias_list[j] = NULL;
	}
}
/**
 * sisifo - it's an infinite loop that shows prompt
 * @prompt: prompt for printing
 * @data: it's an infinite loop that shows prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int status = 0, length = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
			status = length = _getline(data);

		if (status == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (length >= 1)
		{
			resolve_alias(data);
			resolve_variables(data);
			split(data);
			if (data->tokens[0])
			{
				status = run(data);
				if (status != 0)
					_print_error(status, data);
			}
			free_recurrent_data(data);
		}
	}
}
