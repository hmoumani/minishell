/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:23:22 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:23:25 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_custom_print(char *s, char **argv)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, "env", 3))
		{
			ft_putstr_fd(argv[0], 1);
			return ;
		}
		ft_putchar_fd(s[i], 1);
		i++;
	}
}

void	ft_env(char **argv)
{
	t_list *curr;

	curr = g_env.env_head;
	while (curr)
	{
		if (ft_strchr(curr->content, '='))
		{
			if (!ft_strncmp(curr->content, "_=", 2))
				ft_custom_print(curr->content, argv);
			else
				ft_putstr_fd(curr->content, 1);
			ft_putstr_fd("\n", 1);
		}
		curr = curr->next;
	}
}
