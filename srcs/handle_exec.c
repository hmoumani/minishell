/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:59:15 by hmoumani          #+#    #+#             */
/*   Updated: 2020/12/29 14:59:18 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

t_list *ft_array_to_lst(char **array)
{
    t_list *head;
    int i;

    // if (!(head = malloc(sizeof(t_list *))))
    //     return (NULL);
    i = 0;
    head = NULL;
    while (array[i])
    {   
        ft_lstadd_back(&head, ft_lstnew(ft_strdup(array[i])));
        i++;
    }
    return (head);
}

int is_command(char *s)
{
    if (!strcmp(s, "echo"))
        return (1);
    if (!strcmp(s, "cd"))
        return (2);
    if (!strcmp(s, "pwd"))
        return (3);
    if (!strcmp(s, "export"))
        return (4);
    if (!strcmp(s, "unset"))
        return (5);
    if (!strcmp(s, "env"))
        return (6);
    if (!strcmp(s, "exit"))
        return (7);
    return (0);
}



void treat_cmd(char **argv, int cmd_id)
{
    if (cmd_id == 1)
        ft_echo(argv);
    else if (cmd_id == 2)
        ft_cd(argv);
    else if (cmd_id == 3)
        ft_pwd(argv);
    else if (cmd_id == 4)
        ft_export(argv);
    else if (cmd_id == 5)
        ft_unset(argv);
    else if (cmd_id == 6)
        ft_env(argv);
}

int ft_try_path(char **argv)
{
    int i;
    struct stat sb;
    char *env_args[] = { (char*)0 };
    char *s = NULL;

    i = 0;
    // printf("%s", argv[0]);
    while (g_env.path[i])
    {
        s = ft_strjoin(g_env.path[i], "/");
        s = ft_strjoin(s, argv[0]);
        // printf("%s\n", s);
        if (stat(s, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
            execve(s, argv, env_args);
            return (1);
        }
        i++;
    }
    return (0);
}

void ft_redirect(char **argv)
{
    int cmd_id;
    char *env_args[] = { (char*)0 };
    struct stat sb;
    if ((cmd_id = is_command(argv[0])))
    {
        treat_cmd(argv, cmd_id);
        return ;
    }
    if (stat(argv[0], &sb) == 0 && sb.st_mode & S_IXUSR)
    {
        execve(argv[0], argv, env_args);
        return ;
    }
    else
    {
        if (ft_try_path(argv))
            return ;
    }
    printf("minishell: command not found: %s\n", argv[0]);
}

void    execute_command(t_command *cmd)
{
    // t_command   *cmd;
    char        **argv;
    // char        *path;

    
    // cmd = (t_command *) c;
    argv = ft_lst_to_array(cmd->argv);
    // path = ft_strjoin("/bin/", argv[0]);
    // char *env_args[] = { (char*)0 };
    // printf("|%s %d %d|\n", cmd->argv->content, cmd->inRed, cmd->outRed);
    open_redirect_files(cmd);
    dup2(cmd->inRed, 0);
    dup2(cmd->outRed, 1);
    // execve(argv[0], argv, env_args);
    ft_redirect(argv);
    // ft_putstr_fd("minishell: command not found: ", 2);
    // ft_putendl_fd(argv[0], 2);
    exit(127);
}

void    execute_commands()
{
    t_list  *lst;
    t_command   *cmd;
    int         ret;
    char        **argv;

    lst = g_minishell.cmd_head;
    while (lst != NULL)
	{
        cmd = (t_command *)lst->content;
        if (!(cmd = (t_command *)lst->content) || !cmd->argv)
            break;
        argv = ft_lst_to_array(cmd->argv);
        
        if ((ret = is_command(argv[0])))
        {
            treat_cmd(argv, ret);
            return ;
        }

        if (fork() == 0) {
            // ft_putendl_fd("FORK", 1);
            signal(SIGINT, SIG_DFL);
            // print_command(cmd);
            execute_command(lst->content);
        }
        else
        {
            free_redirect_files();
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
    // ft_lstiter(g_minishell.cmd_head, execute_command);
}
