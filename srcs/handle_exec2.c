/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:18:26 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 15:17:05 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_command(char *s)
{
	if (ft_strequ(s, "echo"))
		return (1);
	if (ft_strequ(s, "cd"))
		return (2);
	if (ft_strequ(s, "pwd"))
		return (3);
	if (ft_strequ(s, "export"))
		return (4);
	if (ft_strequ(s, "unset"))
		return (5);
	if (ft_strequ(s, "env"))
		return (6);
	if (ft_strequ(s, "exit"))
		return (7);
	return (0);
}

int			treat_cmd(char **argv, int cmd_id)
{
	if (cmd_id == 1)
		ft_echo(argv);
	else if (cmd_id == 2)
		return (ft_cd(argv));
	else if (cmd_id == 3)
		ft_pwd(argv);
	else if (cmd_id == 4)
		return (ft_export(argv));
	else if (cmd_id == 5)
		return (ft_unset(argv));
	else if (cmd_id == 6)
		ft_env(argv);
	else if (cmd_id == 7)
		return (ft_exit(argv));
	return (0);
}

int			ft_try_path(char **argv)
{
	int			i;
	struct stat	sb;
	char		**env_args;
	char		*s;
	char		*tmp;

	i = -1;
	env_args = ft_lst_to_array(g_env.env_head);
	if (!(g_env.path = ft_split(get_path(), ':')))
		return (1);
	while (g_env.path[++i])
	{
		s = ft_strjoin(g_env.path[i], "/");
		tmp = s;
		s = ft_strjoin(s, argv[0]);
		free(tmp);
		if (stat(s, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execve(s, argv, env_args);
			free(s);
			return (0);
		}
		else if (stat(s, &sb) == 0 && !(sb.st_mode & S_IXUSR))
		{
			ft_fprintf(2, "minishell: %s: Permission denied\n", s);
			free(s);
			exit(126);
		}
		free(s);
	}
	return (1);
}

int			ft_redirect(char **argv)
{
	char		**env_args;
	struct stat sb;
	int			ret;

	env_args = ft_lst_to_array(g_env.env_head);
	ret = stat(argv[0], &sb);
	if (S_ISLNK(sb.st_mode))
		ret = lstat(argv[0], &sb);
	ft_check_perm(env_args, argv, sb, ret);
	if (!ft_strchr(argv[0], '/'))
		if (!ft_try_path(argv))
			return (0);
	if (ret && ft_strchr(argv[0], '/'))
	{
		ft_fprintf(2, "minishell: %s: %s\n", argv[0], strerror(errno));
		// ft_mprint("minishell: ", "fork: ", strerror(errno));

		return (1);
	}
	if (!get_path() || *get_path() == 0)
		ft_fprintf(2, "minishell: %s: No such file or directory\n", argv[0]);
	else
		ft_fprintf(2, "minishell: %s: command not found\n", argv[0]);
	return (1);
}

void		execute_command(t_command *cmd)
{
	char	**argv;

	argv = ft_lst_to_array(cmd->argv);
	open_redirect_files(cmd);
	dup2(cmd->in_red, 0);
	dup2(cmd->out_red, 1);
	ft_redirect(argv);
	exit(127);
}
