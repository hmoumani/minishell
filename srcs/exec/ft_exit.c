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
    if (s[i] == '-')
        i++;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

int  ft_exit_builtin(char **argv)
{
    int ret;
    int error;

    error = 0;
    if (!argv || !argv[1])
    {
        ft_fprintf(2, "exit\n"); 
        exit(g_minishell.return_code);
    }
    if (ft_ptr_str_len(argv) > 2)
    {
        ft_fprintf(2, "exit\n");
        ft_fprintf(2, "minishell: exit: too many arguments\n");
        return (1);
    }
    if (!ft_isnumber(argv[1]))
    {
        ft_fprintf(2, "exit\n"); 
        ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
        exit(255);
    }
    ret = ft_custom_atoi(argv[1], 0, &error);
    ft_fprintf(2, "exit, %d, %d\n", ret, error);
    // if ((ret == -1 && argv[1][0] != '-') || ret == -2)
    //     exit(255);
    // if (ret > 255)
    //     exit(ret - 1 - 255);
    // else if (ret < 0)
    //     exit(256 + ret);
    // else
    //     exit(ret);
    if (error)
    {
        ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
        exit(255);
    }
    if (ret > 255)
        exit(ret - 1 - 255);
    else if (ret < 0)
        exit(256 + ret);
    else
        exit(ret);
    return (0);
}
