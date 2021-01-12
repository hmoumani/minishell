/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:06:10 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 11:41:35 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			open_file(char *file, int flags, char *type)
{
	int			fd;
	t_command	*cmd;
	int			red;
	char		*cfile;

	cfile = ft_strdup(file);
	file = ft_quotes_convert(ft_convert_env(cfile));
	cmd = g_minishell.cmd_head->content;
	red = ft_strequ(type, INPUT_RED) ? cmd->in_red : cmd->out_red;
	if (red > 2)
		close(red);
	if (ft_strequ(type, INPUT_RED))
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		g_minishell.return_code = 1;
		g_minishell.stat = 0;
	}
	free(file);
	return (fd);
}

void		open_red_file(void *f, void *c)
{
	int			fd;
	t_red_file	*red_file;
	t_command	*cmd;

	red_file = f;
	cmd = c;
	if (red_file->type == 0)
	{
		fd = open_file(red_file->file, O_RDONLY, INPUT_RED);
		cmd->in_red = fd;
	}
	else if (red_file->type == 1)
	{
		fd = open_file(red_file->file, O_WRONLY | O_CREAT |
		O_TRUNC, OUTPUT_RED);
		cmd->out_red = fd;
	}
	else if (red_file->type == 2)
	{
		fd = open_file(red_file->file, O_WRONLY | O_CREAT | O_APPEND,
		APP_OUTPUT_RED);
		cmd->out_red = fd;
	}
}

static void	ft_free_red_file(void *ptr)
{
	t_red_file	*red_file;

	red_file = ptr;
	free(red_file->file);
	free(red_file);
}

void		open_redirect_files(t_command *cmd)
{
	ft_lstiter(cmd->red_files, open_red_file, cmd);
}

void		free_redirect_files(void)
{
	t_list		*lst;
	t_command	*cmd;

	lst = g_minishell.cmd_head;
	if (!lst)
		return ;
	while (lst != NULL)
	{
		cmd = lst->content;
		ft_lstclear(&cmd->red_files, ft_free_red_file);
		lst = lst->next;
	}
}
