/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:17 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:04:01 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int			ft_strequ(char *s1, char *s2)
{
	int len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	return (ft_strncmp(s1, s2, len + 1) == 0);
}

char		*ft_strappend(char *str, char c)
{
	char	strchar[2];
	char	*tmp;

	tmp = str;
	strchar[0] = c;
	strchar[1] = 0;
	str = ft_strjoin(str, strchar);
	free(tmp);
	return (str);
}

int			ft_syntax_error(char *token)
{
	if (*token == '\x4')
		ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
	else
	{
		if (*token == '\n')
			token = "newline";
		else if (ft_strncmp(token, APP_OUTPUT_RED, 2) == 0)
			token = ">>";
		else
			token[1] = 0;
		ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	}
	g_minishell.return_code = 258;
	g_minishell.stat = 0;
	g_minishell.read_next = NULL;
	return (1);
}

int			ft_endwith_pipe(void)
{
	int i;

	i = ft_strlen(g_minishell.command_line) - 1;
	while (i >= 0 && g_minishell.command_line[i] == ' ')
		i--;
	if (i >= 0 && g_minishell.command_line[i] == '|')
		return (1);
	return (0);
}
