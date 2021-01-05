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
    DIR		*pdir;
    // char *pfree;
	char	*to_directory;
	char	*current_directory;

	to_directory = !argv[1] ? get_from_env("HOME") : argv[1];
	pdir = opendir(to_directory);
	if (pdir != NULL)
	{
        add_element("OLDPWD", ft_strdup(get_from_env("PWD")));
		chdir(to_directory);
		current_directory = getcwd(NULL, 0);
        
		if (current_directory == NULL)
        {
            add_element("PWD", ft_strjoin(get_from_env("PWD"), "/."));
			ft_fprintf(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
        }
		else
			add_element("PWD", current_directory);
	}
	if (pdir)
		closedir(pdir);
}
