/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_outil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:17:00 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:17:01 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_valid_identifier(char *s)
{
	int i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && s[i] != '_' && !ft_isdigit(s[i]))
			if (!(s[i] == '+' && !s[i + 1]))
				return (0);
		i++;
	}
	return (1);
}

int				custem_len(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (i);
		i++;
	}
	return (i);
}

t_list			*lstchr(t_list *head, char *s)
{
	t_list	*curr;
	int		len;

	if (!s)
		return (NULL);
	len = custem_len(s);
	curr = head;
	while (curr)
	{
		if (!ft_strncmp(s, curr->content, len) && (*(((char *)curr->content)
		+ len) == '=' ||
		*(((char *)curr->content) + len) == '\0'))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int				in(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void			ft_print_path(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		if (s[i] == '=')
			break ;
		i++;
	}
	if (!strchr(s, '='))
		return ;
	i++;
	ft_putchar_fd('"', 1);
	while (s[i])
	{
		if (in("\"$\\", s[i]))
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(s[i], 1);
		i++;
	}
	ft_putchar_fd('"', 1);
}
