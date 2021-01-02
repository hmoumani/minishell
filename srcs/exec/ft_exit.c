/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:40:57 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:41:04 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_isnumber(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_exit_builtin(char **argv)
{
    int ret;

    if (!argv[1])
    {
        ft_fprintf(2, "exit\n"); 
        exit(0);
    }
    if (ft_ptr_str_len(argv) > 2)
    {
        ft_fprintf(2, "exit\n");
        ft_fprintf(2, "bash: exit: too many arguments\n");
        return ;
    }
    if (!ft_isnumber(argv[1]))
    {
        ft_fprintf(2, "exit\n"); 
        ft_fprintf(2, "bash: exit: %s: numeric argument required\n", argv[1]);
        exit(255);
    }
    ret = ft_atoi(argv[1]);
    ft_fprintf(2, "exit\n");
    exit(ret >= 0 && ret <= 255 ? ret : 0);
}
