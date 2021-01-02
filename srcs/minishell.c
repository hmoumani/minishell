/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:58:08 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/13 12:58:11 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit() {
    ft_putendl_fd("exit", 1);
    exit(0);
}

void    ft_error(char *str)
{
    ft_putendl_fd(str, 2);
    exit(1);
}

t_command   *ft_new_command(int in, int out)
{
    t_command   *cmd;

    cmd = malloc(sizeof(t_command));
    cmd->argv = NULL;
    cmd->inRed = in;
    cmd->outRed = out;
    cmd->inFiles = NULL;
    cmd->outFiles = NULL;
    cmd->aoutFiles = NULL;
    return (cmd);
}

void    show_prompt(char *type)
{
    if (!type) {
        ft_fprintf(1, BBLU "minishell %d%s> "RESET, g_minishell.return_code,
                g_minishell.return_code ? BRED : BGRN);
    } else if (ft_strequ(type, PIPE)) {
        ft_fprintf(1, "pipe > ");
    }
}

void    ft_split_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void    ft_free_command(void *cmd)
{
    ft_lstclear(&((t_command *) cmd)->argv, free);
    free(cmd);
    // return NULL;
}

int ft_skip_space(const char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ')
        i++;
    return (i);
}

int get_next_word(const char *str, char *d)
{
    int     i;
    char    quote[2];

    i = ft_skip_space(str);
    ft_bzero(quote, 2);

    while (str[i])
    {
        // write(1, str + i, 1);
        if (!quote[0] || ft_on_char(str, i, quote))
		{
			if (ft_on_char(str, i, "'\""))
                quote[0] = quote[0] ? 0 : str[i];
            if (!ft_on_char(str, i, d) || ft_on_char(str, i, d))
				break;
        }
        i++;
    }
    i += ft_skip_space(str + i);
    return (i);
}

int    ft_precess_cmd(char *str)
{
    t_command   *cmd;

    cmd = g_minishell.cmd_tail->content;
    // ft_fprintf(1, "%s\n", str);
    if (((ft_strncmp(str, OUTPUT_RED, 1) == 0 || ft_strncmp(str, APP_OUTPUT_RED, 2) == 0 
        || ft_strncmp(str, INPUT_RED, 1) == 0) && (g_minishell.read_next != NULL && ft_strequ(g_minishell.read_next, PIPE))) ||
        ((ft_strncmp(str, PIPE, 1) == 0 || ft_strncmp(str, SEMI_COLUMN, 1) == 0) && 
        (g_minishell.read_next != NULL || cmd->argv == NULL)))
        return ft_syntax_error(str);
    // else if (*str !=)
    if (ft_strncmp(str, PIPE, 1) == 0)
        ft_handle_pipe(str);
    else if (ft_strncmp(str, SEMI_COLUMN, 1) == 0)
        ft_handle_semi_column(str);
    else if (ft_strncmp(str, INPUT_RED, 1) == 0)
        ft_handle_input_red(str);
    else if (ft_strncmp(str, APP_OUTPUT_RED, 2) == 0)
        ft_handle_output_red(str, APP_OUTPUT_RED);
    else if (ft_strncmp(str, OUTPUT_RED, 1) == 0)
        ft_handle_output_red(str, OUTPUT_RED);
    else
        ft_handle_cmd(str);
    return 0;
}

void    init()
{
    g_minishell.cmd_head = ft_lstnew(ft_new_command(0, 1));
    g_minishell.cmd_tail = g_minishell.cmd_head;
    g_minishell.stat = 1;
    g_minishell.forked = 0;
    g_minishell.read_next = NULL;
    g_minishell.pos = 0;
}

int     get_command_line(char **line) 
{
    char    b[2];
    int     r;
    char    *tmp;

    *line = ft_strdup("");
    while ((r = read(0, b, 1)) != -1)
    {
        // ft_fprintf(1, "%d %d %c %s\n", r, *b, *b, *line);
        if (r == 0)
        {
            if (ft_strncmp(*line, "", 1) == 0)
            {
                if (!ft_strequ(g_minishell.read_next, PIPE))
                    ft_exit();
                ft_syntax_error("\x4");
                break;
            }
            ft_putstr_fd("  \b\b", 1);
            continue;
        }
        else if (b[0] == '\n')
            break;
        tmp = *line;
        b[1] = 0;
        *line = ft_strjoin(*line, b);
        free(tmp);
    }
    return (r);
}

char *get_path()
{
    t_list *curr;
    /* TODO: you need to update the env_head to check for updates */
    curr = g_env.env_head;
    while (curr)
        {
        if (!strncmp(curr->content, "PATH", 4))
        {
            return (curr->content + 5);
        }
        curr = curr ->next;
    }
    return (NULL);
}

char *get_home()
        {
    t_list *curr;

    curr = g_env.env_head;
    while (curr)
        {
        if (!strncmp(curr->content, "HOME", 4))
        {
            return (curr->content + 5);
        }
        curr = curr ->next;
    }
    return (NULL);
}

int     main(int argc, char **argv, char **env)
{
    g_env.env_head = ft_array_to_lst(env);
    g_env.path = ft_split(get_path(), ':');
    argc = 0;
    argv = NULL;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigint);
    g_minishell.return_code = 0;
    while (1)
    {
        if (ft_strequ(g_minishell.read_next, PIPE)) {

            show_prompt(PIPE);
            // g_minishell.cmd_head = ft_lstnew(ft_new_command(0, 1));
            // g_minishell.cmd_tail = g_minishell.cmd_head;
            g_minishell.forked = 0;
            // g_minishell.read_next = NULL;
            g_minishell.pos = 0;
            get_command_line(&g_minishell.command_line);
        }
        else {
            show_prompt(NULL);
            init();
            // g_minishell.command_line = get_command_line();
            get_command_line(&g_minishell.command_line);
        }
        // get_next_line(0, &g_minishell.command_line);
        // if (r == 0 && !g_minishell.command_line)
            // ft_exit();
        // else
            // write(1, "HH", 2);
        int len = ft_strlen(g_minishell.command_line);
        while (g_minishell.stat && g_minishell.command_line[g_minishell.pos] &&
        (g_minishell.pos += get_next_word(g_minishell.command_line + g_minishell.pos, SEP)) != -1)
        {
            if (g_minishell.command_line[g_minishell.pos] == 0)
                break;
            // if (ft_on_char(g_minishell.command_line + pos, 0, SEP))
                // pos++;
            len = ft_word_length(g_minishell.command_line + g_minishell.pos, SEP);
            // ft_putnbr_fd(len, 1);
            // ft_putendl_fd(g_minishell.command_line + g_minishell.pos, 1);
            ft_precess_cmd(g_minishell.command_line + g_minishell.pos);
            g_minishell.pos += len;
            // g_minishell.pos++;
        }
        if (g_minishell.stat && g_minishell.read_next != NULL && !ft_strequ(g_minishell.read_next, PIPE))
            ft_syntax_error("\n");

        // print_commands();
        if (g_minishell.stat && g_minishell.read_next == NULL)
            execute_commands();
        if (!ft_strequ(g_minishell.read_next, PIPE))
            ft_lstclear(&g_minishell.cmd_head, ft_free_command);
        free(g_minishell.command_line);
        g_minishell.command_line = NULL;
    }
    return (EXIT_SUCCESS);
}