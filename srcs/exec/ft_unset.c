/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:21:04 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:21:09 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		customized_len(char *s)
{
	int len;

	len = 0;
	while (s[len] && s[len] != '=')
	{
		len++;
	}
	return (len);
}

void	delete_node(char *s)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = g_env.env_head;
	if (tmp != NULL && !strncmp(tmp->content, s, customized_len(tmp->content)))
	{
		g_env.env_head = tmp->next;
		ft_lstdelone(tmp, free);
		return ;
	}
	while (tmp != NULL && strncmp(tmp->content, s,
	customized_len(tmp->content)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	ft_lstdelone(tmp, free);
}

int		ft_unset(char **argv)
{
	int		i;
	int		ret;
	char	*s;

	s = "not a valid identifier";
	i = 1;
	ret = 0;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_fprintf(2, "minishell: unset: `%s': %s\n", argv[i], s);
			ret = 1;
			i++;
			continue ;
		}
		delete_node(argv[i]);
		i++;
	}
	return (ret);
}
