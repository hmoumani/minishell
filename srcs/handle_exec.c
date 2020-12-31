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

t_list *lstchr(t_list *head, char *s)
{
    t_list *curr;
    int len;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    curr = head;
    while (curr)
    {
        if (!ft_strncmp(s, curr->content, len) && *(((char *)curr->content) + len) == '=')
            return (curr);
        curr = curr->next;
    }
    return (NULL);
}

// void delete_node(char *s)
// {
//     int len;
//     t_list *curr;
//     t_list *prev;
//     /* TODO: you need to update the env_head to check for updates */
//     curr = g_env.env_head;
//     prev = curr;
//     while (curr)
//     {
//         len = 0;
//         // printf("*** %s\n", ((char *)curr->content));
//         while (((char *)curr->content)[len] != '='){
//             printf("%d\n", len);
//             len++;
//         }
//         // printf("---> %d\n", strncmp(curr->content, s, len));
//         if (!strncmp(curr->content, s, len))
//         {
//             ft_fprintf(2, "hi");
//             prev->next = curr->next;
//             ft_lstdelone(curr, free);
//             ft_fprintf(2, "%p *** %p\n", prev, curr);
//             return ;
//         }
//         prev = prev->next;
//         curr = curr->next;
//     }
// }

int customized_len(char *s)
{
    int len;

    len = 0;
    while (s[len] && s[len] != '=')
    {
        len++;
    }
    return (len);
}

void deleteNode(char *s) 
{ 
    // Store head node 
    t_list *temp = g_env.env_head, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && !strncmp(temp->content, s, customized_len(temp->content))) 
    { 
        g_env.env_head = temp->next;   // Changed head 
        ft_lstdelone(temp, free);
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && strncmp(temp->content, s, customized_len(temp->content))) 
    {
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 
  
    ft_lstdelone(temp, free);  // Free memory 
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

void ft_echo(char **argv)
{
    int i;

    i = 1;
    if (!strcmp(argv[1], "-n"))
        i = 2;
    while (argv[i])
    {
        ft_putstr_fd(argv[i], 1);
        i++;
        if (argv[i])
            ft_putstr_fd(" ", 1);
    }
    if (strcmp(argv[1], "-n"))
        ft_putstr_fd("\n", 1);
}

void ft_cd(char **argv)
{
    // char *s1;
    int ret;

    g_env.home = get_home();
    if (argv[1])
        ret = chdir(argv[1]);
    else
    {
        ret = chdir(g_env.home);
    }
    if (ret < 0)
        ft_putstr_fd(strerror(errno), 2);
}

void ft_pwd(char **argv)
{
    argv = NULL;
    ft_putstr_fd(getcwd(NULL, 0), 1);
}

int is_valid_identifier(char *s)
{
    int i;

    i = 0;
    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (0);
    while (s[i])
    {
        if (!ft_isalpha(s[i]) && s[i] != '_' && !ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_print_path(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        ft_putchar_fd(s[i], 1);
        if (s[i] == '=')
            break;
        i++;
    }
    i++;
    ft_putchar_fd('"', 1);
    while (s[i])
    {
        ft_putchar_fd(s[i], 1);
        i++;
    }
    ft_putchar_fd('"', 1);
}

void show_all_env(char *start_with)
{
    t_list *curr;

    curr = g_env.env_head;
    while (curr)
    {
        ft_putstr_fd(start_with, 1);
        ft_print_path(curr->content);
        ft_putstr_fd("\n", 1);
        curr = curr->next;
    }
}

void    ft_export(char **argv)
{
    t_list *temp;
    char **sp;
    char *pfree;

    sp = ft_split(argv[1], '=');
    /*
        if (!sp)
            export have another behaviour if it's called only "export"
            SEGV
        don't forget: export ll=fef=fef
    */
    if (argv[1] == NULL)
    {
        show_all_env("declare -x ");
        return ;
    }
    /* check it again */
    if (!is_valid_identifier(sp[0]))
    {
        ft_fprintf(2, "export: `%s': not a valid identifier\n", argv[1]);
        return ;
    }
    // ft_fprintf(2, "%p\n", sp[0]);
    temp = lstchr(g_env.env_head, sp[0]);
    if (temp)
    {
        pfree = temp->content;
        temp->content = ft_strdup(argv[1]);
        free(pfree);
    }
    else
    {
        ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(argv[1])));
    }
    temp = lstchr(g_env.env_head, sp[0]);
    if (temp)
    {
        ft_putstr_fd(temp->content, 2);
    }
    else
    {
        ft_putstr_fd("!exist\n", 2);
    }
}

void ft_unset(char **argv)
{
    deleteNode(argv[1]);
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
