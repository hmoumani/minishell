/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:10:43 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:10:48 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(char **argv)
{
    // char *s1;
    int ret;

    g_env.home = get_home();
    if (argv[1])
        ret = chdir(argv[1]);
    else
    {
        ret = chdir(g_env.home);
    }
    if (ret < 0)
        ft_putstr_fd(strerror(errno), 2);
}
