/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:45:27 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:15:52 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_path(void)
{
	t_list	*curr;

	curr = g_env.env_head;
	while (curr)
	{
		if (!strncmp(curr->content, "PATH", 4))
			return (curr->content + 5);
		curr = curr->next;
	}
	return (NULL);
}

char		*get_from_env(char *s)
{
	t_list	*curr;

	curr = g_env.env_head;
	while (curr)
	{
		if (!strncmp(curr->content, s, ft_strlen(s)))
			return (curr->content + ft_strlen(s) + 1);
		curr = curr->next;
	}
	return (NULL);
}
