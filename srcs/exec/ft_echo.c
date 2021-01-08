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
		add_element("_", argv[0]);
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
		ft_putstr_fd(argv[i++], 1);
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	add_element("_", argv[i - 1]);
	if (!n)
		ft_putstr_fd("\n", 1);
}
