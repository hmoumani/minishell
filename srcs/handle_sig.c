/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:57:12 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 15:23:08 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_sigquit(int sig)
{
	if (!g_minishell.forked)
		ft_putstr_fd("\b\b  \b\b", 1);
	else
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(sig, 2);
		write(2, "\n", 1);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell.return_code = 1;
		if (!g_minishell.forked)
		{
			ft_putendl_fd("\b\b  \b\b", 1);
			free(g_minishell.command_line);
			g_minishell.command_line = ft_strdup("");
			show_prompt(NULL);
		}
		else
		{
			g_minishell.return_code = 130;
			write(1, "\n", 1);
		}
	}
	else if (sig == SIGQUIT)
	{
		is_sigquit(sig);
	}
}
