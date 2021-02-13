/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:18:26 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 19:17:18 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			ft_path_iter(int i, char **env_args, char **argv)
{
	char		*s;
	struct stat	sb;

	while (g_env.path[++i])
	{
		s = join_path(g_env.path[i], "/", argv[0]);
		if (stat(s, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execve(s, argv, env_args);
			free(s);
			free(env_args);
			return (0);
		}
		else if (stat(s, &sb) == 0 && !(sb.st_mode & S_IXUSR))
		{
			ft_mprint("minishell: ", s, ": ", "Permission denied");
			free(env_args);
			free(s);
			exit(126);
		}
		free(s);
	}
	return (1);
}

int			ft_try_path(char **argv)
{
	char		**env_args;

	env_args = ft_lst_to_array(g_env.env_head);
	if (!(g_env.path = ft_split(get_path(), ':')))
		return (1);
	if (!ft_path_iter(-1, env_args, argv))
		return (0);
	free(env_args);
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
	free(env_args);
	if (!ft_strchr(argv[0], '/'))
		if (!ft_try_path(argv))
			return (0);
	if (ret && argv[0] && ft_strchr(argv[0], '/'))
	{
		ft_mprint("minishell: ", argv[0], ": ", strerror(errno));
		return (1);
	}
	if (!get_path() || *get_path() == 0)
		ft_mprint("minishell: ", argv[0], ": ", "No such file or directory");
	else
		ft_mprint("minishell: ", argv[0], ": ", "command not found");
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
