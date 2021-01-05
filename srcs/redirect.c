/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:01:25 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/27 18:01:26 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     open_file(char *file, int flags, char *type)
{
    int         fd;
    t_command   *cmd;
    int         red;

    cmd = g_minishell.cmd_head->content;
    red = ft_strequ(type, INPUT_RED) ? cmd->inRed : cmd->outRed;
    if (red != 1)
        close(red);
    if (ft_strequ(type, INPUT_RED))
        fd = open(file, flags);
    else
        fd = open(file, flags, 0644);
    
    if (fd == -1) {  
        ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
        g_minishell.stat = 0;
        exit(1);
    }
    return fd;
}

void    open_input_file(void  *f, void *c)
{
    int         fd;
    char        *file;
    t_command   *cmd;

    file = f;
    cmd = c;

    fd = open_file(file, O_RDONLY, INPUT_RED);
    if (fd != -1)
        cmd->inRed = fd;
    
}

void    open_out_file(void  *f, void *c)
{
    int         fd;
    char        *file;
    t_command   *cmd;

    file = f;
    cmd = c;
    fd = open_file(file, O_WRONLY | O_CREAT | O_TRUNC, OUTPUT_RED);
    if (fd != -1)
        cmd->outRed = fd;
}

void    open_aout_file(void  *f, void *c)
{
    int         fd;
    char        *file;
    t_command   *cmd;

    file = f;
    cmd = c;
    fd = open_file(file, O_WRONLY | O_CREAT | O_APPEND, APP_OUTPUT_RED);
    if (fd != -1)
        cmd->outRed = fd;
}

static void ft_free(void *ptr)
{
    // ft_fprintf(1, "%p %s\n", ptr, ptr);
    free(ptr);
}
void    open_redirect_files(t_command *cmd)
{

    ft_lstiter(cmd->inFiles, open_input_file, cmd);
    ft_lstiter(cmd->outFiles, open_out_file, cmd);
    ft_lstiter(cmd->aoutFiles, open_aout_file, cmd);
    // ft_lstclear(&(cmd->inFiles), ft_free);
    // ft_lstclear(&(cmd->outFiles), ft_free);
    // ft_lstclear(&(cmd->aoutFiles), ft_free);
}

void    free_files(void *c, void *param)
{
    t_command  *cmd;

    cmd = c;
    param = NULL;
    ft_lstclear(&cmd->inFiles, ft_free);
    ft_lstclear(&cmd->outFiles, ft_free);
    ft_lstclear(&cmd->aoutFiles, ft_free);
}

void    free_redirect_files()
{
    ft_lstiter(g_minishell.cmd_head, free_files, NULL);
}