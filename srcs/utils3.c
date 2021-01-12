/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:10:26 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 15:17:30 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *s)
{
	char **sp;
	int i;
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
			return (0);
			ft_free_split(sp);
		}
		i++;
	}
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
			ft_fprintf(2, "minishell: %s: is a directory\n", argv[0]);
		else if (!(sb.st_mode & S_IXUSR) || !(sb.st_mode & S_IRUSR))
			ft_fprintf(2, "minishell: %s: Permission denied\n", argv[0]);
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