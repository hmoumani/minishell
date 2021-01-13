/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:48:00 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 17:36:58 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_handle_cmd(char *str)
{
	int			len;
	char		*arg;
	t_command	*cmd;

	len = ft_word_length(str, SEP, 0);
	str = ft_substr(str, 0, len);
	arg = str;
	if (ft_strequ(g_minishell.read_next, INPUT_RED))
		ft_handle_input_red(arg);
	else if (ft_strequ(g_minishell.read_next, OUTPUT_RED) ||
	ft_strequ(g_minishell.read_next, APP_OUTPUT_RED))
		ft_handle_output_red(arg, g_minishell.read_next);
	else if (arg)
	{
		cmd = g_minishell.cmd_tail->content;
		ft_lstadd_back(&cmd->argv, ft_lstnew(arg));
	}
	g_minishell.read_next = NULL;
	return (0);
}

t_command	*ft_new_command(int in, int out, int pipe)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->argv = NULL;
	cmd->in_red = in;
	cmd->out_red = out;
	cmd->red_files = NULL;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = pipe;
	return (cmd);
}

void		ft_free_command(void *cmd)
{
	ft_lstclear(&((t_command *)cmd)->argv, free);
	free(cmd);
}
