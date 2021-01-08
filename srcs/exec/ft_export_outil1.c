/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_outil1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/07 16:13:03 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			show_all_export(char *start_with)
{
	t_list *curr;

	curr = g_env.env_head;
	while (curr)
	{
		if (!strncmp(curr->content, "_=", 2))
		{
			curr = curr->next;
			continue ;
		}
		ft_putstr_fd(start_with, 1);
		ft_print_path(curr->content);
		ft_putstr_fd("\n", 1);
		curr = curr->next;
	}
}

int				ft_export(char **argv)
{
	if (!argv[1])
	{
		show_all_export("declare -x ");
		add_element("key", argv[0]);
	}
	else
		return (export_all(argv));
	return (0);
}

int				ft_ptr_str_len(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void			export_name(char *argv)
{
	if (lstchr(g_env.env_head, argv))
		return ;
	ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(argv)));
}

void			export_empty_string(char **argv, char **sp, int i)
{
	t_list	*node;
	char	*pfree;

	if ((node = lstchr(g_env.env_head, argv[i])))
	{
		pfree = node->content;
		node->content = ft_strjoin(argv[i], "");
		free(pfree);
	}
	else
	{
		ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strjoin(argv[i], "")));
	}
	sp = NULL;
}
