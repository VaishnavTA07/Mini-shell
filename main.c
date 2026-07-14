#include "minishell.h"
#include<stdio.h>

char prompt[30]="Minishell ";

int main()
{
    char input_string[40];

    scan_input(prompt, input_string);
}