/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:16:25 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/11 19:16:26 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **argv)
{
	char	*pwd;

	argv = NULL;
	if (!(pwd = ft_strdup(get_from_env("PWD"))))
		pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
