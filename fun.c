#include "minishell.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

int pid = 0;
extern char prompt[30];

void my_strrev(char *str)
{
    int i=0,j=strlen(str)-1;
    while(i<j)
    {
        char temp = str[i];
        str[i]=str[j];
        str[j]=temp;

        i++;j--;
    }
}

void own_handler(int signum)
{
    if(signum == SIGINT)
    {
        if(pid == 0)
        {
            printf("\n\033[1;32m%s:\033[0m", prompt);
             fflush(stdout);
        }
    }
    if(signum == SIGTSTP)
    {
        if(pid==0)
        {
            printf("\n\033[1;32m%s:\033[0m", prompt);
            fflush(stdout);
        }
        
    }
}

void execute_external_command(char **argv)
{
    //count the commands
    int command_position[100];
    int command_count = 1;
    int i=0;

    command_position[0]=0;
    int k=1;

    while (argv[i]!=NULL)
    {
        /* code */
        if(strcmp(argv[i],"|")==0)
        {
            argv[i]=NULL;
            command_position[k++]=i+1;
            command_count++;
        }
        i++;
    }

    int prev_read = -1;

    for (int i = 0; i < command_count; i++)
    {
        int fd[2];

        /* Create pipe except for last command */
        if (i != command_count - 1)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)       // Child
        {
            /* Read from previous pipe */
            if (prev_read != -1)
            {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }

            /* Write into next pipe */
            if (i != command_count - 1)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }

            execvp(argv[command_position[i]], argv + command_position[i]);

            perror("execvp");
            exit(EXIT_FAILURE);
        }

        /* Parent */

        if (prev_read != -1)
            close(prev_read);

        if (i != command_count - 1)
        {
            close(fd[1]);
            prev_read = fd[0];
        }
    }

    if (prev_read != -1)
    {
        close(prev_read);
    }

    /* Wait for all children */
    for (int i = 0; i < command_count; i++)
    {
        wait(NULL);
    }
}

void scan_input(char *prompt, char *input_string)
{
    signal(SIGINT, own_handler);
    signal(SIGTSTP,own_handler);
    system("clear");                 //clear before entering to minishell
    //print prompt

    while(1)
{
    printf("\033[1;32m%s:\033[0m", prompt);

    //read input string
    if (fgets(input_string, 100, stdin) == NULL)
    {
        clearerr(stdin);
        continue;
    }

    input_string[strcspn(input_string, "\n")] = '\0';
    //if input string has PS1 = new
    /*
    update promt stringf as new, means read from n to null
    */
      if(strstr(input_string,"PS1")!=NULL)
   {
        char str[100];
        int i = strlen(input_string)-1;
        int k=0;
        while(i>=0)
        {
            if(input_string[i]=='=')
            {
                str[k]='\0';
                break;
            }
            str[k++] = input_string[i--];
        }

        my_strrev(str);

        //memset(prompt, 0, sizeof(prompt));

        strcpy(prompt,str);
   }

   //tokenise the commands
    char *argv[50];
    int i=0;

    char *tokenised_commands=strtok(input_string," ");

    while(tokenised_commands!=NULL)
    {
        argv[i++]=tokenised_commands;
        tokenised_commands = strtok(NULL," ");
    
    }
    argv[i]=NULL;

    if (argv[0] == NULL)
    {
        continue;
    }


    //char *command = get_command(argv[0]);

    int ret = check_command_type(argv[0]);

 //   free(command);


    if(ret == 1)
    {
        execute_internal_command(argv);
    }
    else if(ret == 2)
    {
        int status;
        pid = fork();
        if(pid > 0)
        {
            waitpid(pid,&status, WUNTRACED);
            pid = 0;
        }
        else if(pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            execute_external_command(argv);
            exit(EXIT_SUCCESS);
        }
    }
    else
    {
        printf("Command not found\n");
    }


}

}


int check_command_type(char *cmd)
{
    	char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

            char *external_commands[] = {
    "bash","ls","date", "cal", "who", "whoami", "hostname", "uname",
    "echo", "cat", "cp", "mv", "rm", "mkdir", "rmdir", "touch",
    "chmod", "chown", "ln", "find", "locate", "which", "whereis",
    "grep", "egrep", "fgrep", "sort", "uniq", "cut", "paste",
    "tr", "wc", "head", "tail", "less", "more", "diff", "cmp",
    "comm", "tar", "gzip", "gunzip", "zip", "unzip", "ps", "top",
    "kill", "killall", "sleep", "clear", "man", "df", "du", "free",
    "mount", "umount", "ping", "curl", "wget", "scp", "ssh", "nano",
    "vi", "vim", "gcc", "g++", "make", "ld", "objdump", "nm",
    "strings", "file", "env", "printenv", "xargs", "awk", "sed", "bc",
    NULL
};


    for(int i=0;builtins[i]!=NULL ;i++)
    {
        if(strcmp(cmd,builtins[i])==0)
        {
            return 1;
        }
    }

        for(int i=0;external_commands[i]!=NULL ;i++)
    {
        if(strcmp(cmd,external_commands[i])==0)
        {
            return 2;
        }
    }

    return 0;
}


void execute_internal_command(char **argv)
{
    /* pwd */
    if (strcmp(argv[0], "pwd") == 0)
    {
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("pwd");
    }

    /* cd */
    else if (strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)
        {
            char *home = getenv("HOME");

            if (home != NULL)
                chdir(home);
        }
        else
        {
            if (chdir(argv[1]) == -1)
                perror("cd");
        }
    }

    /* echo */
    else if (strcmp(argv[0], "echo") == 0)
    {
        if (argv[1] == NULL)
        {
            printf("\n");
        }
        else if (strcmp(argv[1], "$$") == 0)
        {
            printf("%d\n", getpid());
        }
        else if (strcmp(argv[1], "$SHELL") == 0)
        {
            printf("%s\n", getenv("SHELL"));
        }
        else if (strcmp(argv[1], "$HOME") == 0)
        {
            printf("%s\n", getenv("HOME"));
        }
        else if (strcmp(argv[1], "$PATH") == 0)
        {
            printf("%s\n", getenv("PATH"));
        }
        else
        {
            int i = 1;

            while (argv[i] != NULL)
            {
                printf("%s ", argv[i]);
                i++;
            }
            printf("\n");
        }
    }

    /* exit */
    else if (strcmp(argv[0], "exit") == 0)
    {
        exit(0);
    }

    else
    {
        printf("%s: Command not found\n", argv[0]);
    }
}
