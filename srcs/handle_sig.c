/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:41:05 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/27 15:41:06 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_sigint(int sig)
{
    if (sig == SIGINT) {
        g_minishell.return_code = 1;
        if (!g_minishell.forked)
        {
            ft_putendl_fd("\b\b  \b\b", 1);
            free(g_minishell.command_line);
            g_minishell.command_line = ft_strdup("");
            show_prompt();
        } else {
            g_minishell.return_code = 130;
            write(1, "\n", 1);
            // exit(130);
        }
    }
}
