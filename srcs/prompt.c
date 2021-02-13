/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:38:33 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/13 10:56:10 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_getcwd(void)
{
	char	*cwd;
	char	*home;
	char	*res;
	int		len;

	cwd = getcwd(NULL, 0);
	home = ft_get_var("HOME");
	len = ft_strlen(home);
	res = "~";
	if (len && ft_strncmp(home, cwd, len) == 0)
	{
		free(home);
		home = ft_substr(cwd, len, ft_strlen(cwd) - len);
		res = ft_strjoin(res, home);
	}
	else
		res = getcwd(NULL, 0);
	free(home);
	free(cwd);
	return (res);
}

void			show_prompt(char *type)
{
	char	*cwd;

	if (!type)
	{
		cwd = ft_getcwd();
		ft_mprint(BBLU, cwd, " ", NULL);
		ft_mprint(g_minishell.return_code ? BRED : BGRN, "> ", RESET, NULL);
		free(cwd);
	}
	else if (ft_strequ(type, PIPE))
		ft_putstr_fd("pipe > ", 2);
}

int				is_command(char *s)
{
	if (ft_strequ(s, "echo"))
		return (1);
	if (ft_strequ(s, "cd"))
		return (2);
	if (ft_strequ(s, "pwd"))
		return (3);
	if (ft_strequ(s, "export"))
		return (4);
	if (ft_strequ(s, "unset"))
		return (5);
	if (ft_strequ(s, "env"))
		return (6);
	if (ft_strequ(s, "exit"))
		return (7);
	return (0);
}

char			*join_path(char *s, char *s1, char *s2)
{
	char *temp;
	char *pfree;

	temp = ft_strjoin(s, s1);
	pfree = temp;
	temp = ft_strjoin(temp, s2);
	free(pfree);
	return (temp);
}
