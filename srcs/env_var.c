/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:26:55 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 18:36:18 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_env_sep = "'\"$\\?=," SEP;

char	*ft_get_var(char *name)
{
	char	*res;
	t_list	*lst;

	lst = lstchr(g_env.env_head, name);
	if (lst == NULL)
		return (ft_strdup(""));
	res = ft_strchr(lst->content, '=');
	if (res == NULL)
		return (ft_strdup(""));
	return (ft_strdup(res + 1));
}

char	*ft_replace_env(char *str, char *res, int *i, int len)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr(str, *i, len);
	(*i) += len;
	var = ft_get_var(tmp);
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, var);
	free(var);
	free(tmp);
	return (res);
}

char	*ft_lastcmd_return_env(char *res, int *i)
{
	char	*var;
	char	*tmp;

	var = ft_itoa(g_minishell.return_code);
	tmp = res;
	res = ft_strjoin(res, var);
	free(var);
	free(tmp);
	(*i) += 2;
	return (res);
}

char	*ft_append(char *str, char *res, int *i)
{
	res = ft_strappend(res, str[*i]);
	(*i)++;
	return (res);
}

char	*ft_convert_env(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (ft_on_char(str, i, "$") &&
		(len = ft_word_length(str + i + 1, g_env_sep, 1)) > 0)
		{
			i++;
			if (ft_strchr("0123456789", str[i]) && i++)
				continue;
			res = ft_replace_env(str, res, &i, len);
		}
		else if (str[i + 1] == '?')
			res = ft_lastcmd_return_env(res, &i);
		else
			res = ft_append(str, res, &i);
	}
	free(str);
	return (res);
}
