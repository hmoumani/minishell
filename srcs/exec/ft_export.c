/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:13:47 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:13:49 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int custem_len(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    return (i);
}

t_list *lstchr(t_list *head, char *s)
{
    t_list *curr;
    int len;

    if (!s)
        return (NULL);
    len = custem_len(s);
    curr = head;
    while (curr)
    {
        if (!ft_strncmp(s, curr->content, len) && (*(((char *)curr->content) + len) == '=' ||
        *(((char *)curr->content) + len) == '\0'))
            return (curr);
        curr = curr->next;
    }
    return (NULL);
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
    if (!strchr(s, '='))
        return ;
    i++;
    ft_putchar_fd('"', 1);
    while (s[i])
    {
        ft_putchar_fd(s[i], 1);
        i++;
    }
    ft_putchar_fd('"', 1);
}

void show_all_export(char *start_with)
{
    t_list *curr;

    curr = g_env.env_head;
    while (curr)
    {
        if (!strncmp(curr->content, "_=", 2))
        {
            curr = curr->next;
            continue ;
        }
        ft_putstr_fd(start_with, 1);
        ft_print_path(curr->content);
        ft_putstr_fd("\n", 1);
        curr = curr->next;
    }
}

void    ft_export(char **argv)
{
    // t_list *temp;
    // char **sp;
    // char *pfree;

    // sp = ft_split(argv[1], '=');
    // /*
    //     if (!sp)
    //         export have another behaviour if it's called only "export"
    //         SEGV
    //     don't forget: export ll=fef=fef
    // */
    // if (argv[1] == NULL)
    // {
    //     show_all_export("declare -x ");
    //     return ;
    // }
    // /* check it again */
    // if (!is_valid_identifier(sp[0]))
    // {
    //     ft_fprintf(2, "export: `%s': not a valid identifier\n", argv[1]);
    //     return ;
    // }
    // // ft_fprintf(2, "%p\n", sp[0]);
    // temp = lstchr(g_env.env_head, sp[0]);
    // if (temp)
    // {
    //     pfree = temp->content;
    //     temp->content = ft_strdup(argv[1]);
    //     free(pfree);
    // }
    // else
    // {
    //     ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(argv[1])));
    // }
    // temp = lstchr(g_env.env_head, sp[0]);
    // if (temp)
    // {
    //     ft_putstr_fd(temp->content, 2);
    // }
    // else
    // {
    //     ft_putstr_fd("!exist\n", 2);
    // }
    if (!argv[1])
        show_all_export("declare -x ");
    else
        export_all(argv);
}

int ft_ptr_str_len(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
        i++;
    return (i);
}

void export_name(char **argv, int i)
{
    if (lstchr(g_env.env_head, argv[i]))
        return ;
    ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(argv[i])));
}

void export_empty_string(char **argv, char **sp, int i)
{
    t_list *node;
    char *pfree;

    if ((node = lstchr(g_env.env_head, argv[i])))
    {
        pfree = node->content;
        node->content = ft_strjoin(argv[i], "");
        free(pfree);
    }
    else
    {
        ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strjoin(argv[i], "")));
    }
    sp = NULL;
}

void export_normal(char **argv, char **sp, int i)
{
    t_list *node;
    char *pfree;

    if ((node = lstchr(g_env.env_head, argv[i])))
    {
        pfree = node->content;
        node->content = ft_strdup(argv[i]);
        free(pfree);
    }
    else
    {
        ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(argv[i])));
    }
    sp = NULL;
}

void export_all(char **argv)
{
    char **sp;
    int i;

    i = 1;
    while (argv[i])
    {
        sp = ft_split(argv[i], '=');
        if (!is_valid_identifier(sp[0]))
        {
            ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", argv[i]);
            i++;
            continue ;
        }
        if (ft_ptr_str_len(sp) == 1 && !ft_strchr(argv[i], '=')) //export ll
            export_name(argv, i);
        else if (ft_ptr_str_len(sp) == 1 && ft_strchr(argv[i], '=')) // export ll=
            export_empty_string(argv, sp, i);
        else                                                           //export ll=normal
            export_normal(argv, sp, i);
        i++;
    }
    // if (!sp)
    //     export_name(argv);
    // if (ft_ptr_str_len(sp) == 1 && ft_strchr(argv[1], '='))
    //     export_empty_string(argv);
}