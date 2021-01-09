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

void	move_dir(DIR *pdir, char *to_dir)
{
	char	*pfree;
	char	*current_directory;

	if (pdir != NULL)
	{
		add_element("OLDPWD", get_from_env("PWD"));
		chdir(to_dir);
		current_directory = getcwd(NULL, 0);
		if (current_directory == NULL)
		{
			pfree = ft_strjoin(get_from_env("PWD"), "/.");
			add_element("PWD", pfree);
			free(pfree);
			ft_fprintf(2, "cd: error retrieving current directory: getcwd: \
			cannot access parent directories: %s\n", strerror(errno));
		}
		else
		{
			add_element("PWD", current_directory);
		}
		free(current_directory);
	}
}

int		ft_env_change(DIR **pdir, char **to_dir, struct stat sb)
{
	if (!(*pdir = opendir(*to_dir)))
	{
		if (errno == 13 && (sb.st_mode & S_IXUSR))
		{
			add_element("OLDPWD", get_from_env("PWD"));
			chdir(*to_dir);
			*to_dir = getcwd(NULL, 0);
			add_element("PWD", *to_dir);
			free(*to_dir);
		}
		else
		{
			ft_fprintf(2, "minishell: cd: %s: %s\n", *to_dir, strerror(errno));
			return (1);
		}
	}
	return (0);
}

int		ft_cd(char **argv)
{
	DIR			*pdir;
	char		*to_dir;
	struct stat sb;

	if (argv[1] && *argv[1] == 0)
		argv[1] = ".";
	to_dir = !argv[1] || ft_strequ(argv[1], "~")
	? get_from_env("HOME") : argv[1];
	if (to_dir == NULL)
	{
		ft_fprintf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	stat(argv[1], &sb);
	if (ft_env_change(&pdir, &to_dir, sb))
		return (1);
	move_dir(pdir, to_dir);
	if (pdir)
		closedir(pdir);
	return (0);
}
