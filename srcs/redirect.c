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

#include "../includes/minishell.h"

int     open_file(char *file, int flags, char *type)
{
    int         fd;
    t_command   *cmd;
    int         red;

    cmd = g_minishell.cmd_head->content;
    red = ft_strequ(type, INPUT_RED) ? cmd->inRed : cmd->outRed;
    if (red > 2)
        close(red);
    if (ft_strequ(type, INPUT_RED))
        fd = open(file, flags);
    else
        fd = open(file, flags, 0644);
    
    if (fd == -1) {  
        ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
        g_minishell.return_code = 1;
        g_minishell.stat = 0;
        // exit(1);
    }
    return fd;
}

void    open_red_file(void *f, void *c)
{
    int         fd;
    t_red_file  *red_file;
    t_command   *cmd;

    red_file = f;
    cmd = c;

    if (red_file->type == 0)
    {
        fd = open_file(red_file->file, O_RDONLY, INPUT_RED);
        // if (fd != -1)
            cmd->inRed = fd;
    }
    else if (red_file->type == 1)
    {
        fd = open_file(red_file->file, O_WRONLY | O_CREAT | O_TRUNC, OUTPUT_RED);
        // if (fd != -1)
            cmd->outRed = fd;
    }
    else if (red_file->type == 2)
    {
        fd = open_file(red_file->file, O_WRONLY | O_CREAT | O_APPEND, APP_OUTPUT_RED);
        // if (fd != -1)
            cmd->outRed = fd;
    }

}

void ft_free(void *ptr)
{
    // ft_fprintf(1, "%p %s\n", ptr, ptr);
    free(ptr);
}

static void ft_free_red_file(void *ptr)
{
    t_red_file  *red_file;

    red_file = ptr;
    free(red_file->file);
    free(red_file);
}

void    open_redirect_files(t_command *cmd)
{
    ft_lstiter(cmd->redFiles, open_red_file, cmd);
}

void    free_files(void *c, void *param)
{
    t_command  *cmd;

    cmd = c;
    param = NULL;
    ft_lstclear(&cmd->redFiles, ft_free_red_file);
}

void    free_redirect_files()
{
    ft_lstiter(g_minishell.cmd_head, free_files, NULL);
}