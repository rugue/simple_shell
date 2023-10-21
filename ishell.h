#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>


#include "macros.h"

/**
 * struct info- struct for program's data
 * @program_name: name of the executable
 * @input_line: pointer to input read for _getline
 * @command_name: pointer to first cmd typed by the user
 * @exec_counter: number of excecuted cmds
 * @file_descriptor: file descriptor to input of commands
 * @tokens: pointer to array of splitd input
 * @env: copy of environ
 * @alias_list: array of pointers with aliases
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for builtins
 * @builtin: name of builtin
 * @function: associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/*========  shell.c  ========*/

void initialize_data(data_of_program *data, int arc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

int _getline(data_of_program *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

void resolve_variables(data_of_program *data);
void resolve_alias(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

void split(data_of_program *data);
char *_strtok(char *line, char *delim);


/*======== run.c ========*/

int run(data_of_program *data);


/*======== builtins_list.c ========*/

int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

char **split_path(data_of_program *data);
int find_program(data_of_program *data);


/*======== helpers_free.c ========*/

void free_array_of_pointers(char **directories);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);


/*======== builtins_more.c ========*/

int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

int builtin_env(data_of_program *data);
int builtin_set_env(data_of_program *data);
int builtin_unset_env(data_of_program *data);


/*======== env_management.c ========*/

char *env_get_key(char *name, data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);
void print_environ(data_of_program *data);


/*======== helpers_print.c ========*/

int _print(char *string);
int _printe(char *string);
int _print_error(int errorcode, data_of_program *data);


/*======== helpers_string.c ========*/

int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *alias);
int set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
