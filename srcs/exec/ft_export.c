/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:16:36 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/13 10:43:38 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			export_normal(char *string)
{
	t_list	*node;
	char	*pfree;

	if ((node = lstchr(g_env.env_head, string)))
	{
		pfree = node->content;
		node->content = ft_strdup(string);
		free(pfree);
	}
	else
	{
		ft_lstadd_back(&g_env.env_head, ft_lstnew(ft_strdup(string)));
	}
}

void			add_element(char *key, char *value)
{
	char *pfree;
	char *holder;

	holder = ft_strjoin(key, "=");
	pfree = holder;
	if (value)
	{
		holder = ft_strjoin(holder, value);
		free(pfree);
	}
	export_normal(holder);
	free(holder);
}

void			export_append(char *string, char **sp, int len)
{
	char	**tmp;
	t_list	*node;

	*ft_strchr(sp[0], '+') = 0;
	tmp = NULL;
	if ((node = lstchr(g_env.env_head, string)))
	{
		if (len == 1)
			export_name(sp[0]);
		else
		{
			tmp = ft_split(node->content, '=');
			if (ft_ptr_str_len(tmp) == 1)
				add_element(sp[0], sp[1]);
			else if (ft_ptr_str_len(tmp) == 2)
				add_element(sp[0], ft_strjoin(tmp[1], sp[1]));
		}
	}
	else
	{
		add_element(sp[0], sp[1]);
	}
}

static	void	redirect(char **sp, char **argv, int i)
{
	if (ft_ptr_str_len(sp) == 1 && !ft_strchr(argv[i], '='))
		export_name(argv[i]);
	else if (sp[0][ft_strlen(sp[0]) - 1] == '+' && ft_strchr(argv[i], '='))
		export_append(argv[i], sp, ft_ptr_str_len(sp));
	else if (ft_ptr_str_len(sp) == 1 && ft_strchr(argv[i], '='))
		export_empty_string(argv, sp, i);
	else
		export_normal(argv[i]);
}

int				export_all(char **argv)
{
	char	**sp;
	int		i;
	int		ret;
	char	*s;

	ret = 0;
	s = "not a valid identifier";
	i = 1;
	while (argv[i])
	{
		sp = ft_split(argv[i], '=');
		if (!is_valid_identifier(sp[0]) || argv[i][0] == '=')
		{
			g_minishell.return_code = 1;
			ft_mprint("minishell: export: `", argv[i], "': ", s);
			i++;
			ret = 1;
			ft_free_split(sp);
			continue ;
		}
		redirect(sp, argv, i);
		ft_free_split(sp);
		i++;
	}
	return (ret);
}
