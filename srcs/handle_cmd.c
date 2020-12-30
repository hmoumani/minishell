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
    if (*token == '\n')
        token = "newline";
    else
        token[1] = 0;
    ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
                token);
    // ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    // ft_putstr_fd(token, 2);
    // ft_putendl_fd("'", 2);
    g_minishell.return_code = 258;
    g_minishell.stat = 0;
    return (1);
}

int    ft_handle_cmd(char *str)
{
    int	len;
    char *arg;
    t_command   *cmd;

    len = ft_word_length(str, SEP);
    arg = ft_substr(str, 0, len);
    if (g_minishell.read_next == INPUT_RED)
        ft_handle_input_red(arg);
    else if (g_minishell.read_next == OUTPUT_RED || g_minishell.read_next == APP_OUTPUT_RED)
        ft_handle_output_red(arg, g_minishell.read_next);
    else {
        // ft_putstr_fd("CMD:", 1);
        cmd = g_minishell.cmd_tail->content;
        ft_lstadd_back(&cmd->argv, ft_lstnew(arg));
        // ft_putendl_fd(arg, 1);
    }
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
    g_minishell.cmd_tail = ft_lstnew(ft_new_command(p[0], 1));
    ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);

    ft_putstr_fd("PIPE:", 1);
    ft_putendl_fd(str, 1);
    g_minishell.read_next = NULL;
    g_minishell.pos++;
    return (0);
}

int    ft_handle_semi_column(char *str)
{
    // t_list      *item;
    t_command   *cmd;

    // int         p[2];
    cmd = g_minishell.cmd_tail->content;
    // if (pipe(p) < 0)
        // ft_error("pipe error");
    // cmd->outRed = 1;
    g_minishell.cmd_tail = ft_lstnew(ft_new_command(0, 1));
    ft_lstadd_back(&g_minishell.cmd_head, g_minishell.cmd_tail);

    ft_putstr_fd("SEMI-C:", 1);
    ft_putendl_fd(str, 1);
    g_minishell.read_next = NULL;
    g_minishell.pos++;
    return (0);
}

int    ft_handle_input_red(char *str)
{
    if (g_minishell.read_next == INPUT_RED)
    {
        // fd = open(str, O_RDONLY);
        // if (fd == -1) {
        //     ft_fprintf(2, "minishell: %s: %s\n", str, strerror(errno));
        //     g_minishell.stat = 0;
        // } else
        //     ((t_command *)g_minishell.cmd_head->content)->inRed = fd;
        ft_lstadd_back(&((t_command *)g_minishell.cmd_head->content)->inFiles, ft_lstnew(str));
        // free(str);
        g_minishell.read_next = NULL;
    } else {
        // ft_putstr_fd("IN:", 1);
        g_minishell.read_next = INPUT_RED;
        g_minishell.pos++;
    }
    return (0);
}

int    ft_handle_output_red(char *str, char *app)
{
    if (g_minishell.read_next == OUTPUT_RED)
    {
        // fd = open(str, O_RDWR | O_CREAT |
        //     (g_minishell.read_next == APP_OUTPUT_RED ? O_APPEND : 0), 0644);
        // if (fd == -1) {
        //     ft_fprintf(2, "minishell: %s: %s\n", str, strerror(errno));
        //     g_minishell.stat = 0;
        // } else
        //     ((t_command *)g_minishell.cmd_head->content)->outRed = fd;
        t_list *tmp;
        ft_lstadd_back(&((t_command *)g_minishell.cmd_head->content)->outFiles, (tmp = ft_lstnew(str)));
        // ft_fprintf(1, "%p %s %p\n", str, str, tmp);
        g_minishell.read_next = NULL;

    } else if (g_minishell.read_next == APP_OUTPUT_RED) {
        ft_lstadd_back(&((t_command *)g_minishell.cmd_head->content)->aoutFiles, ft_lstnew(str));
        g_minishell.read_next = NULL;
    } else {
        if (app == APP_OUTPUT_RED) {
            // ft_putstr_fd("AOUT:", 1);
            g_minishell.pos += 2;
        } else {
            // ft_putstr_fd("OUT:", 1);
            g_minishell.pos++;
        }
        g_minishell.read_next = app;
        // ft_putendl_fd(str, 1);
    }
    return (0);
}

void    putstr(void *str)
{
    ft_putstr_fd("|", 1);
    ft_putstr_fd(str, 1);
    ft_putendl_fd("|", 1);
}

void    print_command(void *cmd) {
    // ft_putendl_fd(cmd->argv->content);
    ft_putendl_fd("-----", 1);
    ft_lstiter(((t_command *) cmd)->argv, putstr);
}

void    print_commands()
{
    ft_lstiter(g_minishell.cmd_head, print_command);
    ft_putendl_fd("-----", 1);
}


