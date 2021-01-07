/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:43:10 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/27 15:43:12 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_syntax_error(char *token)
{
    if (*token == '\x4')
        ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
    else {
        if (*token == '\n')
            token = "newline";
        else
            token[1] = 0;
        ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
                    token);
    }
    // ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    // ft_putstr_fd(token, 2);
    // ft_putendl_fd("'", 2);
    g_minishell.return_code = 258;
    g_minishell.stat = 0;
    g_minishell.read_next = NULL;
    // ft_lstclear(&g_minishell.cmd_head, ft_free_command);

    return (1);
}

int    ft_handle_cmd(char *str)
{
    int	len;
    char *arg;
    t_command   *cmd;

    len = ft_word_length(str, SEP);
    str = ft_substr(str, 0, len);
    // arg = ft_convert_env(str);
    // str = arg;
    arg = ft_quotes_convert(str);
    free(str);
    if (ft_strequ(g_minishell.read_next, INPUT_RED))
        ft_handle_input_red(arg);
    else if (ft_strequ(g_minishell.read_next, OUTPUT_RED) || ft_strequ(g_minishell.read_next, APP_OUTPUT_RED))
        ft_handle_output_red(arg, g_minishell.read_next);
    else if (arg) {
        // ft_putstr_fd("CMD:", 1);
        cmd = g_minishell.cmd_tail->content;
        // ft_fprintf(1, "CMD %s %d\n", arg, cmd->inRed);
        ft_lstadd_back(&cmd->argv, ft_lstnew(arg));
        // ft_putendl_fd(arg, 1);
    }
    // if (arg)
        // free(arg);
    g_minishell.read_next = NULL;
    return (0);
}

int    ft_handle_pipe(char *str)
{
    // t_list      *item;
    t_command   *cmd;
    int         p[2];

    cmd = g_minishell.cmd_tail->content;
    if (pipe(p) < 0)
        ft_error("pipe error");

    cmd->outRed = p[1];
    cmd->pipe[0] = p[0];
    // ft_fprintf(2, "PIPE %d %d\n", p[0], p[1]);
    // ft_fprintf(1, "PIPE %d\n", p[0]);
    g_minishell.cmd_tail = ft_lstnew(ft_new_command(p[0], 1, p[1]));
    ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);
    str = NULL;
    g_minishell.read_next = PIPE;
    g_minishell.pos++;
    return (0);
}

static t_red_file   *ft_red_file(char *file, char type)
{
    t_red_file  *red_file;

    red_file = malloc(sizeof(t_red_file));
    red_file->file = file;
    red_file->type = type;
    return (red_file);
}

int    ft_handle_semi_column(char *str)
{
    t_command   *cmd;
    cmd = g_minishell.cmd_tail->content;

    ft_execute(0);
    g_minishell.cmd_head = ft_lstnew(ft_new_command(0, 1, -1));
    g_minishell.cmd_tail = g_minishell.cmd_head;
    // ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);

    str = g_minishell.command_line;
    g_minishell.command_line = ft_convert_env(g_minishell.command_line, g_minishell.pos + 1);
    // ft_fprintf(2, "|%s|\n", g_minishell.command_line);

    free(str);
    g_minishell.read_next = NULL;
    g_minishell.pos++;
    return (0);
}

int    ft_handle_input_red(char *str)
{
    if (ft_strequ(g_minishell.read_next, INPUT_RED))
    {
        ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->redFiles, ft_lstnew(ft_red_file(str, 0)));
        g_minishell.read_next = NULL;
    } else {
        g_minishell.read_next = INPUT_RED;
        g_minishell.pos++;
    }
    return (0);
}

int    ft_handle_output_red(char *str, char *app)
{
    if (ft_strequ(g_minishell.read_next, OUTPUT_RED))
    {
        // t_list *tmp;`
        // t_command *cmd = ((t_command *)g_minishell.cmd_tail->content);
        ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->redFiles, ft_lstnew(ft_red_file(str, 1)));

        g_minishell.read_next = NULL;

    } else if (ft_strequ(g_minishell.read_next, APP_OUTPUT_RED)) {
        ft_lstadd_back(&((t_command *)g_minishell.cmd_tail->content)->redFiles, ft_lstnew(ft_red_file(str, 2)));
        g_minishell.read_next = NULL;
    } else {
        if (ft_strequ(app, APP_OUTPUT_RED)) {
            g_minishell.pos += 2;
        } else {
            g_minishell.pos++;
        }
        g_minishell.read_next = app;
    }
    return (0);
}

void    putstr(void *str, void *param)
{
    param = NULL;
    ft_putstr_fd("|", 1);
    ft_putstr_fd(str, 1);
    ft_putendl_fd("|", 1);
}

void    print_command(void *cmd, void *param) {
    // ft_putendl_fd(cmd->argv->content);
    ft_putendl_fd("-----", 1);
    ft_lstiter(((t_command *) cmd)->argv, putstr, param);
}

void    print_commands()
{
    ft_lstiter(g_minishell.cmd_head, print_command, NULL);
    ft_putendl_fd("-----", 1);
}

//----------------
/*
char    **ft_lst_to_array(t_list    *lst)
{
    char        **argv;
    int         len;
    int         i;

    len = ft_lstsize(lst);
    argv = malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (i < len)
    {
        argv[i] = lst->content;
        i++;
        lst = lst->next;
    }
    argv[i] = NULL;
    return (argv);
}


void    execute_command(t_command *cmd)
{
    // t_command   *cmd;
    char        **argv;
    char        *path;

    
    // cmd = (t_command *) c;
    argv = ft_lst_to_array(cmd->argv);
    path = ft_strjoin("/bin/", argv[0]);
    char *env_args[] = { (char*)0 };
    // ft_fprintf(1, "|%s %d %d|\n", cmd->argv->content, cmd->inRed, cmd->outRed);

    open_redirect_files(cmd);
    dup2(cmd->inRed, 0);
    dup2(cmd->outRed, 1);
    execve(path, argv, env_args);
    ft_fprintf(2, "minishell: %s: command not found\n", argv[0]);
    exit(127);
}

void    execute_commands()
{
    t_list  *lst;
    t_command   *cmd;
    int         ret;

    lst = g_minishell.cmd_head;
    while (lst != NULL)
	{
        cmd = (t_command *)lst->content;
        if (!(cmd = (t_command *)lst->content) || !cmd->argv)
            break;
        if (fork() == 0) {
            // ft_putendl_fd("FORK", 1);
            signal(SIGINT, SIG_DFL);
            // print_command(cmd);
            execute_command(lst->content);
        }
        else
        {
            g_minishell.forked = 1;
            wait(&ret);
            // char *s = (char *)&ret;
            // ft_fprintf(1, "%d %d %d %d\n", s[0], s[1], s[2], s[3]);
            if (WIFEXITED(ret))
                g_minishell.return_code = WEXITSTATUS(ret);
            if (cmd->inRed != 0)
                close(cmd->inRed);
            if (cmd->outRed != 1)
                close(cmd->outRed);
            g_minishell.forked = 0;
        }
		lst = lst->next;
	}
    free_redirect_files();
    // ft_lstiter(g_minishell.cmd_head, execute_command);
}
*/