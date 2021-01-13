/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:10:26 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 19:08:17 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *s)
{
	char		**sp;
	int			i;
	struct stat sb;

	i = 0;
	sp = ft_split(s, ':');
	if (!sp[0] && ft_strchr(s, ':'))
	{
		ft_free_split(sp);
		return (1);
	}
	while (sp[i])
	{
		if (stat(sp[i], &sb) != 0)
		{
			ft_free_split(sp);
			return (0);
		}
		i++;
	}
	ft_free_split(sp);
	return (1);
}

void	ft_check_perm(char **env_args, char **argv, struct stat sb, int ret)
{
	if (ret == 0 && sb.st_mode & S_IXUSR && sb.st_mode & S_IRUSR &&
	!S_ISDIR(sb.st_mode) && check_path(get_path()))
	{
		execve(argv[0], argv, env_args);
		exit(0);
	}
	else if (ret == 0 && ((!(sb.st_mode & S_IXUSR) || !(sb.st_mode & S_IRUSR))
	|| S_ISDIR(sb.st_mode)) && ft_strchr(argv[0], '/'))
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_mprint("minishell: ", argv[0], ": ", "is a directory");
		}
		else if (!(sb.st_mode & S_IXUSR) || !(sb.st_mode & S_IRUSR))
		{
			ft_mprint("minishell: ", argv[0], ": ", "Permission denied");
		}
		exit(126);
	}
}

void	ft_mprint(char *s1, char *s2, char *s3, char *s4)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	ft_putendl_fd(s4, 2);
}

int		ft_is_backslashed(const char *str, int i)
{
	int is_backslashed;

	i--;
	is_backslashed = 0;
	while (i >= 0 && str[i] == '\\')
	{
		is_backslashed = !is_backslashed;
		i--;
	}
	return (is_backslashed);
}
