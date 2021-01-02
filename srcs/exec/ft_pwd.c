/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:09:33 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:09:38 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void ft_pwd(char **argv)
{
    char    *pwd;

    argv = NULL;
    pwd = getcwd(NULL, 0);
    ft_putendl_fd(pwd, 1);
    free(pwd);
}
