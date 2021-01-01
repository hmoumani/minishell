/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:07:08 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:07:13 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_echo(char **argv)
{
    int i;

    i = 1;
    if (!strcmp(argv[1], "-n"))
        i = 2;
    while (argv[i])
    {
        ft_putstr_fd(argv[i], 1);
        i++;
        if (argv[i])
            ft_putstr_fd(" ", 1);
    }
    if (strcmp(argv[1], "-n"))
        ft_putstr_fd("\n", 1);
}