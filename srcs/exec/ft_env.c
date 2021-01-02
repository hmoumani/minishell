/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:23:22 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:23:25 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_env(char **argv)
{
    t_list *curr;

    curr = g_env.env_head;
    argv = NULL;
    while (curr)
    {
        if (ft_strchr(curr->content, '='))
        {
            ft_putstr_fd(curr->content, 1);
            ft_putstr_fd("\n", 1);
        }
        curr = curr->next;
    }
}