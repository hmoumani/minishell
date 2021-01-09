/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:50:41 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/09 11:50:43 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_endwith_pipe(void)
{
	int i;

	i = ft_strlen(g_minishell.command_line) - 1;
	while (i >= 0 && g_minishell.command_line[i] == ' ')
		i--;
	if (i >= 0 && g_minishell.command_line[i] == '|')
		return (1);
	return (0);
}
