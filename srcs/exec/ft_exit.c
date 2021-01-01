/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:40:57 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:41:04 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_exit_buildin(char **argv)
{
    if (!argv[1])
        exit(0);
    // TODO: needs some magic here, 200 is randmoly picked
    exit(200);
}
