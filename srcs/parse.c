/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:43:20 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 18:44:35 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_skip_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int			get_next_word(const char *str, char *d)
{
	int		i;
	char	quote[2];

	i = ft_skip_space(str);
	ft_bzero(quote, 2);
	while (str[i])
	{
		if (!quote[0] || ft_on_char(str, i, quote))
		{
			if (ft_on_char(str, i, "'\""))
				quote[0] = quote[0] ? 0 : str[i];
			if (!ft_on_char(str, i, d) || ft_on_char(str, i, d))
				break ;
		}
		i++;
	}
	i += ft_skip_space(str + i);
	return (i);
}

int			ft_precess_cmd(char *str)
{
	t_command	*cmd;

	cmd = g_minishell.cmd_tail->content;
	if (((ft_strncmp(str, OUTPUT_RED, 1) == 0 ||
	ft_strncmp(str, APP_OUTPUT_RED, 2) == 0
	|| ft_strncmp(str, INPUT_RED, 1) == 0) && (g_minishell.read_next != NULL &&
	!ft_strequ(g_minishell.read_next, PIPE))) ||
	((ft_strncmp(str, PIPE, 1) == 0 || ft_strncmp(str, SEMI_COLUMN, 1) == 0) &&
	(g_minishell.read_next != NULL ||
	(cmd->argv == NULL && cmd->red_files == NULL))))
		return (ft_syntax_error(str));
	if (ft_strncmp(str, PIPE, 1) == 0)
		ft_handle_pipe(str);
	else if (ft_strncmp(str, SEMI_COLUMN, 1) == 0)
		ft_handle_semi_column(str);
	else if (ft_strncmp(str, INPUT_RED, 1) == 0)
		ft_handle_input_red(str);
	else if (ft_strncmp(str, APP_OUTPUT_RED, 2) == 0)
		ft_handle_output_red(str, APP_OUTPUT_RED);
	else if (ft_strncmp(str, OUTPUT_RED, 1) == 0)
		ft_handle_output_red(str, OUTPUT_RED);
	else
		ft_handle_cmd(str);
	return (0);
}

void		ft_parse(void)
{
	int	len;

	while (g_minishell.stat && g_minishell.command_line[g_minishell.pos] &&
	(g_minishell.pos += get_next_word(g_minishell.command_line +
	g_minishell.pos, SEP)) != -1)
	{
		if (g_minishell.command_line[g_minishell.pos] == 0)
			break ;
		len = ft_word_length(g_minishell.command_line + g_minishell.pos, SEP);
		ft_precess_cmd(g_minishell.command_line + g_minishell.pos);
		g_minishell.pos += len;
	}
}
