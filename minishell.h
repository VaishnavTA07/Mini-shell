#ifndef MINISHELL_H
#define MINISHELL_H
#include <sys/types.h>

void scan_input(char *prompt,char *input_string);

int check_command_type(char *cmd);

char* get_command(char *input_string);

void execute_external_command(char **argv);

void execute_internal_command(char **argv);

void delete_job(pid_t pid);

void insert_job(pid_t pid, char *cmd);

struct node{
    char command[20];
    int pid;
    struct node *link;
};


typedef struct job
{
    int job_no;
    pid_t pid;
    char command[100];
    struct job *next;
} JOB;          //for fg, bg, jobs

#endif