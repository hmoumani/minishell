#include "minishell.h"


int ft_endwith_pipe()
{
    int i;

    i = ft_strlen(g_minishell.command_line) - 1;
    while (i >= 0 && g_minishell.command_line[i] == ' ')
        i--;
    if (i >= 0 && g_minishell.command_line[i] == '|')
        return (1);
    return (0);
}