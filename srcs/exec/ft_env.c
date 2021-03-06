/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:15:57 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:15:59 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **argv)
{
	t_list *curr;

	curr = g_env.env_head;
	argv = NULL;
	while (curr)
	{
		if (ft_strchr(curr->content, '='))
		{
			ft_putstr_fd(curr->content, 1);
			ft_putstr_fd("\n", 1);
		}
		curr = curr->next;
	}
}
