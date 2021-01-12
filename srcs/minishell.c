/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:29:56 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 12:50:42 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_cmd_init(void)
{
	g_minishell.cmd_head = ft_lstnew(ft_new_command(0, 1, -1));
	g_minishell.cmd_tail = g_minishell.cmd_head;
	g_minishell.stat = 1;
	g_minishell.forked = 0;
	g_minishell.read_next = NULL;
	g_minishell.pos = 0;
}

char		*get_command_line(void)
{
	char	b;
	int		r;
	char	*line;

	line = ft_strdup("");
	while ((r = read(0, &b, 1)) != -1)
	{
		if (r == 0)
		{
			if (ft_strncmp(line, "", 1) == 0)
			{
				if (!ft_strequ(g_minishell.read_next, PIPE))
					ft_exit(NULL);
				ft_syntax_error("\x4");
				break ;
			}
			ft_putstr_fd("  \b\b", 1);
			continue;
		}
		else if (b == '\n')
			break ;
		line = ft_strappend(line, b);
	}
	return (line);
}

void		ft_execute(int f)
{
	if (g_minishell.stat && g_minishell.read_next != NULL)
		ft_syntax_error("\n");
	if (g_minishell.stat && g_minishell.read_next == NULL)
		execute_commands();
	if (!ft_strequ(g_minishell.read_next, PIPE))
		ft_lstclear(&g_minishell.cmd_head, ft_free_command);
	if (f)
	{
		free(g_minishell.command_line);
		g_minishell.command_line = NULL;
	}
}

void		ft_init(char **env)
{
	char	*cwd;

	g_env.env_head = ft_array_to_lst(env);
	g_env.path = ft_split(get_path(), ':');
	cwd = getcwd(NULL, 0);
	add_element("PWD", cwd);
	free(cwd);
	add_element("SHLVL", "1");
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	g_minishell.return_code = 0;
}

int			main(int argc, char **argv, char **env)
{
	char	*old_cmd;

	ft_init(env);
	argc = 0;
	// argv = NULL;
	while (1)
	{
		if (ft_strequ(argv[1], "-c"))
        {
            ft_cmd_init();
            g_minishell.command_line = ft_strdup(argv[2]);
            // ft_fprintf(2, "%s %s\n", argv[1], g_minishell.command_line);
            ft_parse();
            ft_execute(1);
            exit(g_minishell.return_code);
        }
		show_prompt(NULL);
		ft_cmd_init();
		g_minishell.command_line = get_command_line();
		while (ft_endwith_pipe())
		{
			show_prompt(PIPE);
			g_minishell.forked = 0;
			old_cmd = g_minishell.command_line;
			g_minishell.command_line = get_command_line();
			free(old_cmd);
		}
		ft_parse();
		ft_execute(1);
	}
	return (g_minishell.return_code);
}
