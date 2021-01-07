/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:42:21 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/30 15:42:23 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *env_sep = "'\"$\\?=" SEP;

char    *ft_get_var(char *name)
{
    char *res;
    t_list *lst;

    lst = lstchr(g_env.env_head, name);
    if (lst == NULL)
        return (ft_strdup(""));
    res = ft_strchr(lst->content, '=');
    if (res == NULL)
        return (ft_strdup(""));
    return (ft_strdup(res + 1));
}

char    *ft_convert_env(char *str, int i)
{
    // int     i;
    char    *res;
    char    *tmp;
    char    *var;
    int     len;

    // i = 0;
    // res = ft_strdup("");
    res = ft_substr(str, 0, i);

    while (str[i] && !ft_on_char(str, i, ";"))
    {
        if (ft_on_char(str, i, "$") && (len = ft_word_length(str + i + 1, env_sep)) > 0) {
            i++;
            if (ft_on_char(str, i, "0123456789") && i++)
                continue;
            // len = get_next_word(&str[i], env_sep);
            g_minishell.env_var = 1;

            tmp = ft_substr(str, i, len);
            i += len;
            var = ft_get_var(tmp);
            // sprintf(var, "%s", );
            free(tmp);
            tmp = res;
            res = ft_strjoin(res, var);
            free(var);
            free(tmp);
        } else if (ft_on_char(str, i + 1, "?")) {
            var = ft_itoa(g_minishell.return_code);
            tmp = res;
            res = ft_strjoin(res, var);
            free(var);
            free(tmp);
            i += 2;
        } else {
            tmp = res;
            res = ft_strappend(res, str[i]);
            free(tmp);
            i++;
        }
    }
    if (str[i])
    {
        tmp = res;
        res = ft_strjoin(res, str + i);
        free(tmp);
    }
    return (res);
}
