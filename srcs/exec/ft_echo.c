/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:16:04 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:16:05 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		to_skip(char *s)
{
	int i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **argv)
{
	int i;
	int n;

	n = 0;
	if (!argv[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	i = 1;
	while (argv[i] && to_skip(argv[i]))
	{
		n = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}
