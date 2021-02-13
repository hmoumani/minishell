/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:12:12 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 18:42:08 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					ft_handle_pipe(char *str)
{
	t_command	*cmd;
	int			p[2];

	cmd = g_minishell.cmd_tail->content;
	if (pipe(p) < 0)
	{
		ft_putendl_fd("pipe error", 2);
		exit(1);
	}
	cmd->out_red = p[1];
	cmd->pipe[0] = p[0];
	g_minishell.cmd_tail = ft_lstnew(ft_new_command(p[0], 1, p[1]));
	ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);
	str = NULL;
	g_minishell.read_next = PIPE;
	g_minishell.pos++;
	return (0);
}

static t_red_file	*ft_red_file(char *file, char type)
{
	t_red_file	*red_file;

	red_file = malloc(sizeof(t_red_file));
	red_file->file = file;
	red_file->type = type;
	return (red_file);
}

int					ft_handle_semi_column(char *str)
{
	t_command	*cmd;

	cmd = g_minishell.cmd_tail->content;
	g_minishell.cmd_tail = ft_lstnew(ft_new_command(0, 1, -1));
	ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);
	str = NULL;
	g_minishell.read_next = NULL;
	g_minishell.pos++;
	return (0);
}

int					ft_handle_input_red(char *str)
{
	if (ft_strequ(g_minishell.read_next, INPUT_RED))
	{
		ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->red_files,
		ft_lstnew(ft_red_file(str, 0)));
		g_minishell.read_next = NULL;
	}
	else
	{
		g_minishell.read_next = INPUT_RED;
		g_minishell.pos++;
	}
	return (0);
}

int					ft_handle_output_red(char *str, char *app)
{
	if (ft_strequ(g_minishell.read_next, OUTPUT_RED))
	{
		ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->red_files,
		ft_lstnew(ft_red_file(str, 1)));
		g_minishell.read_next = NULL;
	}
	else if (ft_strequ(g_minishell.read_next, APP_OUTPUT_RED))
	{
		ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->red_files,
		ft_lstnew(ft_red_file(str, 2)));
		g_minishell.read_next = NULL;
	}
	else
	{
		if (ft_strequ(app, APP_OUTPUT_RED))
			g_minishell.pos += 2;
		else
			g_minishell.pos++;
		g_minishell.read_next = app;
	}
	return (0);
}
