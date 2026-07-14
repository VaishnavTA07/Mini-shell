#ifndef MINISHELL_H
#define MINISHELL_H

void scan_input(char *prompt,char *input_string);

int check_command_type(char *cmd);

char* get_command(char *input_string);

void execute_external_command(char **argv);

void execute_internal_command(char **argv);

#endif